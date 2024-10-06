#include "AgriArenaClient.h"
#include "RGB_LED.cpp"
#include "Sensors.h"
#include "WifiConfiguration.h"

const uint8_t SWITCH = 5;
const uint8_t DHT_PIN = 4;
const uint8_t DHT_TYPE = DHT11;
const uint8_t MOISTURE_PIN = 11;

const String ENDPOINT = "http://localhost:3000/api/iot";

const String WIFI_SSID = "";
const String WIFI_PASSWORD = "";
const char *TLS_CERTIFICATE = R"KEY(

)KEY";

const uint8_t R = 15;  // LED

// uint8_t LED[3] = {15, 14, 13};
