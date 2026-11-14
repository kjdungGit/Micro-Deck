#include "main.h"
#include "init.h"
#include "runtime.h"
#include <Wire.h>
#include <esp_sleep.h>

uint64_t WAKE_BUTTONS =
    (1ULL << K2_PIN) |
    (1ULL << K3_PIN);

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Wire.begin(SDA_PIN, SCL_PIN);
  for (byte addr = 1; addr < 127; addr++)
  {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0)
    {
      Serial.print("Found device at 0x");
      Serial.println(addr, HEX);
    }
  }

  init(esp_sleep_get_gpio_wakeup_status() == ESP_SLEEP_WAKEUP_UNDEFINED);
  delay(1000);

  if (!startRuntimeTasks())
  {
    Serial.println("Runtime task startup failed");
    while (true)
      delay(1000);
  }
  Serial.println("SetupFinished");
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}