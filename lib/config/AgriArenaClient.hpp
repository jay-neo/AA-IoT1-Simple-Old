#ifndef AGRIARENACLIENT_HPP
#define AGRIARENACLIENT_HPP

#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "OLED.hpp"
#include "Sensors.hpp"

#ifdef USE_HTTPS
#include <WiFiClientSecure.h>
#else
#include <WiFi.h>
#endif

class AgriArenaClient : public Sensors, public OLED {
#ifdef USE_HTTPS
    WiFiClientSecure client;
#else
    WiFiClient client;
#endif

    HTTPClient http;
    uint64_t deviceId;

   public:
    AgriArenaClient(Sensors &S, OLED &D);

    void send_all();
    bool config(const String &URL, const char *certificate);
};

#endif