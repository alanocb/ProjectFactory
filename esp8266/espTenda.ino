#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define WIFI_NAME   ""
#define WIFI_PASS   ""

#define DHTPIN D2     // temp humidity sensor
#define DHTTYPE DHT11  

#define LED_PIN D1 // LED
#define FLAME D4 // flame sensor
#define ALARM D8 // alarm fire
#define RED_PIN D5 // RGB Red pin
#define GREEN_PIN D6 // RGB Green pin
#define BLUE_PIN D7 // RGB Blue pin

#define HEARTBEAT_PIN A0 // KY-039 heartbeat sensor pin

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);

const int sampleWindow = 2000; // Sample window width in ms (2 seconds)
unsigned long lastBeatTime = 0;
int beatCount = 0;
int bpm = 0;

void setup(void) {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FLAME, INPUT);
  pinMode(ALARM, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(HEARTBEAT_PIN, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
 
  Serial.print("IP obtained: ");
  Serial.println(WiFi.localIP());

  server.on("/led", HTTP_POST, []() {
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, server.arg("plain"));

    if (error) {
      server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }

    if (doc.containsKey("state")) {
      bool newState = doc["state"];
      digitalWrite(LED_PIN, newState ? HIGH : LOW);

      DynamicJsonDocument response(128);
      response["success"] = true;
      response["message"] = "LED toggled";
      String jsonResponse;
      serializeJson(response, jsonResponse);
      server.send(200, "application/json", jsonResponse);
    } else {
      server.send(400, "application/json", "{\"error\":\"Missing 'state' key in JSON\"}");
    }
  });

  server.on("/temperature", HTTP_GET, []() {
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
      Serial.println("Failed to read temperature. Trying again...");
      delay(2000); // Wait for sensor to stabilize
      temperature = dht.readTemperature();
      if (isnan(temperature)) {
        server.send(500, "text/plain", "Failed to read temperature");
        return;
      }
    }
    DynamicJsonDocument response(128);
    response["temperature"] = temperature;
    String jsonResponse;
    serializeJson(response, jsonResponse);
    server.send(200, "application/json", jsonResponse);
  });

  server.on("/humidity", HTTP_GET, []() {
    float humidity = dht.readHumidity();
    if (isnan(humidity)) {
      server.send(500, "text/plain", "Failed to read humidity");
      return;
    }
    DynamicJsonDocument response(128);
    response["humidity"] = humidity;
    String jsonResponse;
    serializeJson(response, jsonResponse);
    server.send(200, "application/json", jsonResponse);
  });

  server.on("/rgb", HTTP_POST, []() {
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, server.arg("plain"));

    if (error) {
      server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }

    if (doc.containsKey("r") && doc.containsKey("g") && doc.containsKey("b")) {
      int red = doc["r"];
      int green = doc["g"];
      int blue = doc["b"];
      
      analogWrite(RED_PIN, red);
      analogWrite(GREEN_PIN, green);
      analogWrite(BLUE_PIN, blue);

      DynamicJsonDocument response(128);
      response["success"] = true;
      response["message"] = "RGB values set";
      String jsonResponse;
      serializeJson(response, jsonResponse);
      server.send(200, "application/json", jsonResponse);
    } else {
      server.send(400, "application/json", "{\"error\":\"Missing 'r', 'g', or 'b' key in JSON\"}");
    }
  });

  server.on("/heartbeat", HTTP_GET, []() {
    DynamicJsonDocument response(128);
    response["bpm"] = bpm;
    String jsonResponse;
    serializeJson(response, jsonResponse);
    server.send(200, "application/json", jsonResponse);
  });

  dht.begin();
  server.begin();
  Serial.println("Web Server started");
}

void loop(void) {
  server.handleClient();

  // sensor FLAME
  int fire = digitalRead(FLAME);
  if (fire == HIGH) {
    digitalWrite(ALARM, HIGH);  
  } else {
    digitalWrite(ALARM, LOW);   
  }

  // Heartbeat 
  int signal = analogRead(HEARTBEAT_PIN);
  unsigned long currentTime = millis();

  if (signal > threshold) { 
    if (currentTime - lastBeatTime > 600) { 
      lastBeatTime = currentTime;
      beatCount++;
    }
  }

  if (currentTime - lastBeatTime >= sampleWindow) {
    bpm = (beatCount * 60 * 1000) / (currentTime - lastBeatTime); 
    beatCount = 0;
    lastBeatTime = currentTime;
  }

  delay(200);
}
