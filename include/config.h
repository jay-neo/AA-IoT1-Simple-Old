#include <Arduino.h>

#include "AgriArenaClient.h"
#include "WifiConfiguration.h"
#include "Sensors.h"
// #include "RGB_LED.cpp"

#define SWITCH 5
#define DHT_PIN 15
#define DHT_TYPE DHT11

const String SSID = "";
const String PASSWORD = "";
const String ENDPOINT = "";
const char *TLS_CERTIFICATE = R"KEY(

)KEY";

const uint8_t R = 15;
const uint8_t G = 14;
const uint8_t B = 13;

uint8_t LED[3] = {15, 14, 13};
