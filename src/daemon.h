#pragma once
#include <functional>
#include <vector>
#include <Arduino.h>

struct LoopDaemon;
struct daemonController;

struct LoopDaemon
{
    unsigned long interval;     // Refresh interval in milliseconds
    unsigned long lastRunTime;  // Timestamp of the last execution
    std::function<void()> task; // Target function to execute
    bool enabled;               // Execution-blocking flag

    // -------------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------------

    // Constructor 1: Standard function without parameters
    LoopDaemon(uint32_t refreshIntervalMs, std::function<void()> fn)
        : interval(refreshIntervalMs), lastRunTime(0), task(fn) {}

    // Constructor 2: Function with arbitrary parameters (bound at initialization)
    template <typename Fn, typename... Args>
    LoopDaemon(uint32_t refreshIntervalMs, Fn fn, Args... args)
        : interval(refreshIntervalMs), lastRunTime(0)
    {
        // Bind the function with its arguments into a parameterless callable
        task = std::bind(fn, args...);
    }

    // -------------------------------------------------------------
    // MEMBER FUNCTIONS
    // -------------------------------------------------------------

    // 1. Checks if the initialized delay time has elapsed since last run
    bool isReady() const
    {
        // Subtraction accounts for millis() rollover (~49.7 days)
        return (millis() - lastRunTime >= interval);
    }

    // 2. Executes the assigned function and updates the last run timestamp
    void execute()
    {
        if (task)
        {
            task();
        }
        lastRunTime = millis();
    }

    // Convenience method: Checks readiness and executes automatically
    bool tick()
    {
        if (isReady() && enabled)
        {
            execute();
            return true;
        }
        return false;
    }
};

// Assuming LoopDaemon struct from earlier is included above

struct daemonController
{
    // 1. Vector housing pointers to all managed daemon structs
    std::vector<LoopDaemon *> daemons;

    daemonController() {};

    // Destructor to clean up allocated memory if controller is destroyed
    ~daemonController()
    {
        for (LoopDaemon *daemon : daemons)
        {
            delete daemon;
        }
        daemons.clear();
    }

    // -------------------------------------------------------------
    // 2. INIT FUNCTIONS (Factory Methods)
    // -------------------------------------------------------------

    // Init Variation 1: Standard function without parameters
    LoopDaemon *add(String name,unsigned long refreshIntervalMs, std::function<void()> fn)
    {
        LoopDaemon *newDaemon = new LoopDaemon(refreshIntervalMs, fn);
        daemons.push_back(newDaemon);
        return newDaemon;
    }

    // Init Variation 2: Function with arbitrary parameters
    template <typename Fn, typename... Args>
    LoopDaemon *add(String name, unsigned long refreshIntervalMs, Fn fn, Args... args)
    {
        LoopDaemon *newDaemon = new LoopDaemon(refreshIntervalMs, fn, args...);
        daemons.push_back(newDaemon);
        return newDaemon;
    }

    // -------------------------------------------------------------
    // 3. DESTROY FUNCTION
    // -------------------------------------------------------------

    // Removes and deallocates a daemon from the vector using its pointer
    bool destroy(LoopDaemon *daemonPtr)
    {
        if (!daemonPtr)
            return false;

        for (auto it = daemons.begin(); it != daemons.end(); ++it)
        {
            if (*it == daemonPtr)
            {
                delete *it;        // Free dynamically allocated memory
                daemons.erase(it); // Remove pointer from vector
                return true;
            }
        }
        return false; // Pointer not found
    }

    // -------------------------------------------------------------
    // 4. TICK FUNCTION
    // -------------------------------------------------------------

    // Iterates through all daemons and runs their ready check/execution
    void tick()
    {
        for (LoopDaemon *daemon : daemons)
        {
            if (daemon)
            {
                daemon->tick();
            }
        }
    }
};

static daemonController daemonManager;