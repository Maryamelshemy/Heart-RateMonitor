
// Pin connected to the pulse sensor
const int pulsePin = A0;  

// Variables for BPM calculation
unsigned long lastBeatTime = 0;
int beatCount = 0;
float bpm = 0;
bool pulseDetected = false;

void setup() {
  Serial.begin(9600);
  pinMode(pulsePin, INPUT);
  Serial.println("Place your finger on the sensor...");
}

void loop() {
  int sensorValue = analogRead(pulsePin);

  // Threshold to detect a pulse (tweak depending on sensor)
  if (sensorValue > 512 && !pulseDetected) {
    pulseDetected = true;
    unsigned long currentTime = millis();

    if (lastBeatTime > 0) {
      unsigned long delta = currentTime - lastBeatTime;
      bpm = 60000.0 / delta;  // BPM calculation
      Serial.print("Heart Rate: ");
      Serial.print(bpm);
      Serial.println(" BPM");
    }
    lastBeatTime = currentTime;
  }

  // Reset detection flag
  if (sensorValue < 512) {
    pulseDetected = false;
  }
}
