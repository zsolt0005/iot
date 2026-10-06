#pragma once

#include <Arduino.h>

class Scheduler {
public:
    typedef void (*Callback)();

    static constexpr uint8_t MAX_TASKS = 8;
    static constexpr int8_t INVALID_ID = -1;

    int8_t every(uint32_t intervalMs, Callback fn);
    int8_t after(uint32_t delayMs, Callback fn);
    void cancel(int8_t id);

    void run();

private:
    struct Task {
        Callback fn;
        uint32_t interval;
        uint32_t lastRun;
        bool repeat;
    };

    int8_t add(uint32_t intervalMs, Callback fn, bool repeat);

    Task _tasks[MAX_TASKS] = {};
};
