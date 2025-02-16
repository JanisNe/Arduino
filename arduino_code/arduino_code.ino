#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "BV5900";
const char* password = "123456789";

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Telpas numurs nevar izmantot " " vai / zīmes
String room = "JanisNea";
String serverName = "https://janisneaa.pythonanywhere.com/";

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

float temp;
float hum;

void setup() {
  Serial.begin(115200); 

  dht.begin();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      hum = dht.readHumidity();
      temp = dht.readTemperature();

      String serverPath = serverName + room + "/" + String(temp, 2) + "/" + String(hum, 2) + "/";
      
      http.begin(serverPath);
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}