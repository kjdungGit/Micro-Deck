#pragma once
#include "component_lib.h"


extern lv_obj_t *lv_header;

void buildBlankHeader(lv_obj_t *parent);
void buildFullHeader();
void toggleMainMenuHeader();
void setHeaderWifiActive(bool active);
void setHeaderBluetoothActive(bool active);