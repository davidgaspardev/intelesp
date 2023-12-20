#include <Arduino.h>
#include <Wifi.h>
#include <LedOnboard.h>
#include <InputPin.h>
#include <Time.h>
#include <MqttClient.h>

#define WLAN_SSID ".Intelbras Coletores"
#define WLAN_PASS "Intelbras@Coletores2018"

#define PINS_MAX 1

Wifi wifi;
Time timeNow;
LedOnboard ledOnboard;
MqttClient mqttClient;

// All pins to listening signal
InputPin pins[PINS_MAX] = {
  InputPin(GPIO_NUM_33)
};

typedef struct retained_info {
  char macAddress[18];
  char* time;
} retained_info_t;

retained_info_t info;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(460800);

  // Setuping Wifi
  wifi.connect(WLAN_SSID, WLAN_PASS);

  // Define broker client id as macAdress
  strcpy(mqttClient.clientId, wifi.macAddress().c_str());

  // Setuping MQTT Client
  IPAddress ipAddr(10, 1, 15, 59);
  uint16_t port = 32103;
  mqttClient.setup(ipAddr, port, &wifi.client);

  // Setuping time now
  timeNow.setup();

  strcpy(info.macAddress, wifi.macAddress().c_str());

  Serial.println("Saindo SETUP");
}

void handlePin(InputPin *pin) {
   char msg[90]; // {"pin":13,"mac":"C8:F0:9E:51:64:F0","signal":"HIGH","date":"2023-04-28T20:12:41Z"}

   if (pin->signalChanged()) {
    Serial.printf("Signal Changed");
    char signal[5];
    if(pin->getSignal() != HIGH) {  /** need to do like that, 'cause we are using GND font */
      strcpy(signal, "HIGH");
      ledOnboard.turnOn();
    } else {
      strcpy(signal, "LOW");
      ledOnboard.turnOff();
    }

    String mac = wifi.macAddress();
    sprintf(
      msg,
      "{\"pin\":%d,\"mac\":\"%s\",\"signal\":\"%s\",\"date\":\"%sZ\"}",
      pin->getNumber(),
      info.macAddress,
      signal,
      info.time
    );

    int t = 0;

    while(!mqttClient.publish("ESP32", msg)) {
      mqttClient.connect();
      t++;
      if(t > 10) {
        ESP.restart();
      }
    }
    Serial.printf("[+] Message sent: %s\n", msg);
  }
}

void loop() {
  info.time = timeNow.getISOString();

  for(int i = 0; i < PINS_MAX; i++) handlePin(&pins[i]);

  if(!mqttClient.isConnected()) {
    Serial.println("\n[+] MQTT Broker Conection Losted");
    mqttClient.connect();
  }

  if(!wifi.isConnected()) {
    Serial.println("\n[+] Wifi Conection Losted");
    wifi.connect(WLAN_SSID, WLAN_PASS);
  }

  mqttClient.loop();
  
}