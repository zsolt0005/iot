#pragma once

#include <Arduino.h>

// Relay module KY-019 (SRD-05VDC-SL-C)
//   S -> D7, + -> 5V, - -> GND
// The module is active HIGH: HIGH on S energises the coil (NO contact closes).
constexpr uint8_t RELAY_PIN = 7;

// Tactile button (4 legs). The legs are connected in pairs, so use two legs
// that sit diagonally across from each other: one -> D2, the other -> GND.
// No external resistor is needed, the internal pull-up is used.
constexpr uint8_t BUTTON_PIN = 2;

// I2C LCD (HD44780 with PCF8574 backpack)
//   SDA -> A4 (or the SDA header pin), SCL -> A5 (or the SCL header pin),
//   VCC -> 5V, GND -> GND
// The address is usually 0x27, some backpacks use 0x3F.
constexpr uint8_t LCD_ADDRESS = 0x27;
constexpr uint8_t LCD_COLS = 16;
constexpr uint8_t LCD_ROWS = 2;

// WIfi settings
constexpr char *WifiSSID = "ZHome";
constexpr char *WifiPassword = "Sziszike15.";