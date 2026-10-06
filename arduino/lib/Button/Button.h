#pragma once

#include <Arduino.h>

// Debounced push button wired between the pin and GND (internal pull-up).
class Button {
public:
    typedef void (*Callback)();

    explicit Button(uint8_t pin, uint16_t debounceMs = 30);

    void begin() const;

    // Called once per press (on the press edge, not on release).
    void onPress(Callback fn);

    // Non-blocking; call periodically (every few ms).
    void update();

    bool isPressed() const;

private:
    uint8_t _pin;
    uint16_t _debounceMs;
    Callback _onPress = nullptr;
    bool _pressed = false;
    bool _lastReading = false;
    uint32_t _lastChange = 0;
};
