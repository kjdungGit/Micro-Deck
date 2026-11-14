#pragma once
#include "Global.h"
#include "runtime.h"
#include "buttons.h"
#include "Components/mainMenu/screenMainMenu.h"
#include "Image_Assets/Power/Power_Return.h"
#include "App.h"
#include "battery.h"
#include "nvs.h"
#include <RTClib.h>
#include <atomic>
#include <nvs_flash.h>
#include "algorithm"

static lv_obj_t *taskManagerScreen = nullptr;
static lv_obj_t *taskManagerPowerScreen = nullptr;
static lv_obj_t *taskManagerChartFLASH = nullptr;
static lv_obj_t *taskManagerChartRAM = nullptr;
static lv_obj_t *taskManagerChartTEMP = nullptr;
static lv_obj_t *taskManagerChartBattery = nullptr;
static lv_obj_t *taskManagerReturnButton = nullptr;
static lv_obj_t *taskManagerFlashLabel = nullptr;
static lv_obj_t *taskManagerRamLabel = nullptr;
static lv_obj_t *taskManagerTempLabel = nullptr;
static lv_obj_t *taskManagerNvsLabel = nullptr;
static lv_obj_t *taskManagerBatteryLabel = nullptr;
static lv_obj_t *taskManagerPowerHeaderLabel = nullptr;
static lv_obj_t *taskManagerPowerValueLabel = nullptr;
static lv_obj_t *taskManagerPowerBootCountLabel = nullptr;
static lv_obj_t *taskManagerPowerUptimeLabel = nullptr;
static lv_style_t taskManagerChartStyle;
static lv_style_t taskManagerReturnStyle;

static lv_chart_series_t *RAM_Usage_Ser;
static lv_chart_series_t *TEMP_Usage_Ser;
static lv_chart_series_t *BATTERY_Voltage_Ser;

static TaskHandle_t taskManagerRefreshTaskHandle = nullptr;
static std::atomic<bool> taskManagerRefreshActive{false};

static float maxTemperature = 0;
static uint32_t taskManagerBatteryPointCount = 0;
static bool taskManagerPowerActive = false;
static bool taskManagerTransitioning = false;

static constexpr uint32_t TASK_MANAGER_BATTERY_POINT_CAPACITY = 128;
static constexpr int32_t TASK_MANAGER_SCREEN_WIDTH = 128;
static constexpr uint32_t TASK_MANAGER_SCREEN_SLIDE_DURATION_MS = 220;

static void buildTaskManagerUIMain(lv_obj_t *parent)
{
    taskManagerScreen = lv_obj_create(parent);
    lv_obj_set_size(taskManagerScreen, 128, 64);
    lv_obj_set_pos(taskManagerScreen, 0, 0);
    lv_obj_set_style_bg_color(taskManagerScreen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(taskManagerScreen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(taskManagerScreen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(taskManagerScreen, 0, LV_PART_MAIN);
    lv_obj_add_flag(taskManagerScreen, LV_OBJ_FLAG_IGNORE_LAYOUT);

    lv_style_init(&taskManagerChartStyle);
    lv_style_set_bg_color(&taskManagerChartStyle, lv_color_black());
    lv_style_set_bg_opa(&taskManagerChartStyle, LV_OPA_TRANSP);
    lv_style_set_border_color(&taskManagerChartStyle, lv_color_white());
    lv_style_set_border_width(&taskManagerChartStyle, 1);
    lv_style_set_radius(&taskManagerChartStyle, 0);
    lv_style_set_pad_all(&taskManagerChartStyle, 0);

    taskManagerChartFLASH = lv_bar_create(taskManagerScreen);
    lv_obj_set_size(taskManagerChartFLASH, 68, 14);
    lv_obj_set_pos(taskManagerChartFLASH, 4, 17);
    lv_obj_add_style(taskManagerChartFLASH, &taskManagerChartStyle, LV_PART_MAIN);

    lv_bar_set_orientation(taskManagerChartFLASH, LV_BAR_ORIENTATION_HORIZONTAL);
    lv_bar_set_range(taskManagerChartFLASH, 0, 100);
    lv_bar_set_value(taskManagerChartFLASH, 0, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(taskManagerChartFLASH, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(taskManagerChartFLASH, LV_OPA_COVER, LV_PART_INDICATOR);

    taskManagerChartRAM = lv_chart_create(taskManagerScreen);
    lv_obj_set_size(taskManagerChartRAM, 68, 14);
    lv_obj_set_pos(taskManagerChartRAM, 4, 33);
    lv_obj_add_style(taskManagerChartRAM, &taskManagerChartStyle, LV_PART_MAIN);

    lv_chart_set_type(taskManagerChartRAM, LV_CHART_TYPE_LINE);
    lv_chart_set_axis_range(taskManagerChartRAM, LV_CHART_AXIS_PRIMARY_Y, 0, RAM_SIZE_BIT);
    lv_chart_set_point_count(taskManagerChartRAM, 66);
    lv_chart_set_div_line_count(taskManagerChartRAM, 0, 0);
    lv_obj_set_style_line_width(taskManagerChartRAM, 1, LV_PART_ITEMS);
    lv_obj_set_style_width(taskManagerChartRAM, 1, LV_PART_INDICATOR);
    lv_obj_set_style_height(taskManagerChartRAM, 1, LV_PART_INDICATOR);
    RAM_Usage_Ser = lv_chart_add_series(taskManagerChartRAM, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_update_mode(taskManagerChartRAM, LV_CHART_UPDATE_MODE_SHIFT);

    taskManagerChartTEMP = lv_chart_create(taskManagerScreen);
    lv_obj_set_size(taskManagerChartTEMP, 68, 14);
    lv_obj_set_pos(taskManagerChartTEMP, 4, 49);
    lv_obj_add_style(taskManagerChartTEMP, &taskManagerChartStyle, LV_PART_MAIN);

    lv_chart_set_type(taskManagerChartTEMP, LV_CHART_TYPE_LINE);
    lv_chart_set_axis_range(taskManagerChartTEMP, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_point_count(taskManagerChartTEMP, 66);
    lv_chart_set_div_line_count(taskManagerChartTEMP, 0, 0);
    lv_obj_set_style_line_width(taskManagerChartTEMP, 1, LV_PART_ITEMS);
    lv_obj_set_style_width(taskManagerChartTEMP, 1, LV_PART_INDICATOR);
    lv_obj_set_style_height(taskManagerChartTEMP, 1, LV_PART_INDICATOR);
    TEMP_Usage_Ser = lv_chart_add_series(taskManagerChartTEMP, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_update_mode(taskManagerChartTEMP, LV_CHART_UPDATE_MODE_SHIFT);

    taskManagerFlashLabel = lv_label_create(taskManagerScreen);
    taskManagerRamLabel = lv_label_create(taskManagerScreen);
    taskManagerTempLabel = lv_label_create(taskManagerScreen);
    taskManagerNvsLabel = lv_label_create(taskManagerScreen);
    taskManagerBatteryLabel = lv_label_create(taskManagerScreen);
    lv_obj_t *metricLabels[] = {
        taskManagerFlashLabel,
        taskManagerRamLabel,
        taskManagerTempLabel,
        taskManagerNvsLabel,
        taskManagerBatteryLabel};
    const int16_t metricX[] = {77, 77, 77, 77, 24};
    const int16_t metricY[] = {17, 33, 49, 1, 1};
    for (size_t i = 0; i < 5; ++i)
    {
        lv_obj_set_pos(metricLabels[i], metricX[i], metricY[i]);
        lv_obj_set_size(metricLabels[i], 48, 14);
        lv_obj_set_style_text_color(metricLabels[i], lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_text_font(metricLabels[i], &fixed6, LV_PART_MAIN);
    }

    lv_style_init(&taskManagerReturnStyle);
    lv_style_set_bg_color(&taskManagerReturnStyle, lv_color_black());
    lv_style_set_bg_opa(&taskManagerReturnStyle, LV_OPA_TRANSP);
    lv_style_set_border_color(&taskManagerReturnStyle, lv_color_white());
    lv_style_set_border_width(&taskManagerReturnStyle, 1);
    lv_style_set_radius(&taskManagerReturnStyle, 0);
    lv_style_set_pad_all(&taskManagerReturnStyle, 1);

    taskManagerReturnButton = lv_image_create(taskManagerScreen);
    lv_image_set_src(taskManagerReturnButton, &Power_Return);
    lv_obj_set_size(taskManagerReturnButton, 18, 16);
    lv_obj_set_pos(taskManagerReturnButton, 4, 0);
    lv_obj_add_style(taskManagerReturnButton, &taskManagerReturnStyle, LV_PART_MAIN);
}

static void buildTaskManagerUIPower(lv_obj_t *parent)
{
    taskManagerPowerScreen = lv_obj_create(parent);
    lv_obj_set_size(taskManagerPowerScreen, 128, 64);
    lv_obj_set_pos(taskManagerPowerScreen, 0, 0);
    lv_obj_set_style_bg_color(taskManagerPowerScreen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(taskManagerPowerScreen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(taskManagerPowerScreen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(taskManagerPowerScreen, 0, LV_PART_MAIN);
    lv_obj_add_flag(taskManagerPowerScreen, LV_OBJ_FLAG_IGNORE_LAYOUT);

    taskManagerPowerHeaderLabel = lv_label_create(taskManagerPowerScreen);
    lv_obj_set_size(taskManagerPowerHeaderLabel, 128, 16);
    lv_obj_set_pos(taskManagerPowerHeaderLabel, 0, 0);
    lv_obj_set_style_text_color(taskManagerPowerHeaderLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(taskManagerPowerHeaderLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_align(taskManagerPowerHeaderLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(taskManagerPowerHeaderLabel, "BATTERY");

    taskManagerPowerValueLabel = lv_label_create(taskManagerPowerScreen);
    lv_obj_set_size(taskManagerPowerValueLabel, 128, 20);
    lv_obj_set_pos(taskManagerPowerValueLabel, 0, 10);
    lv_obj_set_style_text_color(taskManagerPowerValueLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(taskManagerPowerValueLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_align(taskManagerPowerValueLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    taskManagerPowerBootCountLabel = lv_label_create(taskManagerPowerScreen);
    lv_obj_set_size(taskManagerPowerBootCountLabel, 128, 10);
    lv_obj_set_pos(taskManagerPowerBootCountLabel, 0, 22);
    lv_obj_set_style_text_color(taskManagerPowerBootCountLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(taskManagerPowerBootCountLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_align(taskManagerPowerBootCountLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    taskManagerPowerUptimeLabel = lv_label_create(taskManagerPowerScreen);
    lv_obj_set_size(taskManagerPowerUptimeLabel, 128, 12);
    lv_obj_set_pos(taskManagerPowerUptimeLabel, 0, 36);
    lv_obj_set_style_text_color(taskManagerPowerUptimeLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(taskManagerPowerUptimeLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_align(taskManagerPowerUptimeLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    taskManagerChartBattery = lv_chart_create(taskManagerPowerScreen);
    lv_obj_set_size(taskManagerChartBattery, 128, 10);
    lv_obj_set_pos(taskManagerChartBattery, 0, 54);
    lv_obj_add_style(taskManagerChartBattery, &taskManagerChartStyle, LV_PART_MAIN);
    lv_chart_set_type(taskManagerChartBattery, LV_CHART_TYPE_SCATTER);
    lv_chart_set_axis_range(
        taskManagerChartBattery,
        LV_CHART_AXIS_PRIMARY_X,
        0,
        1);
    lv_chart_set_axis_range(taskManagerChartBattery, LV_CHART_AXIS_PRIMARY_Y, 1600, 2100);
    lv_chart_set_point_count(taskManagerChartBattery, TASK_MANAGER_BATTERY_POINT_CAPACITY);
    lv_chart_set_div_line_count(taskManagerChartBattery, 0, 0);
    lv_obj_set_style_line_width(taskManagerChartBattery, 1, LV_PART_ITEMS);
    lv_obj_set_style_width(taskManagerChartBattery, 1, LV_PART_INDICATOR);
    lv_obj_set_style_height(taskManagerChartBattery, 1, LV_PART_INDICATOR);
    BATTERY_Voltage_Ser = lv_chart_add_series(taskManagerChartBattery, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_all_values(taskManagerChartBattery, BATTERY_Voltage_Ser, LV_CHART_POINT_NONE);
    taskManagerBatteryPointCount = 0;

    lv_obj_add_flag(taskManagerPowerScreen, LV_OBJ_FLAG_HIDDEN);
}

static void formatTaskManagerUptime(uint32_t uptimeMilliseconds, char *buffer, size_t bufferSize)
{
    const uint32_t milliseconds = uptimeMilliseconds % 1000;
    const uint32_t totalSeconds = uptimeMilliseconds / 1000;
    const TimeSpan duration(static_cast<int32_t>(totalSeconds));
    DateTime timeOfDay = DateTime(2000, 1, 1) + duration;
    char timeText[] = "hh-mm-ss";
    timeOfDay.toString(timeText);
    snprintf(
        buffer,
        bufferSize,
        "%d-%s-%03lu",
        static_cast<int>(duration.days()),
        timeText,
        static_cast<unsigned long>(milliseconds));
}

static void updateTaskManagerPowerUI(uint16_t batteryVoltageMillivolts, uint8_t batteryChargePercent)
{
    if (taskManagerPowerScreen == nullptr)
        return;

    lv_label_set_text_fmt(
        taskManagerPowerValueLabel,
        "%umV  %u%%",
        static_cast<unsigned>(batteryVoltageMillivolts),
        static_cast<unsigned>(batteryChargePercent));
    char uptimeText[24];
    formatTaskManagerUptime(millis(), uptimeText, sizeof(uptimeText));
    lv_label_set_text(taskManagerPowerUptimeLabel, uptimeText);

    if (batteryVoltageMillivolts > 0 &&
        taskManagerBatteryPointCount < TASK_MANAGER_BATTERY_POINT_CAPACITY)
    {
        const uint32_t pointIndex = taskManagerBatteryPointCount;
        const int32_t xAxisMax = static_cast<int32_t>(pointIndex > 0 ? pointIndex : 1);
        lv_chart_set_axis_range(taskManagerChartBattery, LV_CHART_AXIS_PRIMARY_X, 0, xAxisMax);
        lv_chart_set_series_value_by_id2(
            taskManagerChartBattery,
            BATTERY_Voltage_Ser,
            pointIndex,
            pointIndex,
            batteryVoltageMillivolts);
        ++taskManagerBatteryPointCount;
        lv_chart_refresh(taskManagerChartBattery);
    }
}

static void setTaskManagerScreenX(void *screen, int32_t x)
{
    lv_obj_set_x(static_cast<lv_obj_t *>(screen), x);
}

static void finishTaskManagerScreenTransition(lv_anim_t *)
{
    lv_obj_t *incomingScreen = taskManagerPowerActive ? taskManagerPowerScreen : taskManagerScreen;
    lv_obj_t *outgoingScreen = taskManagerPowerActive ? taskManagerScreen : taskManagerPowerScreen;
    lv_obj_add_flag(outgoingScreen, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_x(outgoingScreen, 0);
    lv_obj_set_x(incomingScreen, 0);
    taskManagerTransitioning = false;
}

static void navigateTaskManagerScreens(int8_t direction)
{
    configASSERT(isRuntimeUiTask());
    if (direction == 0 || taskManagerTransitioning || taskManagerPowerScreen == nullptr)
        return;

    lv_obj_t *outgoingScreen = taskManagerPowerActive ? taskManagerPowerScreen : taskManagerScreen;
    lv_obj_t *incomingScreen = taskManagerPowerActive ? taskManagerScreen : taskManagerPowerScreen;
    const int32_t slideDirection = direction > 0 ? 1 : -1;

    lv_anim_delete(outgoingScreen, setTaskManagerScreenX);
    lv_anim_delete(incomingScreen, setTaskManagerScreenX);
    lv_obj_clear_flag(incomingScreen, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_x(outgoingScreen, 0);
    lv_obj_set_x(incomingScreen, slideDirection * TASK_MANAGER_SCREEN_WIDTH);
    taskManagerPowerActive = !taskManagerPowerActive;
    taskManagerTransitioning = true;

    lv_anim_t outgoingAnimation;
    lv_anim_init(&outgoingAnimation);
    lv_anim_set_var(&outgoingAnimation, outgoingScreen);
    lv_anim_set_exec_cb(&outgoingAnimation, setTaskManagerScreenX);
    lv_anim_set_values(&outgoingAnimation, 0, -slideDirection * TASK_MANAGER_SCREEN_WIDTH);
    lv_anim_set_duration(&outgoingAnimation, TASK_MANAGER_SCREEN_SLIDE_DURATION_MS);
    lv_anim_set_path_cb(&outgoingAnimation, lv_anim_path_ease_in_out);
    lv_anim_start(&outgoingAnimation);

    lv_anim_t incomingAnimation;
    lv_anim_init(&incomingAnimation);
    lv_anim_set_var(&incomingAnimation, incomingScreen);
    lv_anim_set_exec_cb(&incomingAnimation, setTaskManagerScreenX);
    lv_anim_set_values(&incomingAnimation, slideDirection * TASK_MANAGER_SCREEN_WIDTH, 0);
    lv_anim_set_duration(&incomingAnimation, TASK_MANAGER_SCREEN_SLIDE_DURATION_MS);
    lv_anim_set_path_cb(&incomingAnimation, lv_anim_path_ease_in_out);
    lv_anim_set_completed_cb(&incomingAnimation, finishTaskManagerScreenTransition);
    lv_anim_start(&incomingAnimation);
}

static void processTaskManagerInput(int8_t direction)
{
    if (direction != -1 && direction != 1)
        return;

    postRuntimeUiMessage(
        RuntimeUiMessageType::NavigateTaskManager,
        static_cast<uint8_t>(direction));
}

static void updateGraphs()
{
    configASSERT(isRuntimeUiTask());
    if (!taskManagerRefreshActive.load() || taskManagerScreen == nullptr)
        return;

    const uint32_t flashSize = ESP.getFlashChipSize();
    const uint32_t flashUsage = getFlash_Usage();
    const uint32_t ramSize = getRAM_Size();
    const uint32_t ramUsage = getRAM_Usage();
    const float temperature = getMCUTemp();
    const uint16_t batteryVoltageMillivolts = getBatteryVoltage();
    const uint8_t batteryChargePercent = getBatteryChargePercent();
    const uint32_t flashPercent = flashSize == 0 ? 0 : (static_cast<uint64_t>(flashUsage) * 100) / flashSize;
    const uint32_t ramPercent = ramSize == 0 ? 0 : (static_cast<uint64_t>(ramUsage) * 100) / ramSize;
    nvs_stats_t nvsStats{};
    const esp_err_t nvsStatsResult = nvs_get_stats(nullptr, &nvsStats);

    if(maxTemperature < temperature){
        maxTemperature = temperature;
        lv_chart_set_axis_range(taskManagerChartTEMP, LV_CHART_AXIS_PRIMARY_Y, 0, int(maxTemperature * 10) + 2);
    }

    lv_bar_set_value(taskManagerChartFLASH, flashPercent, LV_ANIM_ON);
    lv_chart_set_next_value(taskManagerChartRAM, RAM_Usage_Ser, ramUsage);
    lv_chart_set_next_value(taskManagerChartTEMP, TEMP_Usage_Ser, temperature * 10);
    updateTaskManagerPowerUI(batteryVoltageMillivolts, batteryChargePercent);
    lv_label_set_text_fmt(taskManagerFlashLabel, "%s %d%%", "ROM", static_cast<int>(flashPercent));
    lv_label_set_text_fmt(taskManagerRamLabel, "%s %d%%", "RAM", static_cast<int>(ramPercent));
    lv_label_set_text_fmt(taskManagerTempLabel, "C° %d", static_cast<int>(temperature));
    lv_label_set_text_fmt(taskManagerBatteryLabel, "B %umV %u%%", static_cast<unsigned>(batteryVoltageMillivolts), static_cast<unsigned>(batteryChargePercent));
    if (nvsStatsResult == ESP_OK && nvsStats.total_entries > 0)
    {
        const uint32_t nvsPercent = static_cast<uint32_t>(
            (static_cast<uint64_t>(nvsStats.used_entries) * 100U) / nvsStats.total_entries);
        lv_label_set_text_fmt(taskManagerNvsLabel, "%s %d%%", "NVS", static_cast<int>(nvsPercent));
    }
    else
    {
        static esp_err_t lastNvsStatsError = ESP_OK;
        if (nvsStatsResult != lastNvsStatsError)
        {
            Serial.printf("[Task Manager] NVS stats unavailable: %d\n", nvsStatsResult);
            lastNvsStatsError = nvsStatsResult;
        }
        lv_label_set_text(taskManagerNvsLabel, "N ERR");
    }
}

static void taskManagerRefreshTask(void *)
{
    App *taskManagerApp = App::getApp(APP_ID_TSKMNGR);
    const TickType_t refreshTicks = pdMS_TO_TICKS(taskManagerApp->getRefreshSpeedMs());

    for (;;)
    {
        if (!taskManagerRefreshActive.load())
        {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            continue;
        }

        postRuntimeUiMessage(RuntimeUiMessageType::UpdateTaskManagerGraphs);
        ulTaskNotifyTake(pdTRUE, refreshTicks);
    }
}

static void startTaskManagerRefreshTask()
{
    if (taskManagerRefreshTaskHandle == nullptr)
    {
        const BaseType_t result = xTaskCreate(
            taskManagerRefreshTask,
            "TaskMgrRefresh",
            2048,
            nullptr,
            1,
            &taskManagerRefreshTaskHandle);
        if (result != pdPASS)
        {
            taskManagerRefreshTaskHandle = nullptr;
            Serial.println("[Task Manager] Failed to create refresh task");
            return;
        }
    }

    taskManagerRefreshActive.store(true);
    xTaskNotifyGive(taskManagerRefreshTaskHandle);
}

static void activateTaskManagerUI()
{
    configASSERT(isRuntimeUiTask());
    if (taskManagerScreen == nullptr)
    {
        buildTaskManagerUIMain(lv_scr_act());
        buildTaskManagerUIPower(lv_scr_act());
    }
    lv_label_set_text_fmt(
        taskManagerPowerBootCountLabel,
        "BOOT %d",
        preferences.getInt("free_boot_count", 0));
    taskManagerPowerActive = false;
    taskManagerTransitioning = false;
    lv_anim_delete(taskManagerScreen, setTaskManagerScreenX);
    lv_anim_delete(taskManagerPowerScreen, setTaskManagerScreenX);
    lv_obj_set_x(taskManagerScreen, 0);
    lv_obj_set_x(taskManagerPowerScreen, 0);
    lv_obj_clear_flag(taskManagerScreen, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(taskManagerPowerScreen, LV_OBJ_FLAG_HIDDEN);

    if (lv_menu_screen != nullptr)
        lv_obj_add_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);

    startTaskManagerRefreshTask();

    if (buttonK3 != nullptr)
    {
        buttonK3->pressedFunction = []()
        { postAppInput(1); };
        buttonK3->releasedFunction = []() {};
        buttonK3->downFunction = []() {};
    }
    if (buttonK2 != nullptr)
    {
        buttonK2->pressedFunction = []()
        { postAppInput(-1); };
        buttonK2->releasedFunction = []() {};
        buttonK2->downFunction = []() {};
    }
    if (buttonK4 != nullptr)
    {
        buttonK4->pressedFunction = []()
        { App::closeActiveApp(); };
        buttonK4->releasedFunction = []() {};
        buttonK4->downFunction = []() {};
    }
}

static void restoreTaskManagerUI()
{
    configASSERT(isRuntimeUiTask());
    taskManagerRefreshActive.store(false);
    if (taskManagerRefreshTaskHandle != nullptr)
        xTaskNotifyGive(taskManagerRefreshTaskHandle);

    lv_anim_delete(taskManagerScreen, setTaskManagerScreenX);
    lv_anim_delete(taskManagerPowerScreen, setTaskManagerScreenX);
    taskManagerTransitioning = false;
    taskManagerPowerActive = false;
    if (taskManagerScreen != nullptr)
    {
        lv_obj_add_flag(taskManagerScreen, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_x(taskManagerScreen, 0);
    }
    if (taskManagerPowerScreen != nullptr)
    {
        lv_obj_add_flag(taskManagerPowerScreen, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_x(taskManagerPowerScreen, 0);
    }
    if (lv_menu_screen != nullptr)
        lv_obj_clear_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);

    initMainMenuButtons(buttonK3, buttonK2, buttonK4);
    setMainMenuActive(true);
}
