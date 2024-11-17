#include <Arduino.h>
#define BLYNK_TEMPLATE_ID "TMPL3sEw8Vt2t" // Replace with your Blynk template ID
#define BLYNK_TEMPLATE_NAME "Quickstart Template" // Replace with your device name
#define BLYNK_AUTH_TOKEN "M0dKxY6YOWuesFa5EFUBKlKr3SGUjhkn"   // Replace with your token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Your Wi-Fi credentials
char ssid[] = "Siddardha Redmi Note 12 Pro+ 5G";      // Replace with your Wi-Fi SSID
char pass[] = "12345678";  // Replace with your Wi-Fi Password

#define VIRTUAL_PIN V2 
#define TRIG_PIN 13       // GPIO pin for Trigger
#define ECHO_PIN 12       // GPIO pin for Echo
#define HALL_SENSOR 14    // Analog pin for Hall sensor

int RPM = 0, rotationCount = 0;
unsigned long lastTime = 0;       // Time for RPM calculation
const unsigned long interval = 1000; // Time interval for RPM calculation (1 second)
const int THRESHOLD = 3200;      // ADC value for 3.3V (10-bit resolution)

// Variable to track Hall sensor state
bool lastRotationRegistered = false;
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void setup() {
  Serial.begin(115200);      // Start the Serial Monitor
  WiFi.begin(ssid, pass);
   pinMode(TRIG_PIN, OUTPUT); // Set TRIG_PIN as output
  pinMode(ECHO_PIN, INPUT);
  pinMode(HALL_SENSOR,INPUT);  
  WiFi.begin(ssid, pass);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Connect to Blynk server
  Serial.println("ESP32 connected to Blynk!");// Set ECHO_PIN as input
}

void loop() {
  // Measure distance using ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the echo duration
  float duration = pulseIn(`+                                                                                                             `               ECHO_PIN, HIGH);

  // Avoid division by zero in distance calculation
  int distance = 0;
  if (duration > 0) {
    distance = 337 - 110000 / duration; // Convert duration to distance in cm
  } else {
    Serial.println("Invalid duration detected!");
  }

  // Read Hall sensor voltage
  // Check if Hall sensor value corresponds to 3.3V and register rotation
  unsigned long lastTime = millis();
  while(millis()-lastTime<5000){
    float hallValue=analogRead(HALL_SENSOR);
    if (hallValue >= THRESHOLD && !lastRotationRegistered) {
    rotationCount++;
    lastRotationRegistered = true; // Prevent multiple registrations for the same 3.3V signal
  } else if (hallValue < THRESHOLD) {
    lastRotationRegistered = false; // Reset when voltage drops below the threshold
  }
  }
    RPM = rotationCount* 6.28; // Convert rotations per second to RPM
    rotationCount = 0;        // Reset the rotation count for the next interval
    // Update the time

  // Print results to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(duration);
  Serial.println(" m/s");

  Serial.print("RPM: ");
  Serial.println(RPM);
  if(RPM==0) Serial.println("Not moving");
  else Serial.println(distance/RPM);
  Blynk.run();
  Blynk.virtualWrite(VIRTUAL_PIN, distance);

  // Short delay before the next reading
  delay(100); // Small delay for stability
}#include <Arduino.h>
#define BLYNK_TEMPLATE_ID "TMPL3sEw8Vt2t" // Replace with your Blynk template ID
#define BLYNK_TEMPLATE_NAME "Quickstart Template" // Replace with your device name
#define BLYNK_AUTH_TOKEN "M0dKxY6YOWuesFa5EFUBKlKr3SGUjhkn"   // Replace with your token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Your Wi-Fi credentials
char ssid[] = "Siddardha Redmi Note 12 Pro+ 5G";      // Replace with your Wi-Fi SSID
char pass[] = "12345678";  // Replace with your Wi-Fi Password

#define VIRTUAL_PIN V2 
#define TRIG_PIN 13       // GPIO pin for Trigger
#define ECHO_PIN 12       // GPIO pin for Echo
#define HALL_SENSOR 14    // Analog pin for Hall sensor

int RPM = 0, rotationCount = 0;
unsigned long lastTime = 0;       // Time for RPM calculation
const unsigned long interval = 1000; // Time interval for RPM calculation (1 second)
const int THRESHOLD = 3200;      // ADC value for 3.3V (10-bit resolution)

// Variable to track Hall sensor state
bool lastRotationRegistered = false;
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void setup() {
  Serial.begin(115200);      // Start the Serial Monitor
  WiFi.begin(ssid, pass);
   pinMode(TRIG_PIN, OUTPUT); // Set TRIG_PIN as output
  pinMode(ECHO_PIN, INPUT);
  pinMode(HALL_SENSOR,INPUT);  
  WiFi.begin(ssid, pass);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Connect to Blynk server
  Serial.println("ESP32 connected to Blynk!");// Set ECHO_PIN as input
}

void loop() {
  // Measure distance using ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the echo duration
  float duration = pulseIn(`+                                                                                                             `               ECHO_PIN, HIGH);

  // Avoid division by zero in distance calculation
  int distance = 0;
  if (duration > 0) {
    distance = 337 - 110000 / duration; // Convert duration to distance in cm
  } else {
    Serial.println("Invalid duration detected!");
  }

  // Read Hall sensor voltage
  // Check if Hall sensor value corresponds to 3.3V and register rotation
  unsigned long lastTime = millis();
  while(millis()-lastTime<5000){
    float hallValue=analogRead(HALL_SENSOR);
    if (hallValue >= THRESHOLD && !lastRotationRegistered) {
    rotationCount++;
    lastRotationRegistered = true; // Prevent multiple registrations for the same 3.3V signal
  } else if (hallValue < THRESHOLD) {
    lastRotationRegistered = false; // Reset when voltage drops below the threshold
  }
  }
    RPM = rotationCount* 6.28; // Convert rotations per second to RPM
    rotationCount = 0;        // Reset the rotation count for the next interval
    // Update the time

  // Print results to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(duration);
  Serial.println(" m/s");

  Serial.print("RPM: ");
  Serial.println(RPM);
  if(RPM==0) Serial.println("Not moving");
  else Serial.println(distance/RPM);
  Blynk.run();
  Blynk.virtualWrite(VIRTUAL_PIN, distance);

  // Short delay before the next reading
  delay(100); // Small delay for stability
}