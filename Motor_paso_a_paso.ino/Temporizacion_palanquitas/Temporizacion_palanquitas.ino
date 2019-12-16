// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

// Connect a stepper motor with 48 steps per revolution (7.5 degree)
// to motor port #2 (M3 and M4)
AF_Stepper motor(48, 2);

void setup() {
  Serial.begin(115200);      // set up Serial library at 9600 bps
  //Serial.println("Stepper test!");

  motor.setSpeed(28 0);  // 10 rpm   
}

void loop() {
  uint32_t tiempo1 = millis();
  motor.step(9, FORWARD, DOUBLE); 
  Serial.println(millis() - tiempo1);
  tiempo1 = millis();
  motor.step(9, BACKWARD, DOUBLE); 
  Serial.println(millis() - tiempo1);
}
