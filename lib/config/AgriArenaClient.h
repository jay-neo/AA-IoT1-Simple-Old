#ifndef AGRIARENACLIENT_H
#define AGRIARENACLIENT_H

#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

class AgriArenaClient {
    WiFiClientSecure client;
    HTTPClient http;
public:
    // AgriArenaClient();

    void config(String, const char *);
    void send(DynamicJsonDocument, const uint64_t&, IPAddress);
};

#endif