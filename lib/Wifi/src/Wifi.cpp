#include "Wifi.h"

void Wifi::connect(const char* ssid, const char* pass) {
    strcpy(this->ssid, ssid);
    strcpy(this->pass, pass);

    WiFi.begin(ssid, pass);

    int timeout_counter = 0;

    Serial.print("[+] Connecting to Wifi ");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
        timeout_counter++;
        if(timeout_counter >= 60){
            Serial.println("\n[+] Error to connect on the Wifi, RESTARTING ESP32");
            ESP.restart();
        }
    }

    Serial.println("\n[+] Connected on the Wifi");
}

bool Wifi::isConnected() {
    if ( WiFi.status() != WL_CONNECTED ) {
        return false;
    } else {
        return true;
    }
}

String Wifi::macAddress() {
    return WiFi.macAddress();
}