#include "AgriArenaClient.h"
#include "WifiConfiguration.h"
#include "Sensors.h"
// #include "RGB_LED.cpp"


const uint8_t SWITCH = 5;
const uint8_t DHT_PIN = 4;
const uint8_t DHT_TYPE = DHT11;
const uint8_t SOIL_MOISTURE_PIN = 11;


const String SSID = "";
const String PASSWORD = "";
const String ENDPOINT = "";
const char *TLS_CERTIFICATE = R"KEY(

)KEY";

const uint8_t R = 15; // LED


// uint8_t LED[3] = {15, 14, 13};
