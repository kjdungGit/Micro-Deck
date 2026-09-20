#include "bootLabel.h"
#include "fmt.h"

lv_obj_t *lv_bootLabel_header;
lv_style_t b_labelStyle;

void buildHeaderBootLabel(lv_obj_t *parent)
{
    lv_style_init(&b_labelStyle);

    lv_bootLabel_header = lv_label_create(parent);

    lv_style_set_bg_color(&b_labelStyle, lv_color_black());
    lv_label_set_text(lv_bootLabel_header, "NULL");
    lv_style_set_text_color(&b_labelStyle, lv_color_white());
    lv_style_set_text_font(&b_labelStyle, &fixed6);

    lv_label_set_text(lv_bootLabel_header, "NULL");

    lv_obj_add_style(lv_bootLabel_header, &b_labelStyle, LV_PART_MAIN);
    lv_obj_set_style_align(lv_bootLabel_header, LV_ALIGN_LEFT_MID, LV_PART_MAIN);

    Serial.println("Built header time label");
}

void setBoot(int bootNumber){
    lv_label_set_text(lv_bootLabel_header,fmt::format("MD_b-{:0>3}",bootNumber).c_str());
}