
#include <WiFiClientSecure.h>
#include "WifiConfiguration.h"


WifiConfiguration::WifiConfiguration() : ssid(""), password(""){}
WifiConfiguration::WifiConfiguration(std::pair<String, String> &wifi) : ssid(wifi.first), password(wifi.second){}
WifiConfiguration::WifiConfiguration(String ssid, String password) : ssid(ssid), password(password){}

bool WifiConfiguration::isEmpty() {
    return ssid == "" || password == "";
}

bool WifiConfiguration::connect(const uint8_t& LED_PIN) {
    int retries = 0;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED  && retries < 30) {
        digitalWrite(LED_PIN, HIGH);
        delay(50);
        digitalWrite(LED_PIN, LOW);
        delay(50);
        digitalWrite(LED_PIN, HIGH);
        delay(50);
        digitalWrite(LED_PIN, HIGH);
        delay(1000);
        Serial.print(".");
        retries++;
    }
    return WiFi.status() == WL_CONNECTED;
}

IPAddress WifiConfiguration::reconnect(const uint8_t& LED_PIN) {
    this->connect(LED_PIN);
    return this->getIP();
}

bool WifiConfiguration::config(const uint8_t& LED_PIN) {
    if (this->isEmpty()){
        Serial.println("Wifi credential is empty");
        return false;
    }
    if (!this->connect(LED_PIN)) {
        Serial.println("Failed to connect to WiFi");
        return false;
    }
    Serial.println("WiFi connected");
    return true;
}

bool WifiConfiguration::isAlive(const uint8_t& LED_PIN) {
    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }
    return true;
}

IPAddress WifiConfiguration::getIP() {
    return WiFi.localIP();
}
