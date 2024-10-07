#include "AgriArenaClient.hpp"

#include <ArduinoJson.h>

AgriArenaClient::AgriArenaClient(Sensors &S, OLED &D) : Sensors(S), OLED(D) {}

bool AgriArenaClient::config(const String &URL, const char *certificate) {
#ifdef USE_HTTPS
    this->client.setCACert(certificate);
#endif
    this->http.begin(client, URL);
    this->http.addHeader("Content-Type", "application/json");

    this->deviceId = ESP.getEfuseMac();

    this->wellcome();
    return true;
}

void AgriArenaClient::send_all() {
    DynamicJsonDocument data = this->get_all();
    data["iot"] = this->deviceId;

    String jsonString;
    serializeJson(data, jsonString);

    int httpResponseCode = this->http.POST(jsonString);
    if(httpResponseCode > 0) {
        String response = this->http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
    } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
}
