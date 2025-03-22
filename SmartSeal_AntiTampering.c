#include <WiFi.h>

// WiFi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Pin definitions
#define REED_PIN 14     // GPIO for Reed switch
#define VIBRATION_PIN 27 // GPIO for Vibration sensor
#define ALERT_PIN 16    // GPIO for LED/Buzzer

void setup() {
  Serial.begin(115200);
  pinMode(REED_PIN, INPUT_PULLUP);   // Reed switch, triggered when opened
  pinMode(VIBRATION_PIN, INPUT);     // Vibration sensor
  pinMode(ALERT_PIN, OUTPUT);        // LED/Buzzer alert
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int reedState = digitalRead(REED_PIN);
  int vibrationState = digitalRead(VIBRATION_PIN);
  
  if (reedState == LOW || vibrationState == HIGH) { // Tamper detected
    Serial.println("Tampering Detected!");
    digitalWrite(ALERT_PIN, HIGH); // Trigger alert
    sendAlert(); // Send alert via cloud/app (define this function as per platform)
    delay(2000); // Wait before re-checking
  } else {
    digitalWrite(ALERT_PIN, LOW);  // No tampering
  }
  delay(500); // Loop delay
}

void sendAlert() {
  // Function to send an alert notification, e.g., via Blynk, ThingSpeak, or Firebase
  Serial.println("Sending alert to user...");
  // Code to integrate with cloud/app service
}
