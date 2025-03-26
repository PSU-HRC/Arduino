#include <Servo.h>

Servo pinky;
Servo ring;
Servo middle;
Servo index;
Servo thumb;

void setup() {
  Serial.begin(9600); // Start serial communication
  pinky.attach(6);
  ring.attach(5);
  middle.attach(4);
  index.attach(3);
  thumb.attach(2);

  Serial.println("Enter 5 angles (thumb to pinky) separated by spaces, e.g., '45 90 120 60 30'");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Read input until newline
    input.trim(); // Remove extra whitespace
    
    int angles[5];

    if (input == "wave") {
      for (int i = 0; i < 10; i++) { // Loop waveFingers 10 times
        waveFingers();
      }
      return;
    }

    else if (input == "flip") {
      int flipAngles[5] = {0, 0, 140, 0, 0};
      memcpy(angles, flipAngles, sizeof(angles));
    }

    else if (input == "yolo") {
      int yoloAngles[5] = {0, 140, 0, 0, 140};
      memcpy(angles, yoloAngles, sizeof(angles));
    }

    else {
      int count = 0;
      char *token = strtok((char*)input.c_str(), " ");
      
      while (token != NULL && count < 5) {
        angles[count++] = atoi(token);
        token = strtok(NULL, " ");
      }

      if (count != 5) {
        Serial.println("Invalid input. Enter exactly 5 angles separated by spaces.");
        return;
      }

      for (int i = 0; i < 5; i++) {
        if (angles[i] < 0 || angles[i] > 180) {
          Serial.println("Invalid angle detected. Each value must be between 0 and 180.");
          return;
        }
      }
    }

    thumb.write(angles[0]);
    index.write(angles[1]);
    middle.write(angles[2]);
    ring.write(angles[3]);
    pinky.write(angles[4]);

    Serial.println("Servos moved to new positions.");
  }
}

void waveFingers() {
  for (int pos = 120; pos >= 0; pos -= 5) {
    pinky.write(pos);
    if (pos <= 90) ring.write(pos);
    if (pos <= 60) middle.write(pos);
    if (pos <= 30) index.write(pos);
    delay(20);
  }
  for (int pos = 0; pos <= 120; pos += 5) {
    pinky.write(pos);
    if (pos >= 30) ring.write(pos);
    if (pos >= 60) middle.write(pos);
    if (pos >= 90) index.write(pos);
    delay(20);
  }
}