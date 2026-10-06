#include "Display.h"

#include <Wire.h>

Display::Display(const uint8_t address, const uint8_t cols, const uint8_t rows)
    : _lcd(address, cols, rows), _address(address), _cols(cols) { }

bool Display::begin() {
    Wire.begin();
    // Do not hang forever when the bus is stuck (e.g. a loose wire).
    Wire.setWireTimeout(25000, true);

    Wire.beginTransmission(_address);
    if (Wire.endTransmission() != 0) {
        _ready = false;
        return false;
    }

    _lcd.init();
    _lcd.backlight();
    _lcd.clear();

    _ready = true;
    return true;
}

void Display::print(const uint8_t row, const char *text) {
    if (!_ready) {
        return;
    }
    _lcd.setCursor(0, row);
    uint8_t col = 0;
    for (; col < _cols && text[col] != '\0'; col++) {
        _lcd.write(text[col]);
    }
    for (; col < _cols; col++) {
        _lcd.write(' ');
    }
}

void Display::clear() {
    if (!_ready) {
        return;
    }
    _lcd.clear();
}
