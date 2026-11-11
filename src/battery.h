#pragma once

#include <Arduino.h>

/** Starts the global battery monitor task, which averages repeated ADC samples. */
bool startBatteryMonitorTask();
/** Returns the most recently averaged battery voltage in millivolts. */
uint16_t getBatteryVoltage();
/** Returns the estimated battery charge percentage from the averaged voltage. */
uint8_t getBatteryChargePercent();
