#define DECODE_NEC
#include <Arduino.h>

#include <IRremote.hpp>
#define IR_RECEIVE_PIN 2

const int led1 = 6;
const int led2 = 4;
int currentBrightness = 0;
bool led1State = false;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  analogWrite(led1, currentBrightness);
  digitalWrite(led2, LOW);
}

void loop() {
  if (IrReceiver.decode()) {

    IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();
        
    IrReceiver.resume();
    
    if (IrReceiver.decodedIRData.command == 0x59) {

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
    else if (IrReceiver.decodedIRData.command == 0x19) {
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
}
