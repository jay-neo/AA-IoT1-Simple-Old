#ifndef SENSORS_H
#define SENSORS_H

#include <ArduinoJson.h>
#include <DHT.h>

#include <map>

class Sensors {
    uint8_t dht_pin;
    uint8_t dht_type;
    uint8_t moisture_pin;
    uint8_t ph_pin;
    uint8_t npk_pin;

    DHT *dht;
    std::map<String, float> res;

    // Private Getter
    float get_ph();
    float get_moisture();
    float get_humidity();
    float get_temperature();
    void read_dht(float &humidity, float &temperature);
    void read_npk(float &N, float &P, float &K);

   public:
    Sensors();
    ~Sensors();

    // Public Getter
    DynamicJsonDocument &get();

    // Pubic Setter
    void set_ph_pin(const uint8_t _pin);
    void set_moisture_pin(const uint8_t _pin);
    void set_dht(const uint8_t _pin, const uint8_t _type);
    void set_npk(const uint8_t _RE, const uint8_t _DE, const uint8_t code[]);

    // Public Utilities
    void read_all();
};

#endif