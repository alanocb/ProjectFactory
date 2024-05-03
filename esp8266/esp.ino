#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <Servo.h>

#define WIFI_NAME   "Visitors"
#define WIFI_PASS   ""

#define DHTPIN D2     // temp humidade sensor
#define DHTTYPE DHT11  

#define MOTION_SENSOR_PIN D5 //movimento sensor
#define SERVO_PIN D6 // servo
#define LED_PIN D1 // LED
#define FLAME D7 // flame sensor
#define ALARM D8 // alarm fogo

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);
Servo servo;

void setup(void)
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);
  pinMode(FLAME, INPUT);
  pinMode(ALARM, OUTPUT);
  servo.attach(SERVO_PIN);

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
      delay(2000); // Aguardar sensor estabilizar
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

  dht.begin();
  server.begin();
  Serial.println("Web Server started");
}

void loop(void)
{
  server.handleClient();

  if (digitalRead(MOTION_SENSOR_PIN) == HIGH) {
    activateServo();
    Serial.println("on");
  } else {
    
    Serial.println("off");
    servo.write(0); 
    delay(10); //para ser mais suave
  }

  // sensor FLAME
  int fire = digitalRead(FLAME);
  if( fire == HIGH)
  {
    digitalWrite(ALARM,HIGH);  
  }
  else
  {
    digitalWrite(ALARM,LOW);   
  }

  delay(200);
}

void activateServo() {
  
  servo.write(90); // angulo
  delay(10); // suavidade
}
