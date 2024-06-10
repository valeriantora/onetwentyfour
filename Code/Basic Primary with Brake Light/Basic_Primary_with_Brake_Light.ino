const int led1 = 4;
const int led2 = 3;
int currentBrightness = 0;
bool led1State = false;

void setup() {
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  analogWrite(led1, currentBrightness);
  digitalWrite(led2, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case '1':
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
        break;
        
      case '2':
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
        break;
    }
  }
}
