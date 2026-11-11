#pragma once
#include "Global.h"
#include "runtime.h"
#include "buttons.h"
#include "Components/mainMenu/screenMainMenu.h"
#include "Image_Assets/Power/Power_Return.h"
#include "App.h"
#include "battery.h"
#include <atomic>
#include <nvs_flash.h>

static lv_obj_t *taskManagerScreen = nullptr;
static lv_obj_t *taskManagerChartFLASH = nullptr;
static lv_obj_t *taskManagerChartRAM = nullptr;
static lv_obj_t *taskManagerChartTEMP = nullptr;
static lv_obj_t *taskManagerReturnButton = nullptr;
static lv_obj_t *taskManagerFlashLabel = nullptr;
static lv_obj_t *taskManagerRamLabel = nullptr;
static lv_obj_t *taskManagerTempLabel = nullptr;
static lv_obj_t *taskManagerNvsLabel = nullptr;
static lv_obj_t *taskManagerBatteryLabel = nullptr;
static lv_style_t taskManagerChartStyle;
static lv_style_t taskManagerReturnStyle;

static lv_chart_series_t *RAM_Usage_Ser;
static lv_chart_series_t *TEMP_Usage_Ser;

static TaskHandle_t taskManagerRefreshTaskHandle = nullptr;
static std::atomic<bool> taskManagerRefreshActive{false};

static void buildTaskManagerUI(lv_obj_t *parent)
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

static void updateGraphs()
{
    configASSERT(isRuntimeUiTask());
    if (!taskManagerRefreshActive.load() || taskManagerScreen == nullptr)
        return;

    const uint32_t flashSize = ESP.getFlashChipSize();
    const uint32_t flashUsage = getFlash_Usage();
    const uint32_t ramSize = getRAM_Size();
    const uint32_t ramUsage = getRAM_Usage();
    const int32_t temperature = static_cast<int32_t>(getMCUTemp());
    const uint16_t batteryVoltageMillivolts = getBatteryVoltage();
    const uint8_t batteryChargePercent = getBatteryChargePercent();
    const uint32_t flashPercent = flashSize == 0 ? 0 : (static_cast<uint64_t>(flashUsage) * 100) / flashSize;
    const uint32_t ramPercent = ramSize == 0 ? 0 : (static_cast<uint64_t>(ramUsage) * 100) / ramSize;
    nvs_stats_t nvsStats{};
    const esp_err_t nvsStatsResult = nvs_get_stats(nullptr, &nvsStats);

    lv_bar_set_value(taskManagerChartFLASH, flashPercent, LV_ANIM_OFF);
    lv_chart_set_next_value(taskManagerChartRAM, RAM_Usage_Ser, ramUsage);
    lv_chart_set_next_value(taskManagerChartTEMP, TEMP_Usage_Ser, temperature);
    lv_label_set_text_fmt(taskManagerFlashLabel, "%s %d%%", "ROM", static_cast<int>(flashPercent));
    lv_label_set_text_fmt(taskManagerRamLabel, "%s %d%%", "RAM", static_cast<int>(ramPercent));
    lv_label_set_text_fmt(taskManagerTempLabel, "C° %d", static_cast<int>(temperature));
    lv_label_set_text_fmt(taskManagerBatteryLabel, "B %umV %u%%", static_cast<unsigned>(batteryVoltageMillivolts), static_cast<unsigned>(batteryChargePercent));
    if (nvsStatsResult == ESP_OK && nvsStats.total_entries > 0)
    {
        const uint32_t nvsPercent = static_cast<uint32_t>(
            (static_cast<uint64_t>(nvsStats.used_entries) * 100U) / nvsStats.total_entries);
        lv_label_set_text_fmt(taskManagerNvsLabel, "%c %d%%", 'NVS', static_cast<int>(nvsPercent));
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
        buildTaskManagerUI(lv_scr_act());
    else
        lv_obj_clear_flag(taskManagerScreen, LV_OBJ_FLAG_HIDDEN);

    if (lv_menu_screen != nullptr)
        lv_obj_add_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);

    startTaskManagerRefreshTask();

    if (buttonK3 != nullptr)
        buttonK3->pressedFunction = []() {};
    if (buttonK2 != nullptr)
        buttonK2->pressedFunction = []() {};
    if (buttonK4 != nullptr)
        buttonK4->pressedFunction = []()
        { App::closeActiveApp(); };
}

static void restoreTaskManagerUI()
{
    configASSERT(isRuntimeUiTask());
    taskManagerRefreshActive.store(false);
    if (taskManagerRefreshTaskHandle != nullptr)
        xTaskNotifyGive(taskManagerRefreshTaskHandle);

    if (taskManagerScreen != nullptr)
        lv_obj_add_flag(taskManagerScreen, LV_OBJ_FLAG_HIDDEN);
    if (lv_menu_screen != nullptr)
        lv_obj_clear_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);

    initMainMenuButtons(buttonK3, buttonK2, buttonK4);
    setMainMenuActive(true);
}
