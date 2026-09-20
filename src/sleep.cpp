#include "sleep.h"
#include "display.h"
#include "main.h"
#include "nvs.h"
#include <esp_sleep.h>

void goToSleep(int style)
{
  Serial.println("Sleeping..." + String(style == ESP_SLEEP_DEEP ? "DEEP SLEEP" : "LIGHT SLEEP"));
  Serial.flush();
  
  display.clearDisplay();
  

  switch (style)
  {
  case SleepStyle::ESP_SLEEP_DEEP:
  {
    // Wake if ANY enabled button is pressed (driven LOW).
    esp_err_t err = esp_deep_sleep_enable_gpio_wakeup(
        WAKE_BUTTONS,
        ESP_GPIO_WAKEUP_GPIO_LOW);

    if (err != ESP_OK)
    {
      Serial.printf("Wake setup failed: %d\n", err);
      return;
    }
    display.display();
    delay(100);
    esp_deep_sleep_start();
    break;
  }
  case SleepStyle::ESP_SLEEP_LIGHT:
  {
    gpio_wakeup_enable(GPIO_NUM_4, GPIO_INTR_LOW_LEVEL);
    gpio_wakeup_enable(GPIO_NUM_5, GPIO_INTR_LOW_LEVEL);
    esp_err_t err = esp_sleep_enable_gpio_wakeup();
    if (err != ESP_OK)
    {
      Serial.printf("Wake setup failed: %d\n", err);
      return;
    }
    display.display();
    delay(100);
    esp_light_sleep_start();

    lv_obj_invalidate(lv_scr_act());
    lv_refr_now(NULL);
    preferences.putInt("free_boot_count", preferences.getInt("free_boot_count", 0) + 1);
    break;
  }
  }
}