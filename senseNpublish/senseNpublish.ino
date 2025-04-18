#include <ESP8266WiFi.h>
#include <PubSubClient.h>

extern "C" {
  #include "user_interface.h"
}

const char* ssid = "TPADB PRGAV4202N";
const char* password = "321mLOOu0QdUYDwt";
const char* mqtt_server = "192.168.188.62"; 

const int ledPin = D4;
const int irSensorPin = A0;

const float threshold = 2; // in Volts

float sensorValue = 0;

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastReadTime = 0;
const unsigned long interval = 3000; // 1s

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266-IR")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  client.setServer(mqtt_server, 1883);

  wifi_set_sleep_type(LIGHT_SLEEP_T); // SDK-level call
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  digitalWrite(ledPin, LOW);
  delay(100);
  sensorValue = analogRead(irSensorPin) * 0.0051;  
  digitalWrite(ledPin, HIGH);

  Serial.print("Motor Volts: ");
  Serial.println(sensorValue);

  if (sensorValue > threshold) {
    Serial.println("⚠ Motor active! Sending MQTT alert.");
    client.publish("home/pferdalert/trigger", "PFERDALERT");
    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
  }
  
  delay(interval);
}
