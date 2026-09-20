#pragma once

enum SleepStyle {
  ESP_SLEEP_DEEP = -1,
  ESP_SLEEP_LIGHT = 1
};

void goToSleep(int  style);