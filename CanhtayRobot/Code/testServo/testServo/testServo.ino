#include <Servo.h>

Servo myServo;
Servo myServo1;

void setup() {
  myServo.attach(3);
  myServo1.attach(5);
  Serial.begin(9600); // Initialize UART with 9600 baud rate
  myServo.write(0);
  myServo1.write(0);
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    char receivedChar = Serial.read(); // Read the incoming character
    
    if (receivedChar == 'G') {
      myServo.write(30); // Rotate servo on pin 3 to 30 degrees
    }
    else if (receivedChar == 'M') {
      myServo1.write(0); // Rotate servo on pin 5 to 0 degrees
    }
    else if (receivedChar == 'N') {
      myServo1.write(90); // Rotate servo on pin 5 to 90 degrees
    }
    else if (receivedChar == 'C') {
      myServo.write(0); // Rotate servo on pin 3 to 0 degrees
    }
  }
}