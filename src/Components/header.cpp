#include "header.h"
#include "timeLabel.h"

lv_obj_t *lv_header;
lv_style_t headerStyle;

void buildBlankHeader(lv_obj_t *parent)
{
    lv_style_init(&headerStyle);
    lv_obj_set_style_bg_color(parent, lv_color_black(), LV_PART_MAIN);

    lv_header = lv_obj_create(parent);

    lv_obj_set_size(lv_header, 128, 10);
    lv_style_set_bg_color(&headerStyle, lv_color_black());
    lv_style_set_border_color(&headerStyle, lv_color_white());
    lv_style_set_border_width(&headerStyle, 1);
    // lv_obj_add_flag(lv_header, LV_OBJ_FLAG_IGNORE_LAYOUT);

    lv_style_set_layout(&headerStyle, LV_LAYOUT_FLEX);
    lv_style_set_flex_flow(&headerStyle, LV_FLEX_FLOW_ROW);
    lv_style_set_pad_all(&headerStyle, 1);
    lv_style_set_pad_left(&headerStyle,4);
    lv_style_set_pad_right(&headerStyle,4);

    lv_obj_add_style(lv_header, &headerStyle, LV_PART_MAIN);
    lv_obj_move_to_index(lv_header, 2);

    Serial.println("Built base header");
}

void buildFullHeader()
{
    buildHeaderTimeLabel(lv_header);
}