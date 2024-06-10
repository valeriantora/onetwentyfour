#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <PubSubClient.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t kRecvPin = 14;

WiFiClient espClient;
PubSubClient client(espClient);

#include "config.h"
#include "ir.h"
#include "mqtt.h"

AsyncWebServer server(80);

const int led1 = 32;     //lampu rem
const int led2 = 33;     //lampu depan standar
const int led3 = 25;     //drl kanan sekaligus marker led
const int led4 = 26;     //drl kiri sekaligus marker led
const int led5 = 27;    //sen kanan sekaligus hazard
const int led6 = 14;    //sen kiri sekaligus hazard
const int led7 = 12;    //lampu mundur

int currentBrightness = 0;
bool led1State = false;
bool led3State = false;
bool led4State = false;
bool led5State = false;
bool led6State = false;
bool hazardState = false;
bool led7State = false;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(2, OUTPUT);
  
  analogWrite(led1, currentBrightness);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println("ssid");
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_WIFI, SSID_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(2, LOW);
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! This is a sample response.");
  });

  AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
  server.begin();
  Serial.println("HTTP server started");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  while (!Serial)  // Wait for the serial connection to be establised.
  delay(50);
  Serial.println();

  irrecv.enableIRIn();  // Start the receiver
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  } else {
    digitalWrite(2, HIGH);
  }
  client.loop();
  irCommand();
  drlLoop();
  rightLoop();
  leftLoop();
  hazardLoop();
  reVerse();
}
