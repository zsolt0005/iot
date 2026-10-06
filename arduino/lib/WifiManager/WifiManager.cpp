#include "WifiManager.h"

#include <WiFi.h>

bool WifiManager::begin() { return connect(); }
void WifiManager::onConnect(const Callback cb) { _onConnected = cb; }
bool WifiManager::isConnected() const { return _connected; }

void WifiManager::update() {
    const bool isConnected = WiFi.status() == WL_CONNECTED;

    // Trigger connected state
    if (isConnected && !_connected && _onConnected != nullptr) {
        _onConnected();
    }

    // Reconnect
    if (!isConnected && millis() - _lastAttempt >= RETRY_MS) {
        connect();
    }

    _connected = isConnected;
}

bool WifiManager::connect() {
    _lastAttempt = millis();
    return WiFi.begin(_ssid, _password) == WL_CONNECTED;
}
