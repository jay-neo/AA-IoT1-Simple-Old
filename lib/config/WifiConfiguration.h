#ifndef WIFICONFIGURATION_H
#define WIFICONFIGURATION_H

#include <WiFiClientSecure.h>

class WifiConfiguration {
    String ssid;
    String password;
public:
    WifiConfiguration();
    WifiConfiguration(std::pair<String, String>&);
    WifiConfiguration(String ssid, String password);

    bool isEmpty() ;
    bool connect(const uint8_t&);
    IPAddress reconnect(const uint8_t&);
    bool config(const uint8_t&);
    bool isAlive(const uint8_t&);
    IPAddress getIP();
};

#endif