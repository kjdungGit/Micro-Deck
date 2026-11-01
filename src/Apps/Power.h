#pragma once
#include "Global.h"
#include "daemon.h"
#include "buttons.h"
#include "sleep.h"
#include "Components/mainMenu/screenMainMenu.h"
#include "Image_Assets/Power/Power_Sleep.h"
#include "Image_Assets/Power/Power_Shut.h"
#include "Image_Assets/Power/Power_Return.h"
#include "App.h"

bool enabled;

enum class PowerMenuDirections
{
    LEFT = -1,
    SELECT = 0,
    RIGHT = 1
};

lv_obj_t *lv_power_screen;
lv_style_t powerScreenStyle;

lv_obj_t *lv_sleep_power;
lv_obj_t *lv_shut_power;
lv_obj_t *lv_return_power;
lv_obj_t *lv_selection_label;

lv_style_t powerButtonMainStyle;
lv_style_t powerButtonSelectStyle;
lv_style_t powerLabelStyle;

byte selection;
LoopDaemon *powerDaemon = nullptr;

void buildPowerbutton(lv_obj_t *obj)
{
    Serial.printf("[Power] Configuring button %p\n", obj);
    lv_obj_set_size(obj, 24, 24);
    lv_obj_add_style(obj, &powerButtonMainStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(obj, &powerButtonSelectStyle, LV_STATE_HOVERED);
}

void buildSelectionLabel()
{
    lv_selection_label = lv_label_create(lv_power_screen);
    lv_style_init(&powerLabelStyle);
    lv_obj_set_flag(lv_selection_label, LV_OBJ_FLAG_IGNORE_LAYOUT, true);

    lv_style_set_text_align(&powerLabelStyle, LV_TEXT_ALIGN_CENTER);
    lv_style_set_border_width(&powerLabelStyle, 0);
    lv_style_set_text_font(&powerLabelStyle, &fixed6);
    lv_style_set_text_color(&powerLabelStyle, lv_color_white()); 

    lv_obj_set_size(lv_selection_label, 50, 16);
    lv_obj_set_pos(lv_selection_label,64-25, 20);

    lv_obj_add_style(lv_selection_label, &powerLabelStyle, LV_PART_MAIN);
}

void buildMenu(lv_obj_t *parent)
{
    Serial.printf("[Power] Building power screen on parent %p\n", parent);
    lv_power_screen = lv_obj_create(parent);

    lv_obj_set_size(lv_power_screen, 128, 64);
    lv_obj_set_pos(lv_power_screen, 0, 0);
    lv_obj_set_layout(lv_power_screen, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(lv_power_screen, LV_FLEX_FLOW_ROW_REVERSE);

    lv_style_init(&powerScreenStyle);

    lv_style_set_bg_color(&powerScreenStyle, lv_color_black());
    lv_style_set_radius(&powerScreenStyle, 0);
    lv_style_set_border_width(&powerScreenStyle, 0);
    lv_style_set_pad_hor(&powerScreenStyle, 20);
    lv_style_set_pad_ver(&powerScreenStyle, 50);
    lv_obj_add_style(lv_power_screen, &powerScreenStyle, LV_PART_MAIN);

    lv_style_init(&powerButtonMainStyle);

    lv_style_set_bg_color(&powerButtonMainStyle, lv_color_black());
    lv_style_set_border_color(&powerButtonMainStyle, lv_color_white());
    lv_style_set_border_width(&powerButtonMainStyle, 1);
    lv_style_set_radius(&powerButtonMainStyle, 2);

    lv_style_init(&powerButtonSelectStyle);
    lv_style_copy(&powerButtonSelectStyle, &powerButtonMainStyle);
    lv_style_set_border_width(&powerButtonSelectStyle, 3);
    lv_style_set_radius(&powerButtonSelectStyle, 4);

    lv_sleep_power = lv_image_create(lv_power_screen);
    lv_shut_power = lv_image_create(lv_power_screen);
    lv_return_power = lv_image_create(lv_power_screen);
    lv_image_set_src(lv_return_power, &Power_Return);
    lv_image_set_src(lv_sleep_power, &Power_Sleep);
    lv_image_set_src(lv_shut_power, &Power_Shut);
    Serial.println("[Power] Image sources assigned: return, sleep, shut");
    buildPowerbutton(lv_sleep_power);
    buildPowerbutton(lv_shut_power);
    buildPowerbutton(lv_return_power);
    lv_obj_set_size(lv_return_power, 18, 18);

    buildSelectionLabel();
}

void closePowerMenu()
{
    enabled = false;
    if (lv_power_screen != nullptr)
        lv_obj_add_flag(lv_power_screen, LV_OBJ_FLAG_HIDDEN);
    if (lv_menu_screen != nullptr)
        lv_obj_clear_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);
    if (powerDaemon != nullptr)
        powerDaemon->enabled = false;
    initMainMenuButtons(buttonK2, buttonK3, buttonK4);
    setMainMenuActive(true);
}

void traversePowerMenu(int direction)
{
    Serial.printf("[Power] Menu input direction=%d selection=%u enabled=%s\n",
                  direction, selection, enabled ? "true" : "false");
    if (!direction)
    {
        switch (selection)
        {
        case 0:
            Serial.println("[Power] Return selected");
            App::closeActiveApp();
            break;
        case 1:
            Serial.println("[Power] Light sleep selected");
            App::closeActiveApp();
            goToSleep(SleepStyle::ESP_SLEEP_LIGHT);
            break;
        case 2:
            Serial.println("[Power] Deep sleep selected");
            App::closeActiveApp();
            goToSleep(SleepStyle::ESP_SLEEP_DEEP);
            break;
        }
        return;
    }
    int transform = direction + 3; // make sure a buffer is in place so unsigned arithmetic doesn't break modulus operation
    selection = ((int8_t)selection + transform) % 3;
    Serial.printf("[Power] Selection changed to %u\n", selection);

    lv_obj_t *buttons[] = {lv_return_power, lv_sleep_power, lv_shut_power};
    for (int i = 0; i < 3; i++)
    {
        lv_obj_set_state(buttons[i], LV_STATE_HOVERED, selection == i);
        lv_obj_set_state(buttons[i], LV_STATE_DEFAULT, selection != i);
    }


    switch (selection)
    {
    case 0:
        lv_label_set_text(lv_selection_label, "Return");
        break;
    case 1:
        lv_label_set_text(lv_selection_label, "Sleep");
        break;
    case 2:
        lv_label_set_text(lv_selection_label, "Power Off");
        break;
    }
}

void clearButtons(Button **objs, int count)
{
    for (int i = 0; i < count; i++)
    {
        objs[i]->pressedFunction = []() {};
        objs[i]->releasedFunction = []() {};
        objs[i]->downFunction = []() {};
    }
}

void assignButtons(Button &left, Button &right, Button &select)
{
    Serial.printf("[Power] Assigning buttons left=%p right=%p select=%p\n", &left, &right, &select);
    Button *buttons[] = {&left, &right, &select};
    clearButtons(buttons, 3);

    left.pressedFunction = []()
    { traversePowerMenu(static_cast<int>(PowerMenuDirections::LEFT)); };
    right.pressedFunction = []()
    { traversePowerMenu(static_cast<int>(PowerMenuDirections::RIGHT)); };
    select.pressedFunction = []()
    { traversePowerMenu(static_cast<int>(PowerMenuDirections::SELECT)); };
}

void Power_exec()
{
    Serial.printf("[Power] Exec begin enabled=%s screen=%p daemon=%p\n",
                  enabled ? "true" : "false", lv_power_screen, powerDaemon);
    enabled = true;
    setMainMenuActive(false);
    if (lv_power_screen == nullptr)
        buildMenu(lv_scr_act());
    else
    {
        Serial.println("[Power] Reusing existing power screen");
        lv_obj_clear_flag(lv_power_screen, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_add_flag(lv_menu_screen, LV_OBJ_FLAG_HIDDEN);
    selection = 0;
    lv_obj_set_state(lv_return_power, LV_STATE_HOVERED, true);
    lv_obj_set_state(lv_sleep_power, LV_STATE_HOVERED, false);
    lv_obj_set_state(lv_shut_power, LV_STATE_HOVERED, false);
    assignButtons(*buttonK2, *buttonK3, *buttonK4);
    Serial.println("[Power] Main menu hidden and power buttons assigned");

    if (powerDaemon == nullptr)
    {
        Serial.println("[Power] Creating power daemon");
        powerDaemon = daemonManager.add("PowerDisplay", 30, []()
                                        {
        static bool lastEnabled = false;
        if (enabled != lastEnabled)
        {
            Serial.printf("[Power] Daemon state changed: enabled=%s\n", enabled ? "true" : "false");
            lastEnabled = enabled;
        }
        if(!enabled){
            Serial.println("[Power] Daemon restoring main menu");
            setMainMenuActive(true);
            if (powerDaemon != nullptr)
                powerDaemon->enabled = false;
        } });
    }
    powerDaemon->enabled = true;
    Serial.printf("[Power] Exec complete daemon=%p enabled=%s\n",
                  powerDaemon, powerDaemon->enabled ? "true" : "false");
}