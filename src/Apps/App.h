#pragma once
#include "Global.h"
#include "app_ids.h"
#include "runtime.h"
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
            return index > -1 && index < ID_List.size() ? ID_List.at(index) : APP_ID_DEFAULT;
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
        return apps.at(APP_ID_DEFAULT);
    }

    static App *createApp_Object(byte id, String name, App_Type type = Utility, REFRESH refresh = REFRESH_SLOW)
    {
        if (id == APP_ID_DEFAULT && apps.find(APP_ID_DEFAULT) != apps.end())
        {
            Serial.printf("\tSKIP: %s has no configured app ID\n", name.c_str());
            return nullptr;
        }

        if (id != APP_ID_DEFAULT && apps.find(id) != apps.end())
        {
            Serial.printf("\tSKIP: %s duplicates app ID %u\n", name.c_str(), id);
            return nullptr;
        }

        apps[id] = new App(id, name, type, refresh);
        if (id == APP_ID_DEFAULT)
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

    static void closeActiveApp()
    {
        if (!enqueueActiveAppClose())
            Serial.println("[App] No active app could be closed");
    }

    static void openApp(byte id)
    {
        Serial.printf("[App] Open requested: id=%u\n", id);
        if (!enqueueAppOpen(id))
            Serial.printf("[App] Failed to queue app id %u\n", id);
    }

    static void executeApp(byte id)
    {
        auto it = apps.find(id);
        if (it == apps.end())
        {
            Serial.printf("[App] Unknown app id %u\n", id);
            finishAppExecution(id);
            return;
        }

        activeApp = it->second;
        setMainMenuActive(false);
        Serial.printf("[App] Active app is '%s'\n", activeApp->name.c_str());
        if (!postRuntimeUiMessage(RuntimeUiMessageType::OpenApp, id))
        {
            activeApp = nullptr;
            setMainMenuActive(true);
            finishAppExecution(id);
        }
    }

    static void executeClose()
    {
        if (activeApp == nullptr)
        {
            Serial.println("[App] Close request ignored; no active app");
            return;
        }

        const byte closingAppId = activeApp->id;
        activeApp = nullptr;
        setMainMenuActive(true);
        finishAppExecution(closingAppId);
        postRuntimeUiMessage(RuntimeUiMessageType::CloseActiveApp, closingAppId);
    }
};