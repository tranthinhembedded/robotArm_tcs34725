#include <Servo.h>

Servo updown;
Servo vuon;
Servo kep;
Servo xoay;

void setup() {
  kep.attach(3);
  vuon.attach(5);
  xoay.attach(6);
  updown.attach(9);

  updown.write(0);
  vuon.write(0);
  kep.write(0);
  xoay.write(0);
}

void loop() {
  // RED();
//   delay(2000);
//   GREEN();
//   delay(2000);
//   BLUE();
//   delay(2000);
 }

void RED(void) {
  for (int i = 0; i <= 180; i++) {
    xoay.write(i);
    delay(10);
  }

  vuon.write(40);
  delay(1000);
  for (int i = 0; i < 61; i++) {
    updown.write(i);
    delay(10);
  }
  delay(500);
  kep.write(171);
  delay(500);

  for (int i = 60; i >= 0; i--) {
    updown.write(i);
    delay(10);
  }

  for (int i = 40; i >= 0; i--) {
    vuon.write(i);
    delay(10);
  }
  delay(1000);

  for (int i = 180; i >= 0; i--) {
    xoay.write(i);
    delay(10);
  }


  vuon.write(40);
  delay(500);
  for (int i = 0; i < 61; i++) {
    updown.write(i);
    delay(10);
  }
  delay(500);

  kep.write(0);
  delay(500);

  for (int i = 60; i >= 0; i--) {
    updown.write(i);
    delay(10);
  }

  for (int i = 40; i >= 0; i--) {
    vuon.write(i);
    delay(10);
  }
  delay(1000);
}

void GREEN(void) {
  for (int i = 0; i <= 180; i++) {
    xoay.write(i);
    delay(10);
  }

  vuon.write(40);
  delay(1000);
  for (int i = 0; i < 61; i++) {
    updown.write(i);
    delay(10);
  }
  delay(500);
  kep.write(171);
  delay(500);

  for (int i = 60; i >= 0; i--) {
    updown.write(i);
    delay(10);
  }

  for (int i = 40; i >= 0; i--) {
    vuon.write(i);
    delay(10);
  }
  delay(1000);

  for (int i = 180; i >= 20; i--) {
    xoay.write(i);
    delay(10);
  }


  vuon.write(40);
  delay(500);
  for (int i = 0; i < 61; i++) {
    updown.write(i);
    delay(10);
  }
  delay(500);

  kep.write(0);
  delay(500);

  for (int i = 60; i >= 0; i--) {
    updown.write(i);
    delay(10);
  }

  for (int i = 40; i >= 0; i--) {
    vuon.write(i);
    delay(10);
  }
  delay(1000);
}
void BLUE(void) {
  for (int i = 0; i <= 180; i++) {
    xoay.write(i);
    delay(10);
  }

  vuon.write(40);
  delay(1000);
  for (int i = 0; i < 61; i++) {
    updown.write(i);
    delay(10);
  }
  delay(500);
  kep.write(171);
  delay(500);

  for (int i = 60; i >= 0; i--) {
    updown.write(i);
    delay(10);
  }

  for (int i = 40; i >= 0; i--) {
    vuon.write(i);
    delay(10);
  }
  delay(1000);

  for (int i = 180; i >= 50; i--) {
    xoay.write(i);
    delay(10);
  }


  vuon.write(40);
  delay(500);
  for (int i = 0; i < 61; i++) {
    updown.write(i);
    delay(10);
  }
  delay(500);

  kep.write(0);
  delay(500);

  for (int i = 60; i >= 0; i--) {
    updown.write(i);
    delay(10);
  }

  for (int i = 40; i >= 0; i--) {
    vuon.write(i);
    delay(10);
  }
  delay(1000);
}
