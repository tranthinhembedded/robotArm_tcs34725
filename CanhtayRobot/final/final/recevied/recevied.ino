#include <Servo.h>

// Khai báo các servo
Servo updown;
Servo vuon;
Servo kep;
Servo xoay;

void setup() {
  // Khởi tạo cổng Serial để nhận dữ liệu và in ra Serial Monitor
  Serial.begin(9600);

  // Thông báo khởi động
  Serial.println("Receiver started, waiting for color data...");

  // Gắn các servo vào các chân
  kep.attach(3);
  vuon.attach(5);
  xoay.attach(6);
  updown.attach(9);
  
  // Đặt vị trí ban đầu cho các servo
  updown.write(0);
  vuon.write(0);
  kep.write(0);
  xoay.write(0);
}

void loop() {
  // Kiểm tra nếu có dữ liệu từ UART cứng
  if (Serial.available()) {
    char received_color = Serial.read();  // Đọc ký tự từ UART cứng

    // In dữ liệu nhận được ra Serial Monitor
    switch (received_color) {
      case 'R':
        Serial.println("Received: Red");
        RED();
        break;
      case 'G':
        Serial.println("Received: Green");
        GREEN();
        break;
      case 'B':
        Serial.println("Received: Blue");
        BLUE();
        break;
      case 'N':
        Serial.println("Received: None");
        break;
      default:
        Serial.print("Received unknown data: ");
        Serial.println(received_color);
        break;
    }
  }
}

void RED(void) {
  for (int i = 0; i <= 180; i++) {
    xoay.write(i);
    delay(10);
  }

  vuon.write(40);
  delay(1000);
  for (int i = 0; i < 161; i++) {
    updown.write(i);
    delay(5);
  }
  delay(500);
  kep.write(171);
  delay(500);

  for (int i = 160; i >= 0; i--) {
    updown.write(i);
    delay(5);
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
  for (int i = 0; i < 161; i++) {
    updown.write(i);
    delay(5);
  }
  delay(500);

  kep.write(0);
  delay(500);

  for (int i = 160; i >= 0; i--) {
    updown.write(i);
    delay(5);
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
  for (int i = 0; i < 161; i++) {
    updown.write(i);
    delay(5);
  }
  delay(500);
  kep.write(171);
  delay(500);

  for (int i = 160; i >= 0; i--) {
    updown.write(i);
    delay(5);
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
  for (int i = 0; i < 161; i++) {
    updown.write(i);
    delay(5);
  }
  delay(500);

  kep.write(0);
  delay(500);

  for (int i = 160; i >= 0; i--) {
    updown.write(i);
    delay(5);
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
  for (int i = 0; i < 161; i++) {
    updown.write(i);
    delay(5);
  }
  delay(500);
  kep.write(171);
  delay(500);

  for (int i = 160; i >= 0; i--) {
    updown.write(i);
    delay(5);
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
  for (int i = 0; i < 161; i++) {
    updown.write(i);
    delay(5);
  }
  delay(500);

  kep.write(0);
  delay(500);

  for (int i = 160; i >= 0; i--) {
    updown.write(i);
    delay(5);
  }

  for (int i = 40; i >= 0; i--) {
    vuon.write(i);
    delay(10);
  }
  delay(1000);
}