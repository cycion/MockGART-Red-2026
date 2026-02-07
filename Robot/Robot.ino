#include <PS2X_lib.h>

PS2X ps2x;

int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motor2Pin1 = 4;
int motor2Pin2 = 5;
int motor3Pin1 = 6;
int motor3Pin2 = 7;
int motor4Pin1 = 8;
int motor4Pin2 = 9;

int enableA = 10;
int enableB = 11;
int enableC = 12;
int enableD = 13;

void setup() {
  pinMode(motor1Pin1, INPUT);
  pinMode(motor1Pin2, INPUT);
  pinMode(motor2Pin1, INPUT);
  pinMode(motor2Pin2, INPUT);
  pinMode(motor3Pin1, INPUT);
  pinMode(motor3Pin2, INPUT);
  pinMode(motor4Pin1, INPUT);
  pinMode(motor4Pin2, INPUT);
  
  pinMode(enableA, INPUT);
  pinMode(enableB, INPUT);
  pinMode(enableC, INPUT);
  pinMode(enableD, INPUT);
  
  ps2x.config_gamepad(15, 16, 17, 18, true, true);
  
  Serial.begin(9600);
}

void loop() {
  ps2x.read_gamepad();
  
  int LY = ps2x.Analog(PSS_LY);
  int LX = ps2x.Analog(PSS_LX);
  int RX = ps2x.Analog(PSS_RX);
  
  int frontLeft = LY + LX + RX;
  int frontRight = LY - LX - RX;
  int backLeft = LY - LX + RX;
  int backRight = LY + LX - RX;
  
  frontLeft = constrain(frontLeft, -255, 255);
  frontRight = constrain(frontRight, -255, 255);
  backLeft = constrain(backLeft, -255, 255);
  backRight = constrain(backRight, -255, 255);
  
  setMotor(1, frontLeft);
  setMotor(2, frontRight);
  setMotor(3, backLeft);
  setMotor(4, backRight);
  
  delay(50);
}

void setMotor(int motor, int speed) {
  int pin1, pin2, enable;
  
  if (motor = 1) {
    pin1 = motor1Pin1;
    pin2 = motor1Pin2;
    enable = enableA;
  } else if (motor = 2) {
    pin1 = motor2Pin1;
    pin2 = motor2Pin2;
    enable = enableB;
  } else if (motor = 3) {
    pin1 = motor3Pin1;
    pin2 = motor3Pin2;
    enable = enableC;
  } else {
    pin1 = motor4Pin1;
    pin2 = motor4Pin2;
    enable = enableD;
  }
  
  if (speed > 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(enable, speed);
  } else if (speed < 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(enable, -speed);
  } else {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    analogWrite(enable, 0);
  }
}
