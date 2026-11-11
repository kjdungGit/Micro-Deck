#include "init.h"
#include "sleep.h"
#include "Apps/App.h"
#include "Apps/Power.h"
#include "buttons.h"
#include "clock.h"
#include "display.h"
#include "nvs.h"

uint32_t serialReadTime = 0;

ulong App::programRunTime = 0;
std::map<byte, App *> App::apps;
App *App::activeApp = nullptr;
int App::AppCount = 0;
std::vector<byte> App::ID_List;

bool checkFreshFlash()
{
    static bool checked = false; // has this function run its detection logic yet this boot?
    static bool result = false;  // cached answer for the rest of this boot cycle
    if (!checked)
    {
        const char *buildStamp = __DATE__ " " __TIME__; // unique per compile
        String storedStamp = preferences.getString("build", "");
        Serial.println(storedStamp != String(buildStamp));
        if (storedStamp != String(buildStamp))
        {
            // firmware binary changed since last time this ran -> fresh flash
            result = true;
            preferences.putString("build", buildStamp);

            // reset your boot counter here, since this is your build-flag trigger
            preferences.putUInt("bootCount", 0);
        }
        else
        {
            result = false;
        }
        checked = true;
    }
    return result;
}

int requestTimeFromPC()
{

    delay(2000);

    Serial.println("REQUEST_TIME");

    unsigned long start = millis();

    while (!Serial.available() && millis() - start < 10000)
    {
        delay(100);
    }
    Serial.print("...");
    delay(500);
    String line = Serial.readStringUntil('\n');
    line.trim();

    int y, mo, d, h, mi, s;
    int parsed = sscanf(line.c_str(), "%d,%d,%d,%d,%d,%d", &y, &mo, &d, &h, &mi, &s);

    if (parsed == 6)
    {
        Serial.println("Got time from PC: " + line);
        Serial.println("REQUEST_TIME_ACK");
        return DateTime(y, mo, d, h, mi, s).unixtime();
    }
    else
    {
        Serial.println("Bad time format: " + line);
        return 0;
    }
}

void setupLVGL()
{
    lv_init(); // starts LVGL's internal systems — call this first, once
    display.clearDisplay();
    display.display();
    disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);

    lv_display_set_color_format(disp, LV_COLOR_FORMAT_I1); // 1-bit monochrome, matches your SSD1309

    lv_display_set_buffers(disp, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_display_set_flush_cb(disp, pushToOled);
}

void setupRTC()
{

    Serial.println("Initializing RTC...");
    if (!RTC.begin())
    {
        Serial.println("Couldn't find RTC");
        return;
    }

    Serial.println("RTC found");
#ifdef FLAG_FLASHNEWTIME
    {
        Serial.println("setupRTC: new boot, setting RTC to Serial time");

        RTC.adjust(preferences.getULong("unix_time", (uint32_t)(1)));
        DateTime now = RTC.now();
        Serial.println(now.unixtime());
        Serial.printf("RTC now: %04d/%02d/%02d %02d:%02d:%02d\n",
                      now.year(), now.month(), now.day(),
                      now.hour(), now.minute(), now.second());
    }
#else
    DateTime dt = DateTime(preferences.getULong("unix_time", 0));
    Serial.printf("RTC already set to: %04d/%02d/%02d %02d:%02d:%02d\n",
                  dt.year(), dt.month(), dt.day(),
                  dt.hour(), dt.minute(), dt.second());
#endif
}

void setupNVS(bool fresh)
{
    preferences.begin("microdeck", false);
    preferences.putInt("free_boot_count", preferences.getInt("free_boot_count", 0) + 1);
    if (!checkFreshFlash())
        return;
#ifdef FLAG_FLASHNEWTIME
    serialReadTime = requestTimeFromPC();

    Serial.print("Unix Time Variance Amount: ");
    Serial.println(serialReadTime - preferences.getULong("unix_time"));
    preferences.putULong("unix_time", serialReadTime);
#endif

#ifdef FLAG_RESETBOOTCOUNTER
    Serial.println("setupNVS: new boot, FLAG_RESETBOOTCOUNTER setting free_boot_count to 0");
    preferences.putInt("free_boot_count", 0);
#else
    preferences.putInt("free_boot_count", preferences.getInt("free_boot_count", 0) + 1);
#endif
}

void setupApps()
{
    // App *App_RAMCPUVISUALIZER = App::createApp_Object(0x0001,"CPU SRAM Visualizer", Utility, REFRESH_SLOW);
    App::createApp_Object(0xFF, "ZERO", Utility, REFRESH_SLOW);
    App::createApp_Object(0x01, "P 1", Utility, REFRESH_SLOW);
    App::createApp_Object(0x02, "P 2", Utility, REFRESH_SLOW);
    App *Power = App::createApp_Object(0xF3, "Power", Service, REFRESH_MEDIUM);
    Serial.println("[App] Registering Power program exec");
    Power->setProgramExec([] { Power_exec(); });
    Power->setProgramClose([] { closePowerMenu(); });

    Serial.printf("\tApps initialized {%d}:\n", App::AppCount);
    for (byte app : App::ID_List)
    {
        Serial.printf("\tApp ID: %d, Name: %s\n", app, App::getApp(app)->getName().c_str());
    }
}

void init(bool fresh)
{
    setupDisplay();
    setupLVGL();
    setupNVS(fresh);
    setupRTC();
    setupButtons();
    setupApps();
}