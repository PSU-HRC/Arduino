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

  rPinky.attach(48);
  lThumb.attach(22);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {    data = Serial.readStringUntil('\n');
    int angle = data.toInt();
    rPinky.write(angle);

    /*if(angle <= 180 && angle >= 0) {
      lThumb.write(180);
    }*/
    Serial.print("Received: ");
    Serial.println(data);
    
    //processHandData(data);
  }
  else {
    Serial.println("fail");
  }
   delay(100);
  //rPinky.write(180);

}
/*
void processHandData(String inputString) {
  //Serial.print(inputString);
  rPinky.write(inputString.toInt());
}
*/