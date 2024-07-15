#include <ArduinoJson.h>
#include "AgriArenaClient.h"
#include "time.h"

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}


void AgriArenaClient::config(String URL, const char *certificate) {
    // this->client.setCACert(certificate);

    http.begin(this->client, URL);
    http.addHeader("Content-Type", "application/json");
}


void AgriArenaClient::send(DynamicJsonDocument data, const uint64_t &chipId, IPAddress IP) {

    data["did"] = chipId;
    data["ip"] = IP;
    data["timestamp"] = getTime();


    String jsonString;
    serializeJson(data, jsonString);
    Serial.println(jsonString);


    int httpResponseCode = this->http.POST(jsonString);

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
    } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
}