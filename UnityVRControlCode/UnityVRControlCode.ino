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
    /*
      Unity
      THumb: 30-230
      index: 20-130
      middle: 10-130
      ring: 10-150
      pinky: 20-120

      fist: all values around 200
 
    */

    
    angles[0] = map(constrain(angles[0], 30, 230), 30, 230, 0, 130);
    angles[1] = map(constrain(angles[1], 20, 130), 20, 130, 0, 130);
    angles[2] = map(constrain(angles[2], 10, 130), 10, 130, 0, 150);
    angles[3] = map(constrain(angles[3], 10, 150), 10, 150, 0, 135);
    angles[4] = map(constrain(angles[4], 20, 120), 20, 120, 0, 120);

    rThumb.write(angles[0]);
    rIndex.write(angles[1]);
    rMiddle.write(angles[2]);
    rRing.write(angles[3]);
    rPinky.write(angles[4]);

    Serial.print("Received angles: ");
    for (int i = 0; i < 5; i++) {
      Serial.print(String(angles[i]) + " ");
      if (i == 4) {
        Serial.println();
      }
    }
    //Serial.println(data); 

  } else {
    //Serial.println("fail"); 
  }
  
  //delay(100);
}
