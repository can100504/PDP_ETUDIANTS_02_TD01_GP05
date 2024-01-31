#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <WiFiClient.h>


#define BLYNK_TEMPLATE_ID "TMPL5PWhkRhOt"
#define BLYNK_TEMPLATE_NAME "Blynk"
#define BLYNK_AUTH_TOKEN "etrlypNQTR4N0HJHz5UY38gq12XvRBXP"

#include <BlynkSimpleEsp32.h>


// Define the pins that we will use
#define SENSOR 33
#define LED 26
#define DHTTYPE DHT11
#define BLYNK_PRINT Serial

DHT_Unified dht(SENSOR, DHTTYPE);

char ssid[] = "iPhone de angelo";
char pass[] = "angelooo";


void setup() {
  // Setup pins
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  // Begin serial communication
  Serial.begin(9600);
  delay(100);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.run();
  Serial.println(">COUCOUUUUuu");
  // Start listening to the DHT11
  dht.begin();

  sensors_event_t event;

  // Get temperature event and print its value
  float temp_measure = -999.0;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    temp_measure = event.temperature;
  }

  // Get humidity event and print its value.
  float relative_humidity_measure = -999.0;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    relative_humidity_measure = event.relative_humidity;
  }

  // Send data to Blynk
  //HUMIDITE
  Blynk.virtualWrite(0,event.relative_humidity);
  //TEMPERATURE
  Blynk.virtualWrite(1,event.temperature);
 

  Serial.println("Going to sleep for 5 seconds...");
  delay(100);
  ESP.deepSleep(5e6);
}

void loop() {
  
}