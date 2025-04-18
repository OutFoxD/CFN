#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Replace these:
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

const char* mqtt_server = "192.168.188.25"; // e.g., "192.168.178.42"

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  // Loop until reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266-" + String(ESP.getChipId());

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // You can subscribe here if needed
      // client.subscribe("home/esp/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 sec");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Simulate a sensor read
  int analogValue = analogRead(A0);
  String payload = String(analogValue);

  // Publish to topic
  client.publish("home/esp8266/analog", payload.c_str());
  Serial.println("Published: " + payload);

  delay(5000);  // Wait 5 seconds
}
