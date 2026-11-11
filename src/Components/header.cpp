#include "header.h"
#include "timeLabel.h"
#include "runtime.h"
#include "battery.h"

lv_obj_t *lv_header;
lv_style_t headerStyle;

namespace
{
constexpr int32_t HEADER_HEIGHT = 10;
constexpr uint32_t HEADER_ANIMATION_DURATION_MS = 180;
bool headerShown = false;
bool wifiActive = false;
bool bluetoothActive = false;
lv_obj_t *connectivityStatusLabel = nullptr;
lv_obj_t *batteryStatusLabel = nullptr;

void setHeaderY(void *object, int32_t y)
{
    lv_obj_set_y(static_cast<lv_obj_t *>(object), y);
}

void headerAnimationCompleted(lv_anim_t *animation)
{
    if (animation->end_value < 0)
        lv_obj_add_flag(static_cast<lv_obj_t *>(animation->var), LV_OBJ_FLAG_HIDDEN);
}

void updateConnectivityStatus()
{
    if (connectivityStatusLabel != nullptr)
        lv_label_set_text_fmt(
            connectivityStatusLabel,
            "%c%c",
            wifiActive ? 'W' : ' ',
            bluetoothActive ? 'B' : ' ');
}

void updateBatteryStatus(lv_timer_t *)
{
    if (batteryStatusLabel != nullptr)
        lv_label_set_text_fmt(batteryStatusLabel, "B %u%%", static_cast<unsigned>(getBatteryChargePercent()));
}
}

void buildBlankHeader(lv_obj_t *parent)
{
    lv_style_init(&headerStyle);
    lv_obj_set_style_bg_color(parent, lv_color_black(), LV_PART_MAIN);

    lv_header = lv_obj_create(parent);

    lv_obj_set_size(lv_header, 128, HEADER_HEIGHT);
    lv_obj_set_y(lv_header, -HEADER_HEIGHT);
    lv_style_set_bg_color(&headerStyle, lv_color_black());
    lv_style_set_border_color(&headerStyle, lv_color_white());
    lv_style_set_border_width(&headerStyle, 1);

    lv_style_set_layout(&headerStyle, LV_LAYOUT_FLEX);
    lv_style_set_flex_flow(&headerStyle, LV_FLEX_FLOW_ROW);
    lv_style_set_pad_all(&headerStyle, 1);
    lv_style_set_pad_left(&headerStyle,4);
    lv_style_set_pad_right(&headerStyle,4);

    lv_obj_add_style(lv_header, &headerStyle, LV_PART_MAIN);
    lv_obj_move_to_index(lv_header, 2);

    connectivityStatusLabel = lv_label_create(lv_header);
    lv_obj_set_size(connectivityStatusLabel, 12, HEADER_HEIGHT - 2);
    lv_obj_set_style_text_color(connectivityStatusLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(connectivityStatusLabel, &fixed6, LV_PART_MAIN);
    updateConnectivityStatus();

    batteryStatusLabel = lv_label_create(lv_header);
    lv_obj_set_style_text_color(batteryStatusLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(batteryStatusLabel, &fixed6, LV_PART_MAIN);
    updateBatteryStatus(nullptr);
    lv_timer_create(updateBatteryStatus, 500, nullptr);

    Serial.println("Built base header");
}

void setHeaderWifiActive(bool active)
{
    configASSERT(isRuntimeUiTask());
    wifiActive = active;
    updateConnectivityStatus();
}

void setHeaderBluetoothActive(bool active)
{
    configASSERT(isRuntimeUiTask());
    bluetoothActive = active;
    updateConnectivityStatus();
}

void toggleMainMenuHeader()
{
    configASSERT(isRuntimeUiTask());
    if (lv_header == nullptr || !isMainMenuActive())
        return;

    headerShown = !headerShown;
    lv_anim_delete(lv_header, setHeaderY);

    if (headerShown)
        lv_obj_clear_flag(lv_header, LV_OBJ_FLAG_HIDDEN);

    lv_anim_t animation;
    lv_anim_init(&animation);
    lv_anim_set_var(&animation, lv_header);
    lv_anim_set_exec_cb(&animation, setHeaderY);
    lv_anim_set_values(&animation, lv_obj_get_y(lv_header), headerShown ? 0 : -HEADER_HEIGHT);
    lv_anim_set_duration(&animation, HEADER_ANIMATION_DURATION_MS);
    lv_anim_set_path_cb(&animation, lv_anim_path_ease_in_out);
    lv_anim_set_completed_cb(&animation, headerAnimationCompleted);
    lv_anim_start(&animation);
}

void buildFullHeader()
{
    buildHeaderTimeLabel(lv_header);
}