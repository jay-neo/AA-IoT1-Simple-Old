#include <ArduinoJson.h>
#include "Sensors.h"
#include <DHT.h>


Sensors::Sensors(const uint8_t dht_pin, const uint8_t dht_type)
    : dht(dht_pin, dht_type) {}

// Sensors::~Sensors() {}

void Sensors::read() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (isnan(humidity)) {
        Serial.println("Failed to read from DHT Sensor: Humidity");
    }
    if (isnan(temperature)) {
        Serial.println("Failed to read from DHT Sensor: Temperature");
    }
    res["humidity"] = humidity;
    res["temperature"] = temperature;
}

DynamicJsonDocument Sensors::get() {
    DynamicJsonDocument doc(JSON_OBJECT_SIZE(res.size()+4));
    for (const auto &kv : res) {
        doc[kv.first.c_str()] = kv.second;
    }
    return doc;
}