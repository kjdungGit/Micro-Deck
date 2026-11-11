#pragma once
#include "Components/component_lib.h"
#include "RTClib.h"

class Button;

extern lv_obj_t *lv_app_image;

extern lv_obj_t *lv_menu_screen;

enum MenuDirections
{
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
    SELECT = 5
};

void buildMenuScreen(lv_obj_t *parent);
void setMenu_TimeLabelInformation(DateTime time);

void traverseMenu(unsigned int direction);
void resetMenuNavigation();

void initMainMenuButtons(Button *up, Button *down, Button *select);