#include <Servo.h>
Servo pinky;  // create Servo object to control a servo
Servo ring;
Servo middle;
Servo index;
Servo thumb;

Servo test;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  pinky.attach(9);  // attaches the servo on pin 9 to the servo object
  ring.attach(8);
  middle.attach(7);
  index.attach(6);
  thumb.attach(5);
  test.attach(13);
}

void loop() {
    pinky.write(30);         
    ring.write(30);  
    middle.write(30);  
    index.write(30);       // tell servo to go to position in variable 'pos'
    thumb.write(30);  
    wait(15);                 // waits 15ms for the servo to reach the position
    test.write(50);
}
