#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Display {
public:
    Display(uint8_t address, uint8_t cols, uint8_t rows);

    // Returns false when no device answers on the given I2C address.
    bool begin();

    // Replaces the whole row; the rest of the row is padded with spaces.
    void print(uint8_t row, const char *text);
    void clear();

private:
    LiquidCrystal_I2C _lcd;
    uint8_t _address;
    uint8_t _cols;
    bool _ready = false;
};
