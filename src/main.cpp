#include <Arduino.h>
#include <WiFi.h>

#define WLAN_SSID ".Intelbras Coletores"
#define WLAN_PASS "Intelbras@Coletores2018"

void setupWifi() {
  // Set credential to WiFi access point
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  Serial.print("[+] Connecting on Wifi ");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n[+] Wifi connected");
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}