IRrecv irrecv(kRecvPin);
decode_results results;

int primary = 0xFD9A65;
int braking = 0xFD9867;
int drl = 0xFD1AE5;
int marker = 0xFD18E7;
int dim = 0xFD58A7;
int rightturn = 0xFDD827;
int leftturn = 0xFD5AA5;
int hazard = 0xFD708F;
int reverse = 0xFD48B7;

void irCommand() {
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    irrecv.resume();  // Receive the next value

    if (results.value == primary){   //PRIMARY
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

    if (results.value == braking){   //BRAKE
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

    if (results.value == drl){   //DRL
      led3State = !led3State;
      led4State = !led4State;
    }

    if (results.value == marker){   //MARKER
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

    if (results.value == rightturn){   //RIGHTTURN
      led5State = !led5State;
    }

    if (results.value == leftturn){   //LEFTTURN
      led6State = !led6State;
    }

    if (results.value == hazard){   //HAZARD
      hazardState = !hazardState;
    }

    if (results.value == reverse){   //REVERSE
      led7State = !led7State;
    }
  }
}
