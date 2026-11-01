#include "main.h"
#include "init.h"
#include "Components/components.h"
#include "Components/mainMenu/screenMainMenu.h"
#include "clock.h"
#include "img_resize.h"
#include "buttons.h"
#include "daemon.h"
#include "display.h"
#include "nvs.h"
#include <Wire.h>
#include <esp_sleep.h>

uint64_t WAKE_BUTTONS =
    (1ULL << K2_PIN) |
    (1ULL << K3_PIN);

extern lv_obj_t *lv_app_image;
bool mainMenuActive = true;

void my_log_cb(lv_log_level_t level, const char *buf)
{
  Serial.println(buf);
}

LoopDaemon *buttonManagerDaemon = daemonManager.add("Button_Update",10, [&](){buttonManager.updateButtons();});

LoopDaemon *graphicsRenderDaemon = daemonManager.add("Graphics Manager",1000 / 30, [&]()
{
  if(mainMenuActive)
    setMenu_TimeLabelInformation(getNow());
  lv_tick_inc(millis() - millisSinceGraphicsRefresh);
  lv_task_handler();
  millisSinceGraphicsRefresh = millis(); });

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
  delay(100);

  buildBlankHeader(lv_scr_act());
  buildHeaderTimeLabel(lv_header);
  buildHeaderBootLabel(lv_header);
  buildMenuScreen(lv_scr_act());
  setBoot(preferences.getInt("free_boot_count"));

  lv_obj_add_flag(lv_header, LV_OBJ_FLAG_HIDDEN);
  lv_log_register_print_cb(my_log_cb);
  Serial.println("SetupFinished");
  initMainMenuButtons(buttonManager.getButton(K2_PIN), buttonManager.getButton(K3_PIN), buttonManager.getButton(K4_PIN));
  buttonManager.buttonsEnabled = true;
  buttonManagerDaemon->enabled = true;
}

void loop()
{
  delay(5);
  daemonManager.tick();
}