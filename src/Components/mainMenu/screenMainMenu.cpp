#include "screenMainMenu.h"
#include "Image_Assets/MenuTree.h"
#include "Apps/App.h"
#include "buttons.h"
#include "fmt.h"
#include <stdexcept>

lv_obj_t *lv_menu_screen;
lv_style_t menuStyle;
lv_obj_t *lv_time_text;
lv_style_t menuTimeStyle;
lv_obj_t *lv_date_text;
lv_style_t menuDateStyle;
lv_obj_t *menuImagePane;

lv_obj_t *lv_app_select;
lv_style_t menuAppSelectStyle;
lv_obj_t *lv_app_select_labels[3];
lv_style_t menuAppSelectLabelStyles[3];

int currentAppSelection = 0;

bool showBorders = 0;

void initDateTimeLabels(lv_obj_t *parent)
{
    lv_time_text = lv_label_create(parent);
    lv_obj_set_height(lv_time_text, 20);

    lv_style_init(&menuTimeStyle);
    lv_style_set_margin_all(&menuTimeStyle, -3);
    lv_style_set_margin_left(&menuTimeStyle, 5);
    lv_style_set_bg_opa(&menuTimeStyle, LV_OPA_TRANSP);
    lv_style_set_text_color(&menuTimeStyle, lv_color_white());
    lv_style_set_text_font(&menuTimeStyle, &slacksideOne20);
    lv_style_set_border_color(&menuTimeStyle, lv_color_white());
    lv_style_set_border_width(&menuTimeStyle, showBorders ? 1 : 0);

    lv_obj_add_style(lv_time_text, &menuTimeStyle, LV_PART_MAIN);

    lv_date_text = lv_label_create(parent);
    lv_obj_set_height(lv_date_text, 14);

    lv_style_init(&menuDateStyle);
    lv_style_set_margin_all(&menuDateStyle, 0);
    lv_style_set_margin_left(&menuDateStyle, 7);
    lv_style_set_bg_opa(&menuDateStyle, LV_OPA_TRANSP);
    lv_style_set_text_color(&menuDateStyle, lv_color_white());
    lv_style_set_text_font(&menuDateStyle, &slacksideOne14);
    lv_style_set_border_color(&menuDateStyle, lv_color_white());
    lv_style_set_border_width(&menuDateStyle, showBorders ? 1 : 0);

    lv_obj_add_style(lv_date_text, &menuDateStyle, LV_PART_MAIN);
}

void setMenu_TimeLabelInformation(DateTime time)
{
    lv_label_set_text(lv_time_text, fmt::format("{: >2}:{:0>2}{}", time.twelveHour(), time.minute(), time.isPM() ? "pm" : "am").c_str());
    String months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    String days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    lv_label_set_text(lv_date_text, fmt::format("{}, {}. {}", time.day(), days[time.dayOfTheWeek()], months[time.month() - 1]).c_str());
}

void buildMenuImage(lv_obj_t *parent)
{

    menuImagePane = lv_image_create(parent);
    lv_image_set_src(menuImagePane, &menuTree);
    lv_obj_set_size(menuImagePane, 46, 64);
    lv_obj_set_style_border_color(menuImagePane, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_image_recolor(menuImagePane, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_image_recolor_opa(menuImagePane, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_pos(menuImagePane, 128 - 46, 0);
}

void initAppSelection(lv_obj_t *parent)
{
    lv_app_select = lv_obj_create(parent);
    lv_style_init(&menuAppSelectStyle);

    lv_style_set_bg_color(&menuAppSelectStyle, lv_color_black());
    lv_style_set_radius(&menuAppSelectStyle, 0);
    lv_style_set_border_width(&menuAppSelectStyle, showBorders ? 1 : 0);

    // height fits text, a pixel above/below for padding, and a pixel for border
    lv_obj_set_size(lv_app_select, 50, 3 * (fixed6.line_height + 2 + 2));
    lv_obj_set_layout(lv_app_select, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(lv_app_select, LV_FLEX_FLOW_COLUMN);

    lv_obj_add_style(lv_app_select, &menuAppSelectStyle, LV_PART_MAIN);
    lv_style_set_pad_all(&menuAppSelectStyle, -1);
    lv_style_set_pad_row(&menuAppSelectStyle, -1);

    lv_style_set_margin_all(&menuAppSelectStyle, 0);

    lv_style_t menuAppSelectLabelStyle;
    lv_style_init(&menuAppSelectLabelStyle);

    lv_style_set_text_font(&menuAppSelectLabelStyle, &fixed6);
    lv_style_set_text_color(&menuAppSelectLabelStyle, lv_color_white());
    lv_style_set_bg_color(&menuAppSelectLabelStyle, lv_color_black());
    lv_style_set_border_color(&menuAppSelectLabelStyle, lv_color_white());
    lv_style_set_border_width(&menuAppSelectLabelStyle, showBorders ? 2 : 1);
    lv_style_set_margin_left(&menuAppSelectLabelStyle, 8);
    lv_style_set_pad_left(&menuAppSelectLabelStyle, 3);
    lv_style_set_radius(&menuAppSelectLabelStyle, 0);

    for (int i = 0; i < 3; i++)
    {
        lv_style_copy(&menuAppSelectLabelStyles[i], &menuAppSelectLabelStyle);
        if (!showBorders)
        { // Apply custom bordering to every border if there is no overriding border showing
            switch (i)
            {
            case 0:
                lv_style_set_border_side(&menuAppSelectLabelStyles[i], static_cast<lv_border_side_t>(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT));
                break;
            case 1:
                lv_style_set_border_side(&menuAppSelectLabelStyles[i], static_cast<lv_border_side_t>(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT));
                break;
            case 2:
                lv_style_set_border_side(&menuAppSelectLabelStyles[i], static_cast<lv_border_side_t>(LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT));
                break;
            }
        }

        lv_app_select_labels[i] = lv_label_create(lv_app_select);
        lv_obj_set_height(lv_app_select_labels[i], fixed6.line_height + 2 + 1);
        lv_obj_set_width(lv_app_select_labels[i], 35);

        lv_obj_add_style(lv_app_select_labels[i], &menuAppSelectLabelStyles[i], LV_PART_MAIN);
        lv_label_set_text(lv_app_select_labels[i], "APP");
    }
    traverseMenu(0); // initialize the menu without changing selection
}

void buildMenuScreen(lv_obj_t *parent)
{

    // inits
    lv_menu_screen = lv_obj_create(parent);
    lv_style_init(&menuStyle);

    // manual size/pos
    // set height now, let padding/sizing be autobuild by lvgl grid, set the width to that
    lv_obj_set_size(lv_menu_screen, 80, 64);
    lv_obj_set_pos(lv_menu_screen, 0, 0);

    // style
    lv_style_set_bg_color(&menuStyle, lv_color_black());
    lv_style_set_radius(&menuStyle, 0);
    lv_style_set_border_width(&menuStyle, showBorders ? 1 : 0);
    lv_style_set_pad_all(&menuStyle, 0);
    lv_style_set_pad_row(&menuStyle, 0);

    lv_obj_add_style(lv_menu_screen, &menuStyle, LV_PART_MAIN);

    // flags
    lv_obj_add_flag(lv_menu_screen, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_set_layout(lv_menu_screen, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(lv_menu_screen, LV_FLEX_FLOW_COLUMN);

    buildMenuImage(parent);

    lv_time_text = lv_label_create(lv_menu_screen);

    initDateTimeLabels(lv_menu_screen);
    initAppSelection(lv_menu_screen);

    lv_obj_move_foreground(menuImagePane);
}

void traverseMenu(unsigned int direction)
{
    if (App::AppCount == 0)
    {
        currentAppSelection = 0;
        for (lv_obj_t *label : lv_app_select_labels)
            lv_label_set_text(label, "NO APPS");
        return;
    }

    Serial.println(currentAppSelection);

    switch (direction)
    {
    case MenuDirections::UP:
        currentAppSelection--;
        break;

    case MenuDirections::DOWN:
        currentAppSelection++;
        break;

    case MenuDirections::SELECT:

        App *selectedApp = App::getApp(App::getAppIDatIndex(currentAppSelection));
        Serial.printf("Launching app: %s\n", selectedApp->getName().c_str());
        App::openApp(static_cast<byte>(selectedApp->getID()));
        break;

    }//In the case of a default statement, nothing happens, but the function continues for the case that we want to refresh the menu without a direction change.

    currentAppSelection = (currentAppSelection + App::AppCount) % App::AppCount; // wrap

    for (int i = -1; i < 2; i++)
    {
        int index_of_target = ((currentAppSelection + i) + App::AppCount) % App::AppCount;

        try
        {
            Serial.printf("Setting label %d to app index %d\n", i + 1, index_of_target);
            lv_label_set_text(lv_app_select_labels[i + 1], App::getApp(App::getAppIDatIndex(index_of_target))->getName().c_str());
        }
        catch (const std::out_of_range &e)
        {
            lv_label_set_text(lv_app_select_labels[i + 1], "APP");
        }
    }
}

void resetMenuNavigation()
{
    currentAppSelection = 0;
    traverseMenu(0);
}

void initMainMenuButtons(Button *up, Button *down, Button *select)
{
    up->pressedFunction = []()
    { traverseMenu(MenuDirections::UP); };
    down->pressedFunction = []()
    { traverseMenu(MenuDirections::DOWN); };
    select->pressedFunction = []()
    { traverseMenu(MenuDirections::SELECT); };
}