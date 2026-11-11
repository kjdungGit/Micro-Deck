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


inline uint32_t getRAM_Usage(){
    return ESP.getHeapSize() - ESP.getFreeHeap();
};

inline uint32_t getRAM_Size(){
    return ESP.getHeapSize();
};

inline uint32_t getFlash_Usage(){
    return ESP.getSketchSize();
};

inline float getMCUTemp()
{
    return temperatureRead();
}