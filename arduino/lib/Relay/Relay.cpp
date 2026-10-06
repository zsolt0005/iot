#include "Relay.h"

Relay::Relay(const uint8_t pin, const bool activeHigh) : _pin(pin), _activeHigh(activeHigh) {}

void Relay::begin() {
    // Write the level before switching to OUTPUT so the relay does not click on boot.
    set(false);
    pinMode(_pin, OUTPUT);
}

void Relay::on() {
    set(true);
}

void Relay::off() {
    set(false);
}

void Relay::toggle() {
    set(!_on);
}

void Relay::set(const bool on) {
    _on = on;
    digitalWrite(_pin, on == _activeHigh ? HIGH : LOW);
}

bool Relay::isOn() const {
    return _on;
}
