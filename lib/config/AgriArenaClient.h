#ifndef AGRIARENACLIENT_H
#define AGRIARENACLIENT_H

#include <ArduinoJson.h>
#include <HTTPClient.h>

#ifdef USE_HTTPS
#include <WiFiClientSecure.h>
#else
#include <WiFi.h>
#endif

class AgriArenaClient {
#ifdef USE_HTTPS
    WiFiClientSecure client;
#else
    WiFiClient client;
#endif

    HTTPClient http;
    uint64_t deviceId;
    const char *ntpServer;
    // TaskHandle_t timeTaskHandle = NULL;

   public:
    AgriArenaClient();

    String getTime();
    void send(DynamicJsonDocument &data);
    bool config(const String &URL, const char *certificate);
    // static void timeTask(void* pvParameters);
};

#endif