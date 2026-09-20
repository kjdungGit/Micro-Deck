#pragma once
#include "component_lib.h"
#include "RTClib.h"

void buildHeaderTimeLabel(lv_obj_t *parent);

void setTimeText(DateTime time);
void setTimeText(String str);