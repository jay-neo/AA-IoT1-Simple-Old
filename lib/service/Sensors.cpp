#include "Sensors.h"

#include <ArduinoJson.h>
#include <DHT.h>

// Public Constructor
Sensors::Sensors() : dht(nullptr) {}

// Public Destructor
Sensors::~Sensors() {
    if(dht != nullptr) {
        delete dht;
    }
}

// Public Setter
void Sensors::set_ph_pin(const uint8_t _pin) {
    this->ph_pin = _pin;
    pinMode(this->ph_pin, INPUT);
}
void Sensors::set_moisture_pin(const uint8_t _pin) { this->moisture_pin = _pin; }
void Sensors::set_dht(const uint8_t _pin, const uint8_t _type) {
    if(dht != nullptr) {
        delete dht;
    }
    this->dht_pin = _pin;
    this->dht_type = _type;
    this->dht = new DHT(this->dht_pin, this->dht_type);
    this->dht->begin();
}
void Sensors::set_npk(const uint8_t _RE, const uint8_t _DE, const uint8_t _RX, const uint8_t _TX,
                      const uint8_t code[]) {}

// Private Getter
float Sensors::get_ph() {}
float Sensors::get_moisture() {
    int soilMoistureValue = analogRead(this->moisture_pin);
    float moisture = (100 - ((soilMoistureValue / 4095.00) * 100));
    // float moisture =  map(soilMoistureValue, 0, 4095, 0, 100);

    if(isnan(soilMoistureValue)) {
        Serial.println("Failed to read from DHT Sensor: Humidity");
    }
    return moisture;
}
void Sensors::read_dht(float &humidity, float &temperature) {
    humidity = this->dht->readHumidity();
    temperature = this->dht->readTemperature();
    if(isnan(humidity)) {
        Serial.println("Failed to read from DHT Sensor: Humidity");
    }
    if(isnan(temperature)) {
        Serial.println("Failed to read from DHT Sensor: Temperature");
    }
}
void Sensors::read_npk(float &N, float &P, float &K) {}

// Public Utilities
void Sensors::read_all() {
    // pH
    if(this->ph_pin != 0) {
        res["ph"] = this->get_ph();
    }
    // Soil Moisture
    if(this->moisture_pin != 0) {
        this->res["moisture"] = this->get_moisture();
    }
    // DHT
    if(this->dht_pin != 0) {
        float humidity = 0, temperature = 0;
        this->read_dht(humidity, temperature);
        this->res["humidity"] = humidity, res["temperature"] = temperature;
    }
    // NPK
    if(this->npk_pin != 0) {
        float N = 0, P = 0, K = 0;
        this->read_npk(N, P, K);
        res["nitrogen"] = N, res["phosphorus"] = P, res["potassium"] = K;
    }
}

// Public Getter
DynamicJsonDocument Sensors::get() {
    DynamicJsonDocument doc(JSON_OBJECT_SIZE(res.size() + 2));
    for(const auto &kv : res) {
        doc[kv.first.c_str()] = kv.second;
    }
    return doc;
}