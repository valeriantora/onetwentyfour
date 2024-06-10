//versi 0.1 basic lampu depan sama fungsi dedicated lampu rem (kunci utama)
//versi 0.2 tambahin fitur ir biar bisa kontrol via remote tv rumah
//versi 0.3 tambahin fitur drl, tapi g tau kenapa harus dedicated void
//versi 0.4 tambahin fitur dim yang mana led nya sama kaya drl
//versi 0.5 tambahin fitur sen kiri kanan, sama hazard
//versi 0.6 tambahin fitur lampu mundur
//issue, jika command dim sama hazard atau left/right dinayalakan, terjadi kembang api
//versi 0.7 tambahin daynight led

#define DECODE_NEC
#include <Arduino.h>

#include <IRremote.hpp>
#define IR_RECEIVE_PIN 2

int primary = 0x59;
int braking = 0x19;
int drl = 0x18;
int marker = 0x55;
int dim = 0x58;
int rightturn = 0x1B;
int leftturn = 0x5A;
int hazard = 0x1A;
int reverse = 0x12;

const int led1 = 6;     //lampu rem
const int led2 = 4;     //lampu depan standar
const int led3 = 5;     //drl kanan sekaligus marker led
const int led4 = 9;     //drl kiri sekaligus marker led
const int led5 = 10;    //sen kanan sekaligus hazard
const int led6 = 11;    //sen kiri sekaligus hazard
const int led7 = 3;     //lampu mundur
const int led8 = 7;     //lampu dim

int currentBrightness = 0;
bool led1State = false;
bool led3State = false;
bool led4State = false;
bool led5State = false;
bool led6State = false;
bool hazardState = false;
bool led7State = false;
bool led8State = false;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  
  analogWrite(led1, currentBrightness);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
}

void irCommand() {      //buat proses ir
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
    
    if (IrReceiver.decodedIRData.command == primary) {

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
    else if (IrReceiver.decodedIRData.command == braking) {
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
    
    if (IrReceiver.decodedIRData.command == drl) {
      led3State = !led3State;
      led4State = !led4State;
    }

    if (IrReceiver.decodedIRData.command == marker) {
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

    if (IrReceiver.decodedIRData.command == rightturn) {
      led5State = !led5State;
    }

    if (IrReceiver.decodedIRData.command == leftturn) {
      led6State = !led6State;
    }

    if (IrReceiver.decodedIRData.command == hazard) {
      hazardState = !hazardState;
    }

    if (IrReceiver.decodedIRData.command == reverse) {
      led7State = !led7State;
    }

    if (IrReceiver.decodedIRData.command == dim) {
      
    }
 }
}

void drlLoop() {      //fungsi void biar command ir drl diatas bisa blinking
  if (led3State && led4State) {
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(50);
    digitalWrite(led3, LOW);
    delay(50);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    delay(50);
    digitalWrite(led3, LOW);
    delay(50);
  }
}

void dimLight() {
  if (led8State) {
    digitalWrite(led8, HIGH);
  } else {
    digitalWrite(led8, LOW);
  }
}
void rightLoop() {      //fungsi void untuk sen kanan
  if (!led3State && !led4State && led5State) {
    digitalWrite(led5, HIGH);
    delay(500);
    digitalWrite(led5, LOW);
    delay(500);
  }
}

void leftLoop() {     //fungsi void untuk sen kiri
  if (!led3State && !led4State && led6State) {
    digitalWrite(led6, HIGH);
    delay(500);
    digitalWrite(led6, LOW);
    delay(500);
  }
}

void hazardLoop() {     //fungsi void untuk hazard
  if (!led3State && !led4State && hazardState) {
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    delay(500);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    delay(500);
  }
}

void reVerse() {      //fungsi void untuk lampu mundur
  if (led7State) {
    digitalWrite(led7, HIGH);
  } else {
    digitalWrite(led7, LOW);
  }
}

void loop() {     //looping fungsi void diatas 
  irCommand();
  drlLoop();
  rightLoop();
  leftLoop();
  hazardLoop();
  reVerse();
  dimLight();
}
