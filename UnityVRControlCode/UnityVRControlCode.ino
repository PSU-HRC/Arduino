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
  // Initialize serial communication and attach servos
  Serial.begin(9600);
  Serial.println("Arduino ready");

  rThumb.attach(3);
  rIndex.attach(4);
  rMiddle.attach(5);
  rRing.attach(6);
  rPinky.attach(7);
}

void loop() {
  // Check if there is serial data available
  if (Serial.available() > 0) {    
    data = Serial.readStringUntil('\n'); 
    int angles[5];                       
    int index = 0;                       

    int startIndex = 0;
    int endIndex = data.indexOf(' ');
    
    while (endIndex != -1 && index < 5) {
      angles[index++] = data.substring(startIndex, endIndex).toInt();
      startIndex = endIndex + 1;
      endIndex = data.indexOf(' ', startIndex);
    }
    if (index < 5) {
      angles[index] = data.substring(startIndex).toInt();
    }

    rThumb.write(angles[0]);
    rIndex.write(angles[1]);
    rMiddle.write(angles[2]);
    rRing.write(angles[3]);
    rPinky.write(angles[4]);

    Serial.print("Received angles: ");
    Serial.println(data); 

  } else {
    Serial.println("fail"); 
  }
  
  delay(100);
}
