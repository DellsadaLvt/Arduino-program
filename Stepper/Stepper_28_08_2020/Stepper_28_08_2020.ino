#include <Stepper.h>
 
const int stepsPerRevolution = 2000;  // hehe
 
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
 
void setup() {
 
  myStepper.setSpeed(100);
  Serial.begin(9600);
}
 
void loop() {
 
  Serial.println("clockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
 
 
}
