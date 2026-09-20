#include "display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
lv_color_t buf1[(128 * 10) / 8 + 8];
lv_display_t *disp;
long millisSinceGraphicsRefresh = 0;

void setDisplayBrightnessPercent(uint8_t percent) {
    // Constrain input between 0 and 100
    percent = constrain(percent, 0, 100);

    // 1. Map 0-100% to main contrast register (1 to 255)
    // We stop at 1 so the screen doesn't turn off completely at 0%
    uint8_t contrast = map(percent, 0, 100, 1, 255);
    uint8_t precharge = (percent < 30) ? 0x11 : 0x22;
    uint8_t vcomh = map(percent, 0, 100, 0x00, 0x30);

    // Set Contrast
    display.ssd1306_command(SSD1306_SETCONTRAST);     
    display.ssd1306_command(contrast); 

    // Set Pre-charge Period
    display.ssd1306_command(SSD1306_SETPRECHARGE);      
    display.ssd1306_command(precharge); 

    // Set VCOMH Level
    display.ssd1306_command(SSD1306_SETVCOMDETECT);      
    display.ssd1306_command(vcomh);
}

void setupDisplay()
{

    if (!display.begin(SSD1306_EXTERNALVCC, SSD1309_I2C_ADDR)) {
        Serial.println("Failed to Grab display");
        return;
    } else {
        Serial.println("Grabbed display");
    }
    display.ssd1306_command(SSD1306_DISPLAYON);
    display.display();
}

void pushToOled(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    // Skip the 8-byte palette header for I1 format
    px_map += 8;

    int32_t w = lv_area_get_width(area);

    for (int32_t y = area->y1; y <= area->y2; y++) {
        for (int32_t x = area->x1; x <= area->x2; x++) {
            int32_t local_x = x - area->x1;
            int32_t local_y = y - area->y1;

            int32_t byte_index = (local_y * ((w + 7) / 8)) + (local_x / 8);
            int32_t bit_index = 7 - (local_x % 8);

            bool pixel_on = (px_map[byte_index] >> bit_index) & 0x01;

            display.drawPixel(x, y, pixel_on ? SSD1306_WHITE : SSD1306_BLACK);
        }
    }

    if (lv_display_flush_is_last(disp)) {
        display.display();
    }

    lv_display_flush_ready(disp);
}