#include <Arduino.h>

#include <Button.h>
#include <Display.h>
#include <Relay.h>
#include <Scheduler.h>
#include <WifiManager.h>

#include "config.h"

static Scheduler scheduler;
static Relay relay(RELAY_PIN);
static Button button(BUTTON_PIN);
static Display display(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

static WifiManager wifiManager(WifiSSID, WifiPassword);

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

    // Init components
    relay.begin();
    button.begin();
    if (!display.begin()) Serial.println("LCD not found, check wiring and LCD_ADDRESS");
    //if (!wifiManager.begin()) Serial.println("Failed to connect to WiFi");

    // Pre-render
    showRelayState();
    showUptime();

    // Callbacks
    button.onPress(onButtonPress);

    // Scheduled tasks
    scheduler.every(5, [] { button.update(); });
    //scheduler.every(500, [] { wifiManager.update(); });
    scheduler.every(1000, showUptime);
}

void loop() {
    scheduler.run();
}
