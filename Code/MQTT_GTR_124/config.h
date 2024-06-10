const char* SSID_WIFI = "lavieenrose_2.4G";
const char* SSID_PASS = "admin.admin";
const char* AP_SSID = "oaoaoa";
const char* AP_PASS = "12345678";
const char* mqtt_server = "192.168.0.200";
const char* mqtt_user = "";
const char* mqtt_pass = "";
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

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

void drlLoop() {      //drl blinking
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
