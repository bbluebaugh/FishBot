/*
 * @authors: Atticus Speis, Brian Bluebaugh, John Tripp, Becca Flinn
 * @version: 1.0, 3/1/19
 * This is a proof of concept of a robot which can read input based on a fish's location in a fish tank to move in that direction
 * Using the items provided, (TCS34725 light sensor, Adafruit Motor Shield, Tetrix Motors) we created the following program to
 * loop through to determine the current light values and based on those move in a direction
 */
//these includes are for the light sensor and the motor shield
#include <Wire.h>
#include "Adafruit_TCS34725softi2c.h"
//next includes are for motor
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to digital 8
   Connect SDA    to digital 9
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */
   
// You can use any digital pin for emulate SDA / SCL
#define SDApin 6
#define SCLpin 7

#define SDApin2 8
#define SCLpin2 9

#define SDApin3 10
#define SCLpin3 11

#define SDApin4 12
#define SCLpin4 13

/* Initialise with specific int time and gain values */
//Modified the library for the TCS34725 to add a new value less than the initial 700MS but greater than 154MS
//This was done to keep relatively high accuracy of the color sensor as well as a faster refresh time than the 700MS
//If you are to run this you will also need to modify the library or else change the MS below to 700 or 154
Adafruit_TCS34725softi2c tcs = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_300MS, TCS34725_GAIN_1X, SDApin, SCLpin);
Adafruit_TCS34725softi2c tcs2 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_300MS, TCS34725_GAIN_1X, SDApin2, SCLpin2);
Adafruit_TCS34725softi2c tcs3 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_300MS, TCS34725_GAIN_1X, SDApin3, SCLpin3);
Adafruit_TCS34725softi2c tcs4 = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_300MS, TCS34725_GAIN_1X, SDApin4, SCLpin4);
//These are making objects of the motor shield and then the first motor respectively
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);//first motor
//motor 2
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
//motor3
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
//motor4
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);
void setup(void) {
  //these are the beginning of the motor initializing
  AFMS.begin();//connect to motor shield
  motor1->setSpeed(50);
  motor2->setSpeed(50);
  motor3->setSpeed(50);
  motor4->setSpeed(50);
  
  Serial.begin(9600);

  
  if (tcs.begin() && tcs2.begin() && tcs3.begin() && tcs4.begin()) {
    Serial.println("Found sensors");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  // Now we're ready to get readings!
}

uint16_t r, g, b, c, colorTemp, lux;
uint16_t r2, g2, b2, c2, colorTemp2, lux2;
uint16_t r3, g3, b3, c3, colorTemp3, lux3;
uint16_t r4, g4, b4, c4, colorTemp4, lux4;
void loop(void) {
  //initialize the color sensors
  //Caclulate the Luminosity as the Lux variable so we only have to compare light value for where the fish/object is in the tank
  tcs.getRawData(&r, &g, &b, &c);
  tcs2.getRawData(&r2, &g2, &b2, &c2);
  tcs3.getRawData(&r3, &g3, &b3, &c3);
  tcs4.getRawData(&r4, &g4, &b4, &c4);
  lux = tcs.calculateLux(r, g, b);
  lux2 = tcs2.calculateLux(r2, g2, b2);
  lux3 = tcs3.calculateLux(r3, g3, b3);
  lux4 = tcs4.calculateLux(r4, g4, b4);
  
  /*
  tcs.getRawData(&r, &g, &b, &c);
  tcs2.getRawData(&r2, &g2, &b2, &c2);
  tcs3.getRawData(&r3, &g3, &b3, &c3);
  tcs4.getRawData(&r4, &g4, &b4, &c4);
  
  //colorTemp = tcs.calculateColorTemperature(r, g, b);
  //colorTemp2 = tcs2.calculateColorTemperature(r2, g2, b2);
  lux = tcs.calculateLux(r, g, b);
  lux2 = tcs2.calculateLux(r2, g2, b2);
  lux3 = tcs3.calculateLux(r3, g3, b3);
  lux4 = tcs4.calculateLux(r4, g4, b4);
  */
  //if the threshold for the luminosity drops then run the motors in a specific direction relative to the light sensor direction
  
  if(lux < 800){
    motor1->run(FORWARD);
    motor2->run(BACKWARD);
    motor3->run(BACKWARD);
    motor4->run(FORWARD);
    delay(250);
  }else if(lux2 < 800){
    motor1->run(FORWARD);
    motor2->run(FORWARD);
    motor3->run(BACKWARD);
    motor4->run(BACKWARD);
    delay(250);
  }
  else if(lux3 < 800){
    motor1->run(BACKWARD);
    motor2->run(FORWARD);
    motor3->run(FORWARD);
    motor4->run(BACKWARD);
    delay(250);
  }else if(lux4 < 800){
    motor1->run(BACKWARD);
    motor2->run(BACKWARD);
    motor3->run(FORWARD);
    motor4->run(FORWARD);
    delay(250);    
  }
  else{
    motor1->run(RELEASE);
    motor2->run(RELEASE);
    motor3->run(RELEASE);
    motor4->run(RELEASE);  
  }
  Serial.println("End");
  
}
  /*
   * Taken from loop just before the if statements. This was used to test the color sensors to make sure they were reading how we
   * wanted them to read
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  Serial.print("Color Temp: "); Serial.print(colorTemp2, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux2, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r2, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g2, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b2, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c2, DEC); Serial.print(" ");
  Serial.println(" ");
  Serial.print("Color Temp: "); Serial.print(colorTemp3, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux3, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r3, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g3, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b3, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c3, DEC); Serial.print(" ");
  Serial.println(" ");
  Serial.print("Color Temp: "); Serial.print(colorTemp4, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux4, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r4, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g4, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b4, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c4, DEC); Serial.print(" ");
  Serial.println(" ");
  Serial.println(" ");
  */
