const int led1 = 32;     //lampu rem (PWM)
const int led2 = 33;     //lampu depan standar

//int currentBrightness = 0;
bool led1State = false;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  analogWrite(led1, LOW);
//  analogWrite(led1, currentBrightness);
  digitalWrite(led2, LOW);
}

void loop() {
  analogWrite(led1, 80);
//  currentBrightness = 80;
  digitalWrite(led2, HIGH);
  led1State = true;

  delay(1000);

  analogWrite(led1, 0);
//  currentBrightness = 0;
  digitalWrite(led2, LOW);
  led1State = false;

  delay(1000);

  analogWrite(led1, 80);
//  currentBrightness = 80;
  digitalWrite(led2, HIGH);
  led1State = true;

  delay(1000);

  analogWrite(led1, 255);
//  currentBrightness = 255;
  digitalWrite(led2, HIGH);
  led1State = true;

  delay(1000);

  analogWrite(led1, 80);
//  currentBrightness = 80;
  digitalWrite(led2, HIGH);
  led1State = true;

  delay(1000);

  analogWrite(led1, 0);
//  currentBrightness = 0;
  digitalWrite(led2, LOW);
  led1State = false;

  delay(1000);

  analogWrite(led1, 255);
//  currentBrightness = 255;

  delay(1000);

  analogWrite(led1, 0);
//  currentBrightness = 0;
}
