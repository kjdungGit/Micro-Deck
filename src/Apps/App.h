#pragma once
#include "Global.h"
#include <functional>
#include <map>
#include <vector>

enum App_Type
{
    Game,
    Service,
    Utility
};

enum REFRESH
{
    REFRESH_SLOW = 15,
    REFRESH_MEDIUM = 30,
    REFRESH_FAST = 45
};

class App
{
private:
    /**ID used as identifier of app */
    byte id;
    String name;
    App_Type type;
    REFRESH refreshSpeed;
    static ulong programRunTime;
    static std::map<byte, App *> apps;
    static App *activeApp;
    std::function<void()> program_exec;
    std::function<void()> program_close;

    App(byte id, String name, App_Type type = Utility, REFRESH refresh = REFRESH_FAST) : id(id), name(name), type(type), refreshSpeed(refresh)
    {
    }

public:
    static int AppCount;
    static std::vector<byte> ID_List;
    String getName() { return name; }
    int getID() { return int(id); }
    App_Type getType() { return type; }

    static byte getAppIDatIndex(int index)
    {
            return index > -1 && index < ID_List.size() ? ID_List.at(index) : 0xFF;
    }

    static App *getApp(byte id)
    {
        auto it = apps.find(id);
        if (it != apps.end())
        {
            Serial.println("+");
            return it->second; // one lookup, reused
        }
        Serial.println("-");
        return apps.at(0xFF);
    }

    static App *createApp_Object(byte id, String name, App_Type type = Utility, REFRESH refresh = REFRESH_SLOW)
    {
        apps[id] = new App(id, name, type, refresh);
        if (id == 0xFF)
        {
            Serial.printf("\tDEF: %s\n", name.c_str());
            return nullptr;
        }
        else
        {
            Serial.printf("\tAPP: %s id: %d\n", name.c_str(), id);
        }
        ID_List.push_back(id);
        AppCount += 1;
        return apps[id];
    }

    void setProgramExec(std::function<void()> exec)
    {
        Serial.printf("[App] Registering program exec for '%s': %s\n", name.c_str(), exec ? "set" : "empty");
        program_exec = exec;
    }

    void setProgramClose(std::function<void()> close)
    {
        Serial.printf("[App] Registering program close for '%s': %s\n", name.c_str(), close ? "set" : "empty");
        program_close = close;
    }

    void closeApp()
    {
        Serial.printf("[App] Close requested: '%s'\n", name.c_str());
        if (program_close)
            program_close();
    }

    static void closeActiveApp()
    {
        if (activeApp != nullptr)
            activeApp->closeApp();
    }

    void launchApp()
    {
        Serial.printf("[App] Launch requested: '%s'\n", name.c_str());
        if (!program_exec)
        {
            Serial.printf("[App] No program exec registered for '%s'\n", name.c_str());
            return;
        }
        activeApp = this;
        Serial.printf("[App] Executing program: '%s'\n", name.c_str());
        program_exec();
        Serial.printf("[App] Program returned: '%s'\n", name.c_str());
    }
};

inline void setMainMenuActive(bool state)
{
    mainMenuActive = state;
}