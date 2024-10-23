#include <Servo.h>
Servo rPinky;  // create Servo object to control a servo
Servo rRing;
Servo rMiddle;
Servo rIndex;
Servo rThumb;

Servo lPinky; 
Servo lRing;
Servo lMiddle;
Servo lIndex;
Servo lThumb;

String data = "";
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Arduino ready");

  rPinky.attach(22);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    data = Serial.readStringUntil('\n');
    processHandData(data);
  }
}

void processHandData(String inputString) {
  Serial.println("Received data: " + inputString);
  rPinky.write(inputString.toInt());
}