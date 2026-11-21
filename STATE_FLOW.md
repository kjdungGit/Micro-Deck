# Micro-Deck project state flow

This flow chart follows the current firmware implementation in `src/`. It covers
startup, the launcher, registered apps, and both sleep paths.

```mermaid
flowchart TD
    POWER_ON([Power applied / reset]) --> SETUP["setup(): start Serial and I2C; scan I2C devices"]
    SETUP --> INIT_NVS["init(): open NVS; update boot counter; detect firmware build"]
    INIT_NVS --> INIT_RTC["Initialize RTC"]
    INIT_RTC --> INIT_BUTTONS["Create K1-K4 buttons"]
    INIT_BUTTONS --> INIT_APPS["Register apps"]
    INIT_APPS --> TASKS{"Create runtime tasks and queues"}
    TASKS -->|Failure| STARTUP_FAILED["Startup halted; report runtime startup failure"]
    TASKS -->|Success| UI_SETUP["UI task: initialize display and LVGL; build header and launcher; enable buttons"]
    UI_SETUP --> READY{"UI ready within 10 seconds?"}
    READY -->|No| STARTUP_FAILED
    READY -->|Yes| LAUNCHER["Launcher active"]

    LAUNCHER -->|K3 up / K2 down| MENU_MOVE["Move selection; wrap through registered apps"]
    MENU_MOVE --> LAUNCHER
    LAUNCHER -->|K1| HEADER["Toggle launcher header"]
    HEADER --> LAUNCHER
    LAUNCHER -->|K4 select| QUEUE_OPEN["Queue selected app"]
    QUEUE_OPEN --> APP_START["App task claims app target; pause launcher refresh; request app UI"]
    APP_START --> APP_UI{"Registered app"}

    APP_UI -->|Power| POWER_MENU["Power menu: Return / Sleep / Power Off"]
    POWER_MENU -->|K3 left / K2 right| POWER_MOVE["Cycle selection"]
    POWER_MOVE --> POWER_MENU
    POWER_MENU -->|K4: Return| CLOSE_APP["Close active app; restore launcher"]
    CLOSE_APP --> LAUNCHER
    POWER_MENU -->|K4: Sleep| SLEEP_REQUEST["Queue app close and light-sleep request"]
    POWER_MENU -->|K4: Power Off| DEEP_REQUEST["Queue app close and deep-sleep request"]

    SLEEP_REQUEST --> LIGHT_CONFIG["Clear display; enable low-level wake on GPIO 4 and GPIO 5"]
    LIGHT_CONFIG --> LIGHT_SLEEP["Light sleep"]
    LIGHT_SLEEP -->|Wake signal| LIGHT_RESUME["Resume same runtime; refresh display; reset launcher selection"]
    LIGHT_RESUME --> LAUNCHER

    DEEP_REQUEST --> DEEP_CONFIG["Clear display; enable active-low GPIO wake on K2 or K3"]
    DEEP_CONFIG --> DEEP_SLEEP["Deep sleep (not a true power disconnect)"]
    DEEP_SLEEP -->|K2 or K3 wake| POWER_ON

    APP_UI -->|Task Manager| TASK_MANAGER["Task Manager: resource view and power/boot view"]
    TASK_MANAGER -->|K3 / K2| TASK_NAV["Navigate Task Manager views"]
    TASK_NAV --> TASK_MANAGER
    TASK_MANAGER -->|K4| CLOSE_APP

    APP_UI -->|Guitar Hero| SONG_SELECT["Song selection"]
    SONG_SELECT -->|Select song| SPEED_SELECT["Choose note speed"]
    SPEED_SELECT -->|Start| GAMEPLAY["Play song; K1-K4 hit notes"]
    GAMEPLAY -->|Song ends| SONG_COMPLETE["Song complete; replay or return to song selection"]
    SONG_COMPLETE -->|Replay / back| GAMEPLAY
    SONG_COMPLETE -->|Back to songs| SONG_SELECT
    SONG_SELECT -->|Hold K1 + K4 for 1 second| CLOSE_APP
    SPEED_SELECT -->|Hold K1 + K4 for 1 second| CLOSE_APP
    GAMEPLAY -->|Hold K1 + K4 for 1 second| CLOSE_APP

    APP_UI -->|No UI registered for app| CLOSE_APP

    subgraph BACKGROUND["Runtime workers while awake"]
        BUTTON_WORKER["Poll K1-K4 and dispatch button events"]
        UI_WORKER["Process UI messages and LVGL timers"]
        CLOCK_WORKER["Refresh launcher time once per second while launcher is active"]
        APP_WORKER["Process queued app launch, input, and close requests"]
        BATTERY_WORKER["Sample battery and estimate charge"]
    end
    LAUNCHER -. runs alongside .-> BUTTON_WORKER
    LAUNCHER -. runs alongside .-> UI_WORKER
    LAUNCHER -. runs alongside .-> CLOCK_WORKER
    LAUNCHER -. runs alongside .-> APP_WORKER
    LAUNCHER -. runs alongside .-> BATTERY_WORKER
```

## Current implementation notes

- `setupApps()` registers **Power**, **Task Manager**, and **Guitar Hero** as
  launcher entries. `APP_ID_MUSIC_PLAY` is defined in the build configuration,
  but it is not currently registered by `setupApps()`.
- The Power menu's **Power Off** action calls `esp_deep_sleep_start()`. The
  processor remains in deep sleep and can wake on K2/K3; this is not equivalent
  to physically disconnecting power. A physically unpowered device must have
  power restored before it can boot.
- Light sleep is a suspend/resume path in the current runtime. Its configured
  wake sources are `GPIO_NUM_4` and `GPIO_NUM_5`; after waking, the firmware
  refreshes the UI and resets launcher navigation.
- Deep-sleep wake restarts `setup()` and follows the normal initialization path;
  app execution is not restored. The wake-derived boolean passed to `init()` is
  currently unused by `init()`.
