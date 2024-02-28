#include "MyWifi.h"

void MyWifi::connect(const char* ssid, const char* pass) {
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

bool MyWifi::isConnected() {
    if ( WiFi.status() != WL_CONNECTED ) {
        return false;
    } else {
        return true;
    }
}

String MyWifi::macAddress() {
    return WiFi.macAddress();
}