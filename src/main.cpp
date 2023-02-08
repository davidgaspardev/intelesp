#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

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

IPAddress server(10, 1, 15, 59);
uint16_t port = 32354;
WiFiClient wifiClient;
PubSubClient client(wifiClient);
const char* clientId = "esp32";
const char* user = "admin";
const char* pass = "admin";

void setupMqttClient() {
  Serial.println("[+] (MQTT) Connecting");

  client.setServer(server, port);
}

void reconnectMqtt() {
  if(!client.connected()) {
    Serial.println("[+] (MQTT) Reconnecting");

    if(client.connect(clientId, 0, MQTTQOS1, 0, 0)) {
      Serial.println("[+] (MQTT) Reconnected");
    } else {
      delay(1000);
      Serial.println("[+] (MQTT) Try to reconnect again");
      reconnectMqtt();
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(460800);

  setupWifi();
  setupMqttClient();
}

unsigned int count = 0;

void loop() {
  reconnectMqtt();

  delay(1000);

  char msg[50];

  sprintf(msg, "Joven -> %d", count);

  client.publish("ESP32", msg);
  Serial.print("[+] Message sent: ");
  Serial.println(msg);

  count++;
}  // put your main code here, to run repeatedly: