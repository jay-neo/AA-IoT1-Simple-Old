#include "config.hpp"

const uint64_t chipId = ESP.getEfuseMac();
uint8_t retries = 0;

WifiConfiguration wifi(WIFI_SSID, WIFI_PASSWORD);
AgriArenaClient client;
Sensors sensor;

void setup() {
    Serial.begin(115200);
    // configureLED(LED);
    // pinMode(SWITCH, INPUT);

    Serial.println("Starting...");
    if(DHT_PIN) {
        sensor.set_dht(DHT_PIN, DHT_TYPE);
    }
    if(MOISTURE_PIN) {
        sensor.set_moisture_pin(MOISTURE_PIN);
    }
    if(NPK_RE && NPK_DE && NPK_RX && NPK_TX) {
        sensor.set_npk(NPK_RE, NPK_DE, NPK_RX, NPK_TX, NPK_CODE);
    }

    // setColor(10, 0, 0); setColor(0, 10, 0); setColor(0, 0, 10);

    if(!wifi.config(R)) {
        Serial.println("Wifi not configured successfully!");
        return;
    }
    if(!client.config(ENDPOINT, TLS_CERTIFICATE)) {
        Serial.println("Client not configured successfully!");
        return;
    }

    // sensor.read_all(), setColor(10, 0, 0, 100), delay(1000);
    // sensor.read_all(), setColor(0, 10, 0, 100), delay(1000);
    // sensor.read_all(), setColor(0, 0, 10, 100), delay(1000);
}

bool isPressed = false;
unsigned long pressTime = 0;

void loop() {
    if(wifi.isAlive()) {
        sensor.read_all();
        client.send(sensor.get());

        //     if (digitalRead(SWITCH) == HIGH) {
        //         if (!isPressed) {
        //             pressTime = millis();
        //             Sensor.read();
        //             Client.send(Sensor.get(), chipId, IP);
        //         }
        //     }
        // } else if (!Wifi.isAlive(R) && retries < 2){
        //     Serial.println("WiFi Disconnected");
        //     retries++;
        //     IP = Wifi.reconnect(R);
    } else {
        // setColor(10, 0, 0, 10);
        Serial.println("Wifi disconnectd!");
    }

    delay(5000);
}