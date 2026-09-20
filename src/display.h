#pragma once

#include "Global.h"
#include <Adafruit_SSD1306.h>

#define SSD1309_I2C_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

extern lv_color_t buf1[(128 * 10) / 8 + 8];
extern lv_display_t *disp;

extern Adafruit_SSD1306 display;

extern void setupDisplay();

void BufferGraphics();

void renderFrame();

void pushToOled(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);