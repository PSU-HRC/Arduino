#include <Servo.h>
Servo pinky;  // create Servo object to control a servo
Servo ring;
Servo middle;
Servo index;
Servo thumb;

Servo test;
// twelve servo objects can be created on most boards

int pos = 45;    // variable to store the servo position

void setup() {
 pinky.attach(12);  // attaches the servo on pin 9 to the servo object
  ring.attach(11);
  middle.attach(10);
  index.attach(9);
  thumb.attach(8);
  // test.attach(7);
}

void loop() {
    pinky.write(pos);         
    ring.write(pos);  
    middle.write(pos);  
    index.write(pos);       // tell servo to go to position in variable 'pos'
    thumb.write(pos);  
    //delay(15);                 // waits 15ms for the servo to reach the position
    test.write(0);
}
