#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>

// ---------------- WIFI ----------------
#define WIFI_SSID "Nokia3310"
#define WIFI_PASSWORD "ankit111"

// -------------- FIREBASE --------------
#define DATABASE_URL "https://smarthealthesp32-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define DATABASE_SECRET "FZQEMMyoIYZfAQcmBaN81HczCalT4wUyLiZ7SXFC"

// -------------- DHT -------------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// -------------- PULSE -----------------
#define PULSE_PIN 34

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int heartRate = 0;

void setup() {
  Serial.begin(115200);

  dht.begin();

  // WiFi connect
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected");

  // Firebase config
  config.database_url = DATABASE_URL;
  config.signer.tokens.legacy_token = DATABASE_SECRET;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Firebase connected");
}

void loop() {

  if (millis() - sendDataPrevMillis > 5000) {
    sendDataPrevMillis = millis();

    float temperature = dht.readTemperature();
    int pulseValue = analogRead(PULSE_PIN);

    // simple demo heart rate logic
    heartRate = map(pulseValue, 1500, 3000, 60, 120);

    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print(" | BPM: ");
    Serial.println(heartRate);

    // Send to Firebase
    Firebase.RTDB.setFloat(&fbdo, "/health/temperature", temperature);
    Firebase.RTDB.setInt(&fbdo, "/health/heartRate", heartRate);
  }
}







