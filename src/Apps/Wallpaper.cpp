#include "Wallpaper.h"

#include "App.h"
#include "Global.h"
#include "battery.h"
#include "buttons.h"
#include "clock.h"
#include "Components/header.h"
#include "Components/mainMenu/screenMainMenu.h"
#include "Image_Assets/Wallpaper/Wallpaper_Nazuna.h"
#include "runtime.h"

namespace
{
constexpr int32_t WALLPAPER_WIDTH = 128;
constexpr int32_t WALLPAPER_HEIGHT = 64;
constexpr uint32_t CLOCK_REFRESH_INTERVAL_MS = 1000;

lv_obj_t *wallpaperScreen = nullptr;
lv_obj_t *wallpaperImage = nullptr;
lv_obj_t *wallpaperClockLabel = nullptr;
lv_timer_t *wallpaperTimer = nullptr;
bool wallpaperHeaderWasHidden = true;
bool wallpaperClockVisible = true;
int8_t lastClockSecond = -1;

void setWallpaperClock()
{
    const DateTime now = getNow();
    if (lastClockSecond == static_cast<int8_t>(now.second()))
        return;

    lastClockSecond = static_cast<int8_t>(now.second());
    lv_label_set_text_fmt(
        wallpaperClockLabel,
        "%02u:%02u:%02u %u%%",
        static_cast<unsigned>(now.hour()),
        static_cast<unsigned>(now.minute()),
        static_cast<unsigned>(now.second()),
        static_cast<unsigned>(getBatteryChargePercent()));
}

void wallpaperClockCallback(lv_timer_t *)
{
    setWallpaperClock();
}

void createWallpaperScreen(lv_obj_t *parent)
{
    wallpaperScreen = lv_obj_create(parent);
    if (wallpaperScreen == nullptr)
        return;

    lv_obj_set_size(wallpaperScreen, WALLPAPER_WIDTH, WALLPAPER_HEIGHT);
    lv_obj_set_pos(wallpaperScreen, 0, 0);
    lv_obj_set_style_bg_color(wallpaperScreen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(wallpaperScreen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(wallpaperScreen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(wallpaperScreen, 0, LV_PART_MAIN);
    lv_obj_add_flag(wallpaperScreen, LV_OBJ_FLAG_IGNORE_LAYOUT);

    wallpaperImage = lv_image_create(wallpaperScreen);
    if (wallpaperImage == nullptr)
        return;
    lv_obj_set_size(wallpaperImage, WALLPAPER_WIDTH, WALLPAPER_HEIGHT);
    lv_obj_set_pos(wallpaperImage, 0, 0);
    lv_image_set_src(wallpaperImage, &Wallpaper_Nazuna);

    lv_obj_t *closeLabel = lv_label_create(wallpaperScreen);
    lv_obj_set_pos(closeLabel, 1, 1);
    lv_obj_set_size(closeLabel, 29, 8);
    lv_obj_set_style_text_font(closeLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_color(closeLabel, lv_color_white(), LV_PART_MAIN);
    lv_label_set_text(closeLabel, "k1[x]");

    wallpaperClockLabel = lv_label_create(wallpaperScreen);
    lv_obj_set_size(wallpaperClockLabel, WALLPAPER_WIDTH, 10);
    lv_obj_set_pos(wallpaperClockLabel, 0, 54);
    lv_obj_set_style_text_font(wallpaperClockLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_color(wallpaperClockLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_align(wallpaperClockLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(wallpaperClockLabel, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(wallpaperClockLabel, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_t *clockHelpLabel = lv_label_create(wallpaperScreen);
    lv_obj_set_pos(clockHelpLabel, 85, 1);
    lv_obj_set_size(clockHelpLabel, 42, 8);
    lv_obj_set_style_text_font(clockHelpLabel, &fixed6, LV_PART_MAIN);
    lv_obj_set_style_text_color(clockHelpLabel, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_color(clockHelpLabel, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(clockHelpLabel, LV_OPA_COVER, LV_PART_MAIN);
    lv_label_set_text(clockHelpLabel, "k2[clk]");
}

void bindWallpaperButtons()
{
    buttonK1->pressedFunction = []()
    { App::closeActiveApp(); };
    buttonK1->releasedFunction = []() {};
    buttonK1->downFunction = []() {};
    buttonK2->pressedFunction = []()
    { postAppInput(1); };
    buttonK2->releasedFunction = []() {};
    buttonK2->downFunction = []() {};
    buttonK3->pressedFunction = []()
    { postAppInput(-1); };
    buttonK3->releasedFunction = []() {};
    buttonK3->downFunction = []() {};
    buttonK4->pressedFunction = []()
    { postAppInput(0); };
    buttonK4->releasedFunction = []() {};
    buttonK4->downFunction = []() {};
}
}

bool activateWallpaperUI()
{
    configASSERT(isRuntimeUiTask());
    if (wallpaperScreen == nullptr)
        createWallpaperScreen(lv_scr_act());

    if (wallpaperScreen == nullptr || wallpaperImage == nullptr || wallpaperClockLabel == nullptr)
    {
        Serial.println("[Wallpaper] Failed to create the wallpaper screen");
        return false;
    }

    wallpaperClockVisible = true;
    lastClockSecond = -1;
    setWallpaperClock();
    lv_obj_clear_flag(wallpaperScreen, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(wallpaperClockLabel, LV_OBJ_FLAG_HIDDEN);
    if (lv_menu_screen != nullptr)
        lv_obj_add_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);
    if (lv_header != nullptr)
    {
        wallpaperHeaderWasHidden = lv_obj_has_flag(lv_header, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(lv_header, LV_OBJ_FLAG_HIDDEN);
    }

    if (wallpaperTimer == nullptr)
        wallpaperTimer = lv_timer_create(wallpaperClockCallback, CLOCK_REFRESH_INTERVAL_MS, nullptr);
    if (wallpaperTimer == nullptr)
    {
        Serial.println("[Wallpaper] Failed to create the wallpaper clock timer");
        lv_obj_add_flag(wallpaperScreen, LV_OBJ_FLAG_HIDDEN);
        return false;
    }

    bindWallpaperButtons();
    return true;
}

void restoreWallpaperUI()
{
    configASSERT(isRuntimeUiTask());
    if (wallpaperTimer != nullptr)
    {
        lv_timer_delete(wallpaperTimer);
        wallpaperTimer = nullptr;
    }

    if (wallpaperScreen != nullptr)
        lv_obj_add_flag(wallpaperScreen, LV_OBJ_FLAG_HIDDEN);
    if (lv_menu_screen != nullptr)
        lv_obj_clear_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);
    if (lv_header != nullptr && !wallpaperHeaderWasHidden)
        lv_obj_clear_flag(lv_header, LV_OBJ_FLAG_HIDDEN);

    if (buttonK1 != nullptr)
    {
        buttonK1->pressedFunction = []()
        { toggleMainMenuHeader(); };
        buttonK1->releasedFunction = []() {};
        buttonK1->downFunction = []() {};
    }
    initMainMenuButtons(buttonK3, buttonK2, buttonK4);
    setMainMenuActive(true);
}

void processWallpaperInput(int8_t direction)
{
    postRuntimeUiMessage(
        RuntimeUiMessageType::WallpaperInput,
        static_cast<uint8_t>(direction));
}

void processWallpaperUiInput(int8_t direction)
{
    configASSERT(isRuntimeUiTask());
    if (direction != 1 || wallpaperClockLabel == nullptr)
        return;

    wallpaperClockVisible = !wallpaperClockVisible;
    if (wallpaperClockVisible)
        lv_obj_clear_flag(wallpaperClockLabel, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(wallpaperClockLabel, LV_OBJ_FLAG_HIDDEN);
}
