#include "runtime.h"

#include <atomic>
#include <freertos/semphr.h>

#include "Apps/App.h"
#include "Apps/Task-Manager.h"
#include "battery.h"
#include "buttons.h"
#include "clock.h"
#include "display.h"
#include "init.h"
#include "sleep.h"
#include "Components/timeLabel.h"
#include "Components/mainMenu/screenMainMenu.h"

/**
 * Runtime task implementation.
 *
 * This file owns the FreeRTOS worker tasks that coordinate the UI loop, button
 * polling, periodic main-menu refreshes, and app execution. The runtime acts as
 * the central dispatcher for app launches, input routing, and power-management
 * transitions.
 */

namespace
{
constexpr uint8_t NO_APP_ID = APP_ID_DEFAULT;
constexpr UBaseType_t UI_QUEUE_LENGTH = 24;
constexpr UBaseType_t APP_QUEUE_LENGTH = 8;
constexpr TickType_t BUTTON_POLL_TICKS = pdMS_TO_TICKS(10);
constexpr TickType_t MAIN_REFRESH_TICKS = pdMS_TO_TICKS(1000);

enum class AppTaskMessageType : uint8_t
{
    Launch,
    Close,
    Input
};

struct AppTaskMessage
{
    AppTaskMessageType type;
    uint8_t appId;
    uint8_t value;
};

QueueHandle_t uiQueue = nullptr;
QueueHandle_t appQueue = nullptr;
SemaphoreHandle_t taskStartGate = nullptr;
SemaphoreHandle_t uiReady = nullptr;
TaskHandle_t uiTaskHandle = nullptr;
TaskHandle_t buttonTaskHandle = nullptr;
TaskHandle_t mainTaskHandle = nullptr;
TaskHandle_t appTaskHandle = nullptr;
std::atomic<bool> mainMenuActive{true};
std::atomic<uint8_t> targetAppId{NO_APP_ID};

/**
 * Waits until the task startup gate is released so all worker threads begin in
 * sync after the runtime queues and semaphores have been created.
 */
void waitForTaskStart()
{
    xSemaphoreTake(taskStartGate, portMAX_DELAY);
}

/**
 * Executes a runtime UI message by updating the appropriate display or button
 * state.
 */
void dispatchUiMessage(const RuntimeUiMessage &message)
{
    switch (message.type)
    {
    case RuntimeUiMessageType::ButtonPressed:
    case RuntimeUiMessageType::ButtonDown:
    case RuntimeUiMessageType::ButtonReleased:
    {
        Button *button = buttonManager.getButton(message.value);
        if (button == nullptr)
        {
            Serial.printf("[Runtime] Ignoring event for unknown button pin %u\n", message.value);
            return;
        }

        switch (message.type)
        {
        case RuntimeUiMessageType::ButtonPressed:
            button->buttonPressed();
            break;
        case RuntimeUiMessageType::ButtonDown:
            if (button->isDown())
                button->buttonDown();
            break;
        case RuntimeUiMessageType::ButtonReleased:
            button->buttonReleased();
            break;
        default:
            break;
        }
        break;
    }
    case RuntimeUiMessageType::RefreshMainTime:
        if (mainMenuActive.load())
        {
            const DateTime now = getNow();
            setMenu_TimeLabelInformation(now);
            setTimeText(now);
        }
        break;
    case RuntimeUiMessageType::OpenApp:
        if (message.value == APP_ID_POWER)
            activatePowerScreenUI();
        else if (message.value == APP_ID_TSKMNGR)
            activateTaskManagerUI();
        else
        {
            Serial.printf("[Runtime] No UI registered for app id %u\n", message.value);
            App::closeActiveApp();
        }
        break;
    case RuntimeUiMessageType::CloseActiveApp:
        if (message.value == APP_ID_POWER)
            restoreMainScreenUI();
        else if (message.value == APP_ID_TSKMNGR)
            restoreTaskManagerUI();
        break;
    case RuntimeUiMessageType::UpdatePowerSelection:
        setPowerSelectionUI(message.value);
        break;
    case RuntimeUiMessageType::UpdateTaskManagerGraphs:
        updateGraphs();
        break;
    case RuntimeUiMessageType::NavigateTaskManager:
        navigateTaskManagerScreens(static_cast<int8_t>(message.value));
        break;
    case RuntimeUiMessageType::EnterSleep:
    {
        const int8_t style = static_cast<int8_t>(message.value);
        goToSleep(style);
        if (style == SleepStyle::ESP_SLEEP_LIGHT)
            resetMenuNavigation();
        break;
    }
    }
}

/**
 * UI pump task: receives queued runtime notifications, applies them to the
 * active screen state, and advances the LVGL tick loop.
 */
void uiTask(void *)
{
    waitForTaskStart();
    setupUI();
    const DateTime now = getNow();
    setMenu_TimeLabelInformation(now);
    setTimeText(now);
    buttonManager.buttonsEnabled = true;
    xSemaphoreGive(uiReady);

    uint32_t previousTick = millis();
    for (;;)
    {
        RuntimeUiMessage message;
        if (xQueueReceive(uiQueue, &message, pdMS_TO_TICKS(5)) == pdTRUE)
        {
            dispatchUiMessage(message);
            while (xQueueReceive(uiQueue, &message, 0) == pdTRUE)
                dispatchUiMessage(message);
        }

        const uint32_t currentTick = millis();
        lv_tick_inc(currentTick - previousTick);
        previousTick = currentTick;
        lv_timer_handler();
    }
}

/**
 * Polls physical buttons on a fixed cadence and forwards each change into the
 * runtime UI message queue.
 */
void buttonTask(void *)
{
    waitForTaskStart();
    TickType_t lastWake = xTaskGetTickCount();
    for (;;)
    {
        buttonManager.updateButtons();
        vTaskDelayUntil(&lastWake, BUTTON_POLL_TICKS);
    }
}

/**
 * Refreshes the main menu time display while the main screen is active.
 */
void mainTask(void *)
{
    waitForTaskStart();
    TickType_t lastWake = xTaskGetTickCount();
    for (;;)
    {
        if (mainMenuActive.load())
            postRuntimeUiMessage(RuntimeUiMessageType::RefreshMainTime);
        vTaskDelayUntil(&lastWake, MAIN_REFRESH_TICKS);
    }
}

/**
 * Executes app lifecycle messages such as launch, close, and input events.
 */
void appTask(void *)
{
    waitForTaskStart();
    AppTaskMessage message{};
    for (;;)
    {
        if (xQueueReceive(appQueue, &message, portMAX_DELAY) != pdTRUE)
        {
            Serial.println("[Runtime] Failed to receive app task message");
            continue;
        }

        if (message.type == AppTaskMessageType::Launch)
        {
            if (message.appId == APP_ID_POWER)
                resetPowerMenuState();
            App::executeApp(message.appId);
        }
        else if (message.type == AppTaskMessageType::Close)
            App::executeClose();
        else if (message.appId == targetAppId.load() && message.appId == APP_ID_POWER)
            processPowerMenuInput(static_cast<int8_t>(message.value));
        else if (message.appId == targetAppId.load() && message.appId == APP_ID_TSKMNGR)
            processTaskManagerInput(static_cast<int8_t>(message.value));
    }
}

/**
 * Removes any runtime tasks created during startup so the system can be reset
 * cleanly.
 */
void deleteCreatedTasks()
{
    if (uiTaskHandle != nullptr)
        vTaskDelete(uiTaskHandle);
    if (buttonTaskHandle != nullptr)
        vTaskDelete(buttonTaskHandle);
    if (mainTaskHandle != nullptr)
        vTaskDelete(mainTaskHandle);
    if (appTaskHandle != nullptr)
        vTaskDelete(appTaskHandle);

    uiTaskHandle = nullptr;
    buttonTaskHandle = nullptr;
    mainTaskHandle = nullptr;
    appTaskHandle = nullptr;
}
}

/**
 * Allocates the runtime queues and starts the worker tasks used by the UI,
 * button polling, clock refresh, and app execution pipeline.
 */
bool startRuntimeTasks()
{
    uiQueue = xQueueCreate(UI_QUEUE_LENGTH, sizeof(RuntimeUiMessage));
    appQueue = xQueueCreate(APP_QUEUE_LENGTH, sizeof(AppTaskMessage));
    taskStartGate = xSemaphoreCreateCounting(4, 0);
    uiReady = xSemaphoreCreateBinary();
    if (uiQueue == nullptr || appQueue == nullptr || taskStartGate == nullptr || uiReady == nullptr)
    {
        Serial.println("[Runtime] Failed to allocate task queues or semaphores");
        if (uiQueue != nullptr)
            vQueueDelete(uiQueue);
        if (appQueue != nullptr)
            vQueueDelete(appQueue);
        if (taskStartGate != nullptr)
            vSemaphoreDelete(taskStartGate);
        if (uiReady != nullptr)
            vSemaphoreDelete(uiReady);
        uiQueue = nullptr;
        appQueue = nullptr;
        taskStartGate = nullptr;
        uiReady = nullptr;
        return false;
    }

    BaseType_t result = xTaskCreate(uiTask, "UI", 8192, nullptr, 3, &uiTaskHandle);
    if (result == pdPASS)
        result = xTaskCreate(buttonTask, "Buttons", 3072, nullptr, 2, &buttonTaskHandle);
    if (result == pdPASS)
        result = xTaskCreate(mainTask, "MAIN", 3072, nullptr, 2, &mainTaskHandle);
    if (result == pdPASS)
        result = xTaskCreate(appTask, "APP_EXEC", 4096, nullptr, 1, &appTaskHandle);

    if (result != pdPASS)
    {
        Serial.println("[Runtime] Failed to create FreeRTOS task");
        deleteCreatedTasks();
        vQueueDelete(uiQueue);
        vQueueDelete(appQueue);
        vSemaphoreDelete(taskStartGate);
        vSemaphoreDelete(uiReady);
        uiQueue = nullptr;
        appQueue = nullptr;
        taskStartGate = nullptr;
        uiReady = nullptr;
        return false;
    }

    if (!startBatteryMonitorTask())
    {
        deleteCreatedTasks();
        vQueueDelete(uiQueue);
        vQueueDelete(appQueue);
        vSemaphoreDelete(taskStartGate);
        vSemaphoreDelete(uiReady);
        uiQueue = nullptr;
        appQueue = nullptr;
        taskStartGate = nullptr;
        uiReady = nullptr;
        return false;
    }

    for (UBaseType_t i = 0; i < 4; ++i)
        xSemaphoreGive(taskStartGate);

    if (xSemaphoreTake(uiReady, pdMS_TO_TICKS(10000)) != pdTRUE)
    {
        Serial.println("[Runtime] UI task did not finish initialization");
        return false;
    }
    return true;
}

/**
 * Queues a runtime UI message for processing on the UI task.
 */
bool postRuntimeUiMessage(RuntimeUiMessageType type, uint8_t value)
{
    RuntimeUiMessage message{type, value};
    if (uiQueue == nullptr || xQueueSend(uiQueue, &message, pdMS_TO_TICKS(20)) != pdTRUE)
    {
        Serial.printf("[Runtime] Failed to queue UI message %u\n", static_cast<unsigned>(type));
        return false;
    }
    return true;
}

/**
 * Converts a physical button edge event into the runtime UI message format.
 */
bool postButtonEvent(uint8_t pin, bool pressed)
{
    return postRuntimeUiMessage(
        pressed ? RuntimeUiMessageType::ButtonPressed : RuntimeUiMessageType::ButtonReleased,
        pin);
}

/**
 * Queues a repeat event for a button that remains held down.
 */
bool postButtonDownEvent(uint8_t pin)
{
    return postRuntimeUiMessage(RuntimeUiMessageType::ButtonDown, pin);
}

/**
 * Enqueues a launch request for the app identified by appId.
 */
bool enqueueAppOpen(uint8_t appId)
{
    if (appQueue == nullptr || appId == APP_ID_DEFAULT)
        return false;

    uint8_t expected = NO_APP_ID;
    if (!targetAppId.compare_exchange_strong(expected, appId))
    {
        Serial.printf("[Runtime] App %u launch ignored; app %u is already targeted\n", appId, expected);
        return false;
    }

    AppTaskMessage message{AppTaskMessageType::Launch, appId, 0};
    if (xQueueSend(appQueue, &message, pdMS_TO_TICKS(20)) != pdTRUE)
    {
        targetAppId.store(NO_APP_ID);
        Serial.printf("[Runtime] Failed to queue launch for app %u\n", appId);
        return false;
    }
    return true;
}

/**
 * Queues a request to close the currently active app.
 */
bool enqueueActiveAppClose()
{
    if (appQueue == nullptr || targetAppId.load() == NO_APP_ID)
        return false;

    AppTaskMessage message{AppTaskMessageType::Close, NO_APP_ID, 0};
    if (xQueueSend(appQueue, &message, pdMS_TO_TICKS(20)) != pdTRUE)
    {
        Serial.println("[Runtime] Failed to queue active app close");
        return false;
    }
    return true;
}

/**
 * Forwards app input to the currently active app target.
 */
bool postAppInput(int8_t input)
{
    const uint8_t appId = targetAppId.load();
    if (appQueue == nullptr || appId == NO_APP_ID)
    {
        Serial.println("[Runtime] Cannot route input; no active app target");
        return false;
    }

    AppTaskMessage message{AppTaskMessageType::Input, appId, static_cast<uint8_t>(input)};
    if (xQueueSend(appQueue, &message, pdMS_TO_TICKS(20)) != pdTRUE)
    {
        Serial.printf("[Runtime] Failed to queue input for app %u\n", appId);
        return false;
    }
    return true;
}

/**
 * Updates the global state indicating whether the main menu is currently active.
 */
void setMainMenuActive(bool active)
{
    mainMenuActive.store(active);
}

/**
 * Returns the current main menu state.
 */
bool isMainMenuActive()
{
    return mainMenuActive.load();
}

/**
 * Returns true if the current task is the runtime UI task.
 */
bool isRuntimeUiTask()
{
    return uiTaskHandle != nullptr && xTaskGetCurrentTaskHandle() == uiTaskHandle;
}

/**
 * Clears the active app target when app execution is complete.
 */
void finishAppExecution(uint8_t appId)
{
    uint8_t expected = appId;
    targetAppId.compare_exchange_strong(expected, NO_APP_ID);
}
