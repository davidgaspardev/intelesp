#include <Arduino.h>
#include <Wifi.h>
#include <PubSubClient.h>
#include <LedOnboard.h>
#include <esp_system.h>

#define WLAN_SSID ".Intelbras Coletores"
#define WLAN_PASS "Intelbras@Coletores2018"

LedOnboard ledOnboard;
Wifi wifi;

IPAddress server(10, 1, 15, 59);
uint16_t port = 32354;
PubSubClient client(wifi.client);
const char* clientId = "esp32";

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

void setupMqttClient() {
  Serial.println("[+] (MQTT) Connecting");

  client.setServer(server, port);
  reconnectMqtt();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(460800);

  pinMode(GPIO_NUM_13, INPUT_PULLDOWN);

  wifi.connect(WLAN_SSID, WLAN_PASS);
  setupMqttClient();
}

unsigned int count = 0;
uint8_t lastSignal = LOW;
char msg[100];

void loop() {
  // Serial.print("[+] Message sent: ");
  uint8_t signal = digitalRead(GPIO_NUM_13);
  if (signal == HIGH && lastSignal == LOW) {
    String mac = wifi.macAddress();
    // Serial.println(mac.c_str());
    sprintf(msg, "{\"pin\":13,\"mac\":\"%s\"}", mac.c_str());
    if(!client.publish("ESP32", msg)) {
      reconnectMqtt();
    };
    Serial.print("[+] Message sent: ");
    Serial.println(msg);
    count++;
    lastSignal = signal;
    return;
  } else {
    lastSignal = signal;
  }

  if (signal == HIGH) {
    ledOnboard.turnOn();
  } else {
    ledOnboard.turnOff();
  }

  delay(100);
}