#include "timeLabel.h"
#include "fmt.h"

lv_obj_t *lv_timeLabel_header;
lv_style_t t_labelStyle;

void buildHeaderTimeLabel(lv_obj_t *parent)
{
    lv_style_init(&t_labelStyle);

    lv_timeLabel_header = lv_label_create(parent);

    lv_style_set_bg_color(&t_labelStyle, lv_color_black());
    lv_label_set_text(lv_timeLabel_header, "");
    lv_style_set_text_color(&t_labelStyle, lv_color_white());
    lv_style_set_text_font(&t_labelStyle, &fixed6);

    lv_obj_add_style(lv_timeLabel_header, &t_labelStyle, LV_PART_MAIN);

    Serial.println("Built header time label");
}

void setTimeText(DateTime time)
{
    std::string buffer = fmt::format("{: >2}:{:0>2}{}", time.twelveHour(), time.minute(), time.isPM() ? "p" : "a");
    lv_label_set_text(lv_timeLabel_header, buffer.c_str());
}



void setTimeText(String str)
{
    lv_label_set_text(lv_timeLabel_header, str.c_str());
    Serial.println("set text for time");
}
