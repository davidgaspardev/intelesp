#include "Wifi.h"

void Wifi::connect(const char* ssid, const char* pass) {
    strcpy(this->ssid, ssid);
    strcpy(this->pass, pass);

    WiFi.begin(ssid, pass);

    Serial.print("[+] Connecting to Wifi ");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\n[+] Connected on the Wifi");
}

String Wifi::macAddress() {
    return WiFi.macAddress();
}