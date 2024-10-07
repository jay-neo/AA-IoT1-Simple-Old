#include "AgriArenaClient.h"

#include <ArduinoJson.h>

#include "time.h"

AgriArenaClient::AgriArenaClient() : ntpServer("pool.ntp.org") {}

String AgriArenaClient::getTime() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) {
        return "Unknown";
    }
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%H:%M:%S - %d %B, %Y", &timeinfo);
    //   strftime(buffer, sizeof(buffer), "%A, %B %d %Y %H:%M:%S", &timeinfo);

    // Debugging
    Serial.print("Time = ");
    Serial.println(buffer);

    return String(buffer);
}

bool AgriArenaClient::config(const String &URL, const char *certificate) {
#ifdef USE_HTTPS
    client.setCACert(certificate);
#endif

    // Endpoint configuration
    http.begin(client, URL);
    http.addHeader("Content-Type", "application/json");

    // Experiment Time configuration
    long gmtOffset_sec = 19800;  // IST offset: 5 hours 30 minutes (19800 seconds)
    int daylightOffset_sec = 0;  // No daylight saving in India
    configTime(gmtOffset_sec, daylightOffset_sec, this->ntpServer);

    // Device ID configuration
    this->deviceId = ESP.getEfuseMac();

    // xTaskCreatePinnedToCore(
    //     timeTask,          // Task function
    //     "TimeTask",        // Name of the task (for debugging)
    //     4096,              // Stack size (in words)
    //     this,              // Task input parameter (this instance)
    //     1,                 // Priority of the task
    //     &timeTaskHandle,   // Task handle
    //     1                  // Core where the task should run
    // );

    // Debugging
    Serial.print("NTP Server");
    Serial.println(this->ntpServer);
}

void AgriArenaClient::send(DynamicJsonDocument data) {
    data["iot"] = this->deviceId;
    data["timestamp"] = this->getTime();

    String jsonString;
    serializeJson(data, jsonString);

    // Debugging
    Serial.println(jsonString);

    int httpResponseCode = http.POST(jsonString);
    if(httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
    } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
}

// void AgriArenaClient::timeTask(void* pvParameters) {
//     AgriArenaClient* client = static_cast<AgriArenaClient*>(pvParameters);
//     while (true) {
//         // Update the time every hour (3600000 milliseconds)
//         vTaskDelay(3600000 / portTICK_PERIOD_MS);
//         struct tm timeinfo;
//         if (!getLocalTime(&timeinfo)) {
//             Serial.println("Failed to obtain time");
//         } else {
//             char timeStringBuff[50];
//             strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);
//             Serial.println(String(timeStringBuff)); // Print the time for debugging
//         }
//     }
// }