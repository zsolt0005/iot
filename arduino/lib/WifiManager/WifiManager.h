#pragma once

#include <Arduino.h>

class WifiManager {
public:
    typedef void (*Callback)();

    explicit WifiManager(const char *ssid, const char *password)
        : _ssid(ssid), _password(password) {}

    bool begin();
    void onConnect(Callback cb);
    bool isConnected() const;

    void update();

private:
    static constexpr uint32_t RETRY_MS = 10000;

    const char *_ssid;
    const char *_password;

    Callback _onConnected = nullptr;
    bool _connected = false;

    uint32_t _lastAttempt = 0;

    bool connect();
};