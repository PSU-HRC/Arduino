#include <Servo.h>
Servo pinky;  // create Servo object to control a servo
Servo ring;
Servo middle;
Servo index;
Servo thumb;

Servo test;
// twelve servo objects can be created on most boards

int pos = 100;    // variable to store the servo position

void setup() {
  //pinky.attach(9);  // attaches the servo on pin 9 to the servo object
  //ring.attach(8);
  //middle.attach(7);
  //index.attach(6);
  //thumb.attach(5);
  test.attach(9);
}

void loop() {
    pinky.write(pos);         
    ring.write(pos);  
    middle.write(pos);  
    index.write(pos);       // tell servo to go to position in variable 'pos'
    thumb.write(pos);  
    delay(15);                 // waits 15ms for the servo to reach the position
    test.write(0);
}
