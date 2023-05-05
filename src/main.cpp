#include <Arduino.h>
#include <Wifi.h>
#include <LedOnboard.h>
#include <InputPin.h>
#include <Time.h>
#include <MqttClient.h>

#define WLAN_SSID ".Intelbras Coletores"
#define WLAN_PASS "Intelbras@Coletores2018"

#define PINS_MAX 6

Wifi wifi;
Time timeNow;
LedOnboard ledOnboard;
MqttClient mqttClient;

// All pins to listening signal
InputPin pins[PINS_MAX] = {
  InputPin(GPIO_NUM_12),
  InputPin(GPIO_NUM_13),
  InputPin(GPIO_NUM_14),
  InputPin(GPIO_NUM_15),
  InputPin(GPIO_NUM_16),
  InputPin(GPIO_NUM_17)
};
char MAC[18];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(460800);

  // Setuping Wifi
  wifi.connect(WLAN_SSID, WLAN_PASS);

  // Setuping MQTT Client
  IPAddress ipAddr(10, 1, 15, 59);
  uint16_t port = 32354;
  mqttClient.setup(ipAddr, port, &wifi.client);

  // Setuping time now
  timeNow.setup();

  strcpy(MAC, wifi.macAddress().c_str());
}

void handlePin(InputPin *pin) {
    char msg[90]; // {"pin":13,"mac":"C8:F0:9E:51:64:F0","signal":"HIGH","date":"2023-04-28T20:12:41Z"}

   if (pin->signalChanged()) {
    char signal[5];
    if(pin->getSignal() == HIGH) {
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
      MAC,
      signal,
      timeNow.getISOString()
    );

    if(!mqttClient.publish("ESP32", msg)) {
      mqttClient.reconnect();
    }
    Serial.printf("[+] Message sent: %s\n", msg);
  }
}

void loop() {
  for(int i = 0; i < PINS_MAX; i++) {
    handlePin(&pins[i]);
  }

  delay(32);
}