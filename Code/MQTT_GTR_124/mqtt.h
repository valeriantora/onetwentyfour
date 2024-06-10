extern const int led1;     //lampu rem
extern const int led2;     //lampu depan standar
extern const int led3;     //drl kanan sekaligus marker led
extern const int led4;     //drl kiri sekaligus marker led
extern const int led5;    //sen kanan sekaligus hazard
extern const int led6;    //sen kiri sekaligus hazard
extern const int led7;    //lampu mundur

extern int currentBrightness;
extern bool led1State;
extern bool led3State;
extern bool led4State;
extern bool led5State;
extern bool led6State;
extern bool hazardState;
extern bool led7State;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass, "Tora/LWT", 1, true, "offline")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.subscribe("Tora/124/NISSAN/R32/LWT" , true);
      client.publish("Tora/124/NISSAN/R32/LWT", "online", 1);
      client.publish("Tora/124/NISSAN/R32/ssid", SSID_WIFI, true);
      client.publish("Tora/124/NISSAN/R32/ip", WiFi.localIP().toString().c_str(), true);
      client.subscribe("Tora/124/NISSAN/R32/lavieen");
//      client.subscribe("Tora/124/NISSAN/R32/BRAKE");
//      client.subscribe("Tora/124/NISSAN/R32/DRL");
//      client.subscribe("Tora/124/NISSAN/R32/MARKER");
//      client.subscribe("Tora/124/NISSAN/R32/RIGHTTURN");
//      client.subscribe("Tora/124/NISSAN/R32/LEFTTURN");
//      client.subscribe("Tora/124/NISSAN/R32/HAZARD");
//      client.subscribe("Tora/124/NISSAN/R32/REVERSE");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg += (char)payload[i];
  }
  Serial.println();

  if (strcmp(topic, "Tora/124/NISSAN/R32/lavieen") == 0) {    //PRIMARY
    if (payload[0] == '0') {
      if (currentBrightness == 0 || currentBrightness == 255) {
        analogWrite(led1, 80);
        currentBrightness = 80;
        digitalWrite(led2, HIGH);
        led1State = true;
      } else {
        analogWrite(led1, 0);
        currentBrightness = 0;
        digitalWrite(led2, LOW);
        led1State = false;
      }
    }
  }

  if (strcmp(topic, "Tora/124/NISSAN/R32/lavieen") == 0) {    //BRAKE
    if (payload[0] == '1') {
      if (led1State) {
        if (currentBrightness == 80) {
          analogWrite(led1, 255);
          currentBrightness = 255;
        } else {
          analogWrite(led1, 80);
          currentBrightness = 80;
        }
      } else {
        if (currentBrightness == 0) {
          analogWrite(led1, 255);
          currentBrightness = 255;
        } else {
          analogWrite(led1, 0);
          currentBrightness = 0;
        }
      }
    }
  }

  if (strcmp(topic, "Tora/124/NISSAN/R32/lavieen") == 0) {    //DRL
    if (payload[0] == '2') {
      led3State = !led3State;
      led4State = !led4State;
    }
  }

  if (strcmp(topic, "Tora/124/NISSAN/R32/lavieen") == 0) {    //MARKER
    if (payload[0] == '3') {
      if (currentBrightness == 0) {
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        currentBrightness = HIGH;
      } else {
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        currentBrightness = LOW;
      }
    }
  }

  if (strcmp(topic, "Tora/124/NISSAN/R32/lavieen") == 0) {    //RIGHTTURN
    if (payload[0] == '4') {
      led5State = !led5State;
    }
  }

  if (strcmp(topic, "Tora/124/NISSAN/R32/lavieen") == 0) {    //LEFTTURN
    if (payload[0] == 'A') {
      led6State = !led6State;
    }
  }

  if (strcmp(topic, "Tora/124/NISSAN/R32/lavieen") == 0) {    //HAZARD
    if (payload[0] == 'B') {
      hazardState = !hazardState;
    }
  }

  if (strcmp(topic, "Tora/124/NISSAN/R32/lavieen") == 0) {    //REVERSE
    if (payload[0] == 'C') {
      led7State = !led7State;
    }
  }
}
