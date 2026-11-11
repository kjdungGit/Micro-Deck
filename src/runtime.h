#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include "app_ids.h"

enum class RuntimeUiMessageType : uint8_t
{
    ButtonPressed,
    ButtonDown,
    ButtonReleased,
    RefreshMainTime,
    OpenApp,
    CloseActiveApp,
    UpdatePowerSelection,
    EnterSleep
};

struct RuntimeUiMessage
{
    RuntimeUiMessageType type;
    uint8_t value;
};

bool startRuntimeTasks();
bool postRuntimeUiMessage(RuntimeUiMessageType type, uint8_t value = 0);
bool postButtonEvent(uint8_t pin, bool pressed);
bool postButtonDownEvent(uint8_t pin);
bool enqueueAppOpen(uint8_t appId);
bool enqueueActiveAppClose();
bool postAppInput(int8_t input);
void setMainMenuActive(bool active);
bool isMainMenuActive();
bool isRuntimeUiTask();
void finishAppExecution(uint8_t appId);
void activatePowerScreenUI();
void restoreMainScreenUI();
void setPowerSelectionUI(uint8_t selection);
void resetPowerMenuState();
void processPowerMenuInput(int8_t direction);
