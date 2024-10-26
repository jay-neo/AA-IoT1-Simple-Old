#include "config.hpp"

Sensors sensor;
WifiConfiguration wifi(WIFI_SSID, WIFI_PASSWORD);
OLED display(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_ADDRESS);

AgriArenaClient client(sensor, display);

void setup() {
    Serial.begin(115200);

    Serial.println("Starting...");
    if(DHT_PIN) {
        client.set_dht(DHT_PIN, DHT_TYPE);
    }
    if(MOISTURE_PIN) {
        client.set_moisture_pin(MOISTURE_PIN);
    }
    if(PH_PIN) {
        client.set_ph_pin(PH_PIN);
    }
    if(NPK_RE && NPK_DE && NPK_RX && NPK_TX) {
        client.set_npk(NPK_RE, NPK_DE, NPK_RX, NPK_TX, NPK_CODE, NPK_BAUD_RATE);
    }

    if(!wifi.config()) {
        Serial.println("Wifi not configured successfully!");
        display.error("Error: WiFi Configuration");
        esp_deep_sleep_start();
    }
    if(!client.config(ENDPOINT, TLS_CERTIFICATE)) {
        Serial.println("Client not configured successfully!");
        display.error("Error: Client Configuration");
        esp_deep_sleep_start();
    }
}

void loop() {
    if(wifi.isAlive()) {
        client.read_all();
        client.send_all();
    } else {
        Serial.println("Wifi disconnectd!");
        display.error("Error: WiFi Disconnected");
    }
    delay(5000);
}