#include <Arduino.h>

const int ENABLEB = 7;
const int PIN_C   = 9;
const int PIN_D   = 11;
const int PWM     = 3;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_C,   OUTPUT);
  pinMode(PIN_D,   OUTPUT);
  pinMode(PWM,     OUTPUT);
  pinMode(ENABLEB, OUTPUT);

  digitalWrite(ENABLEB, HIGH);
}

void loop() {
  Serial.println("Spinning clockwise");
  digitalWrite(PIN_C, HIGH);
  digitalWrite(PIN_D, LOW);
  analogWrite(PWM, 255);
  delay(3000);

  // For brake
  Serial.println("Braking");
  digitalWrite(PIN_C, HIGH);
  digitalWrite(PIN_D, HIGH);
  delay(1000);

  // For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
  Serial.println("Spinning counter-clockwise");
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, HIGH);
  delay(3000);

  // For brake
  Serial.println("Braking");
  digitalWrite(PIN_C, HIGH);
  digitalWrite(PIN_D, HIGH);
  delay(1000);
}
