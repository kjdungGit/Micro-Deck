#pragma once
#include <Arduino.h>
#include <lvgl.h>

#define BAT_DIV_PIN D1

#define K1_PIN D10
#define K2_PIN D2
#define K3_PIN D3
#define K4_PIN D6

#define SDA_PIN D4
#define SCL_PIN D5

extern bool mainMenuActive;

extern long millisSinceGraphicsRefresh;