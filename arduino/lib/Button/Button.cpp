#include "Button.h"

void Button::begin() const {
    pinMode(_pin, INPUT_PULLUP);
}

void Button::onPress(const Callback fn) {
    _onPress = fn;
}

void Button::update() {
    const bool reading = digitalRead(_pin) == LOW;
    const uint32_t now = millis();

    if (reading != _lastReading) {
        _lastReading = reading;
        _lastChange = now;
        return;
    }

    // Accept the new state only after it has been stable for the debounce time.
    if (reading != _pressed && now - _lastChange >= _debounceMs) {
        _pressed = reading;
        if (_pressed && _onPress != nullptr) {
            _onPress();
        }
    }
}

bool Button::isPressed() const {
    return _pressed;
}
