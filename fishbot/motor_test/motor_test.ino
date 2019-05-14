#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *myMotor = AFMS.getMotor(1);//first motor
void setup() {
  // put your setup code here, to run once:
  AFMS.begin();//connect to motor shield
  myMotor->setSpeed(150);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  myMotor->run(FORWARD);
  delay(2000);
  myMotor->run(BACKWARD);
  delay(2000);
  myMotor->run(RELEASE);
  
}
