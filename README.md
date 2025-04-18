## Pferdalert – ESP8266 IR Motor Monitor

This project uses an ESP8266 (NodeMCU ESP-12E) to monitor the operation of an **automatic pet feeder** by detecting motor activity through voltage changes.

The goal is to detect when the feeder motor runs, and send an MQTT alert when it does — enabling remote monitoring or notifications.

### 📦 Target Device
Tested with this feeder:
[Closer Pets C500 – 5-Meal Automatic Pet Feeder](https://closerpets.eu/products/five-meal-automatic-pet-feeder-with-digital-timer-c500-1?_pos=1&_sid=ed1502ae5&_ss=r)

### ⚙️ Features
- Monitors analog voltage from the motor(via A0)
- Sends MQTT alert (`"PFERDALERT"`) when motor is active
- Onboard LED flashes on activity
- WiFi-enabled (ESP8266)
- Power-optimized using **light sleep mode** between readings

### 🔋 Power Saving
- WiFi stays connected
- Light sleep enabled using `wifi_set_sleep_type(LIGHT_SLEEP_T)`
- Sensor is read every 3 seconds
- Onboard LED is normally off to save power

### 🧠 Dependencies
- ESP8266 Arduino Core
- PubSubClient (for MQTT)

