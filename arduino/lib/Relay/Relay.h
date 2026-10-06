#pragma once

#include <Arduino.h>

// Single relay module such as KY-019 (active HIGH by default).
class Relay {
public:
    explicit Relay(const uint8_t pin, const bool activeHigh = true) : _pin(pin), _activeHigh(activeHigh) {}

    // Configures the pin; the relay starts switched off.
    void begin();

    void on();
    void off();
    void toggle();
    void set(bool on);
    bool isOn() const;

private:
    uint8_t _pin;
    bool _activeHigh;
    bool _on = false;
};
