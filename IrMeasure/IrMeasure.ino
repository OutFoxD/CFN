const int ledPin = D0;          // Your external LED (GPIO16 / D0)
const int irSensorPin = A0;     // IR sensor analog output

unsigned long lastReadTime = 0;
const unsigned long interval = 200;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // LED off initially

  Serial.println("IR Sensor Measurement with 60-char Bar");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastReadTime >= interval) {
    lastReadTime = currentTime;

    digitalWrite(ledPin, HIGH);  // LED on
    delay(100);                  // IR settle time
    int sensorValue = analogRead(irSensorPin);
    digitalWrite(ledPin, LOW);   // LED off

    // Map to percentage (0–100%)
    int percentage = map(sensorValue, 0, 1023, 0, 100);

    // Build a bar of 60 characters max
    int barLength = map(percentage, 0, 100, 0, 60);
    String bar = "";
    for (int i = 0; i < barLength; i++) {
      bar += '|';
    }

    // Optional: pad to 60 for consistent width
    while (bar.length() < 60) bar += ' ';

    // Print to Serial (great for Serial Monitor)
    Serial.print("IR: ");
    Serial.print(sensorValue);
    Serial.print(" (");
    Serial.print(percentage);
    Serial.println("%) " + bar);
  }
}
