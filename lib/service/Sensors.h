#ifndef SENSORS_H
#define SENSORS_H

#include <ArduinoJson.h>
#include <DHT.h>
#include <map>

class Sensors {
    DHT dht;
    std::map<String, float> res;
public:
    Sensors(const uint8_t, const uint8_t);
    // ~Sensors();

    void read();
    DynamicJsonDocument get();

};



#endif