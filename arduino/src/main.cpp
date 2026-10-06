#include <Arduino.h>

#include <Button.h>
#include <Display.h>
#include <Relay.h>
#include <Scheduler.h>

#include "config.h"

static Scheduler scheduler;
static Relay relay(RELAY_PIN);
static Button button(BUTTON_PIN);
static Display display(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

static void showRelayState() {
    display.print(0, relay.isOn() ? "Relay: ON" : "Relay: OFF");
}

static void showUptime() {
    char line[LCD_COLS + 1];
    snprintf(line, sizeof(line), "Uptime: %lus", millis() / 1000);
    display.print(1, line);
}

static void onButtonPress() {
    relay.toggle();
    showRelayState();
}

void setup() {
    Serial.begin(9600);

    relay.begin();
    button.begin();
    button.onPress(onButtonPress);

    if (!display.begin()) {
        Serial.println("LCD not found, check wiring and LCD_ADDRESS");
    }
    showRelayState();
    showUptime();

    scheduler.every(5, [] { button.update(); });
    scheduler.every(1000, showUptime);
}

void loop() {
    scheduler.run();
}
