#include "battery.h"

#include <atomic>

#include "Global.h"

namespace
{
constexpr uint32_t BATTERY_SAMPLE_COUNT = 8;
constexpr TickType_t BATTERY_SAMPLE_DELAY = pdMS_TO_TICKS(20);
constexpr TickType_t BATTERY_UPDATE_DELAY = pdMS_TO_TICKS(500);

std::atomic<uint16_t> averagedVoltageMillivolts{0};
std::atomic<uint8_t> chargePercent{0};
TaskHandle_t batteryMonitorTaskHandle = nullptr;

float estimateChargePercent(uint16_t voltageMillivolts)
{
    const float voltage = voltageMillivolts * 2.0f / 1000.0f;
    static constexpr float volts[] = {
        3.00f, 3.30f, 3.50f, 3.60f, 3.70f, 3.75f,
        3.80f, 3.85f, 3.90f, 4.00f, 4.10f, 4.20f};
    static constexpr float percents[] = {
        0.0f, 5.0f, 10.0f, 15.0f, 25.0f, 35.0f,
        45.0f, 55.0f, 65.0f, 80.0f, 90.0f, 100.0f};
    constexpr size_t count = sizeof(volts) / sizeof(volts[0]);

    if (voltage <= volts[0])
        return percents[0];
    if (voltage >= volts[count - 1])
        return percents[count - 1];

    for (size_t i = 1; i < count; ++i)
    {
        if (voltage <= volts[i])
        {
            const float fraction = (voltage - volts[i - 1]) / (volts[i] - volts[i - 1]);
            return percents[i - 1] + fraction * (percents[i] - percents[i - 1]);
        }
    }

    return percents[count - 1];
}

void batteryMonitorTask(void *)
{
    for (;;)
    {
        uint32_t voltageTotalMillivolts = 0;
        for (uint32_t sample = 0; sample < BATTERY_SAMPLE_COUNT; ++sample)
        {
            voltageTotalMillivolts += analogReadMilliVolts(BAT_DIV_PIN);
            vTaskDelay(BATTERY_SAMPLE_DELAY);
        }

        const uint16_t averageVoltageMillivolts =
            static_cast<uint16_t>(voltageTotalMillivolts / BATTERY_SAMPLE_COUNT);
        const uint8_t estimatedCharge =
            static_cast<uint8_t>(estimateChargePercent(averageVoltageMillivolts));
        averagedVoltageMillivolts.store(averageVoltageMillivolts);
        chargePercent.store(estimatedCharge);
        vTaskDelay(BATTERY_UPDATE_DELAY);
    }
}
}

bool startBatteryMonitorTask()
{
    if (batteryMonitorTaskHandle != nullptr)
        return true;

    pinMode(BAT_DIV_PIN, INPUT);
    const BaseType_t result = xTaskCreate(
        batteryMonitorTask,
        "BatteryMonitor",
        2048,
        nullptr,
        1,
        &batteryMonitorTaskHandle);
    if (result != pdPASS)
    {
        batteryMonitorTaskHandle = nullptr;
        Serial.println("[Battery] Failed to create monitor task");
        return false;
    }

    return true;
}

uint16_t getBatteryVoltage()
{
    return averagedVoltageMillivolts.load();
}

uint8_t getBatteryChargePercent()
{
    return chargePercent.load();
}
