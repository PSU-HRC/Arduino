#include <Servo.h>

Servo rThumb; // Right hand servos
Servo rIndex;
Servo rMiddle;
Servo rRing;
Servo rPinky; 

Servo lThumb; // Left hand servos
Servo lIndex;
Servo lMiddle;
Servo lRing;
Servo lPinky; 

Servo rElbow;
Servo lElbow;

String data = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino ready");

  // Right hand servos
  rThumb.attach(2);    //min 130 max 40
  rIndex.attach(3);    //min 25  max 130
  rMiddle.attach(4);   //min 25  max 130
  rRing.attach(5);     //min 25  max 130
  rPinky.attach(6);    //min 25  max 130
  rElbow.attach(7);

  // Left hand servos
  lThumb.attach(8);    //min 45  max 120
  lIndex.attach(9);    //min 180 max 50
  lMiddle.attach(10);  //min 180 max 50
  lRing.attach(11);    //min 180 max 50
  lPinky.attach(12);   //min 180 max 50
  lElbow.attach(13);
}

void loop() {
  if (Serial.available() > 0) {    
    data = Serial.readStringUntil('\n'); 
    
    // Check if data starts with "Left" or "Right"
    if (data.startsWith("Left:")) {
      processHandData(data.substring(5), true); // Process left hand
    } 
    else if (data.startsWith("Right:")) {
      processHandData(data.substring(6), false); // Process right hand
    }
  }
}

void processHandData(String angleData, bool isLeftHand) {
  int angles[6];
  int index = 0;
  
  int startIndex = 0;
  int endIndex = angleData.indexOf(' ');

  // Serial.print(angleData);

  while (endIndex != -1 && index < 6) {
    angles[index++] = angleData.substring(startIndex, endIndex).toInt();
    startIndex = endIndex + 1;
    endIndex = angleData.indexOf(' ', startIndex);
  }
  if (index < 6) {
    angles[index] = angleData.substring(startIndex).toInt();
  }

  // Map the angles to servo ranges -- NEED TO BE EDITED FOR THON BOT HANDS
  //This is for INMOVE hands
  // angles[0] = map(constrain(angles[0], 30, 230), 30, 230, 0, 130);
  // angles[1] = map(constrain(angles[1], 20, 130), 20, 130, 0, 130);
  // angles[2] = map(constrain(angles[2], 10, 130), 10, 130, 0, 150);
  // angles[3] = map(constrain(angles[3], 10, 150), 10, 150, 0, 135);
  // angles[4] = map(constrain(angles[4], 20, 120), 20, 120, 0, 120);

  //This is for THONBOT hands
  if (isLeftHand) {
      //Left: Thumb --> Pinky
    angles[0] = map(constrain(angles[0], 30, 230), 30, 230, 120, 45);
    angles[1] = map(constrain(angles[1], 20, 130), 20, 130, 50, 180);
    angles[2] = map(constrain(angles[2], 10, 130), 10, 130, 50, 180);
    angles[3] = map(constrain(angles[3], 10, 150), 10, 150, 50, 180);
    angles[4] = map(constrain(angles[4], 20, 120), 20, 120, 50, 180);
    angles[5] = map(constrain(angles[5], 20, 75), 20, 75, 0, 180); //Editing needed
  } else {
      //Right: Thumb --> Pinky
    angles[0] = map(constrain(angles[0], 30, 230), 30, 230, 40, 130);
    angles[1] = map(constrain(angles[1], 20, 130), 20, 130, 130, 25);
    angles[2] = map(constrain(angles[2], 10, 130), 10, 130, 130, 25);
    angles[3] = map(constrain(angles[3], 10, 150), 10, 150, 130, 25);
    angles[4] = map(constrain(angles[4], 20, 120), 20, 120, 130, 25);
    // angles[5] = map(constrain(angles[5], 20, 120), 20, 120, 130, 25);
    angles[5] = map(constrain(angles[5], 20, 75), 20, 75, 0, 180); //Editing needed
  }


  // Control the appropriate servos based on which hand it is
  if (isLeftHand) {
    lThumb.write(angles[0]);
    lIndex.write(angles[1]);
    lMiddle.write(angles[2]);
    lRing.write(angles[3]);
    lPinky.write(angles[4]);
    lElbow.write(angles[5]);
  } else {
    rThumb.write(angles[0]);
    rIndex.write(angles[1]);
    rMiddle.write(angles[2]);
    rRing.write(angles[3]);
    rPinky.write(angles[4]);
    rElbow.write(angles[5]);
  }

  Serial.print(isLeftHand ? "Left" : "Right");
  Serial.print(" hand angles: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(String(angles[i]) + " ");
  }
  Serial.println();
}