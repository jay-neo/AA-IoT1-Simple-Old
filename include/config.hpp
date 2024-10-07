#include "AgriArenaClient.h"
#include "RGB_LED.cpp"
#include "Sensors.h"
#include "WifiConfiguration.h"

// For General Purpose
const uint8_t SWITCH = 0;
const uint8_t R = 15;
const uint8_t LED[3] = {0, 0, 0};

// For DHT Sensor
const uint8_t DHT_PIN = 0;
const uint8_t DHT_TYPE = DHT11;

// For Moisture Sensor
const uint8_t MOISTURE_PIN = 0;

// For PH Sensor
const uint8_t PH_POS = 0;
const uint8_t PH_NEG = 0;

// For NPK Sensor
const uint8_t NPK_RE = 0;
const uint8_t NPK_DE = 0;
const uint8_t NPK_RX = 0;
const uint8_t NPK_TX = 0;
const uint8_t NPK_CODE[] = {};

// For Server Endpoint
const String ENDPOINT = "http://localhost:3000/api/iot";

// For ESP32 Internet Connection
const String WIFI_SSID = "";
const String WIFI_PASSWORD = "";
const char *TLS_CERTIFICATE = R"KEY(

)KEY";
