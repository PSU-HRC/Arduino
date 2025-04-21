#include <Servo.h>

Servo lThumb; // Right hand servos
Servo lIndex;
Servo lMiddle;
Servo lRing;
Servo lPinky; 

Servo lThumb; // Left hand servos
Servo lIndex;
Servo lMiddle;
Servo lRing;
Servo lPinky; 

void setup() {
  Serial.begin(9600); // Start serial communication
  r_thumb.attach(2);    //min 130 max 40
  r_index.attach(3);    //min 25  max 130
  r_middle.attach(4);   //min 25  max 130
  r_ring.attach(5);     //min 25  max 130
  r_pinky.attach(6);    //min 25  max 130

  l_thumb.attach(8);    //min 45  max 120
  l_index.attach(9);    //min 180 max 50
  l_middle.attach(10);  //min 180 max 50
  l_ring.attach(11);    //min 180 max 50
  l_pinky.attach(12);   //min 180 max 50

  Serial.println("Enter 10 angles (right thumb to pinky and left thumb to pinky) separated by spaces, e.g., '45 90 120 60 30...'");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Read input until newline
    input.trim(); // Remove extra whitespace
    
    int angles[10];

    if (input == "wave") {
      for (int i = 0; i < 10; i++) { // Loop waveFingers 10 times
        waveFingers();
      }
      return;
    }

    else if (input == "min") {
      int minAngles[10] = {130, 25, 25, 25, 25, 45, 180, 180, 180, 180};
      memcpy(angles, minAngles, sizeof(angles));
    }

    else if (input == "max") {
      int maxAngles[10] = {40, 130, 130, 130, 130, 120, 50, 50, 50, 50};
      memcpy(angles, maxAngles, sizeof(angles));
    }

    else if (input == "flip") {
      int flipAngles[10] = {40, 25, 130, 25, 25, 120, 180, 50, 180, 180};
      memcpy(angles, flipAngles, sizeof(angles));
    }

    else if (input == "yolo") { //FIX
      int yoloAngles[10] = {40, 130, 25, 25, 130, 120, 50, 180, 180, 50};
      memcpy(angles, yoloAngles, sizeof(angles));
    }

    else {
      int count = 0;
      char *token = strtok((char*)input.c_str(), " ");
      
      while (token != NULL && count < 10) {
        angles[count++] = atoi(token);
        token = strtok(NULL, " ");
      }

      if (count != 10) {
        Serial.println("Invalid input. Enter exactly 5 angles separated by spaces.");
        return;
      }

      for (int i = 0; i < 10; i++) {
        if (angles[i] < 0 || angles[i] > 180) {
          Serial.println("Invalid angle detected. Each value must be between 0 and 180.");
          return;
        }
      }
    }

    r_thumb.write(angles[0]);
    r_index.write(angles[1]);
    r_middle.write(angles[2]);
    r_ring.write(angles[3]);
    r_pinky.write(angles[4]);
    l_thumb.write(angles[5]);
    l_index.write(angles[6]);
    l_middle.write(angles[7]);
    l_ring.write(angles[8]);
    l_pinky.write(angles[9]);


    Serial.println("Servos moved to new positions.");
  }
}

void waveFingers() {
  for (int pos = 120; pos >= 0; pos -= 5) {
    r_pinky.write(pos);
    if (pos <= 90) r_ring.write(pos);
    if (pos <= 60) r_middle.write(pos);
    if (pos <= 30) r_index.write(pos);
    delay(20);
  }
  for (int pos = 0; pos <= 120; pos += 5) {
    r_pinky.write(pos);
    if (pos >= 30) r_ring.write(pos);
    if (pos >= 60) r_middle.write(pos);
    if (pos >= 90) r_index.write(pos);
    delay(20);
  }
}