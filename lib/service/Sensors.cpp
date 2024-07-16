#include <ArduinoJson.h>
#include "Sensors.h"
#include <DHT.h>


Sensors::Sensors(const uint8_t dht_pin, const uint8_t dht_type, const uint8_t _soil_moisture_pin)
    : dht(dht_pin, dht_type), soil_moisture_pin(_soil_moisture_pin) {}

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

    int soilMoistureValue = analogRead(soil_moisture_pin);
    float moisture = (100 - ((soilMoistureValue / 4095.00) * 100));


    res["humidity"] = humidity;
    res["temperature"] = temperature;
    res["moisture"] = moisture;
}

DynamicJsonDocument Sensors::get() {
    DynamicJsonDocument doc(JSON_OBJECT_SIZE(res.size() + 2));
    for (const auto &kv : res) {
        doc[kv.first.c_str()] = kv.second;
    }
    return doc;
}