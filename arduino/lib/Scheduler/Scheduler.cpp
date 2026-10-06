#include "Scheduler.h"

int8_t Scheduler::every(const uint32_t intervalMs, const Callback fn) {
    return add(intervalMs, fn, true);
}

int8_t Scheduler::after(const uint32_t delayMs, const Callback fn) {
    return add(delayMs, fn, false);
}

void Scheduler::cancel(const int8_t id) {
    if (id >= 0 && id < MAX_TASKS) {
        _tasks[id].fn = nullptr;
    }
}

void Scheduler::run() {
    for (uint8_t i = 0; i < MAX_TASKS; i++) {
        Task &task = _tasks[i];
        if (task.fn == nullptr) {
            continue;
        }

        // Unsigned subtraction keeps working when millis() overflows.
        uint32_t now = millis();
        if (now - task.lastRun < task.interval) {
            continue;
        }

        Callback fn = task.fn;
        if (task.repeat) {
            task.lastRun = now;
        } else {
            // Free the slot first so the callback can schedule a new task.
            task.fn = nullptr;
        }
        fn();
    }
}

int8_t Scheduler::add(uint32_t intervalMs, Callback fn, bool repeat) {
    if (fn == nullptr) {
        return INVALID_ID;
    }
    for (uint8_t i = 0; i < MAX_TASKS; i++) {
        if (_tasks[i].fn == nullptr) {
            _tasks[i] = {fn, intervalMs, millis(), repeat};
            return i;
        }
    }
    return INVALID_ID;
}
