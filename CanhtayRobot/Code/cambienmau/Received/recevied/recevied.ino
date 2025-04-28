#include <SoftwareSerial.h>
#include <Servo.h>
// Khai báo cổng UART mềm (RX, TX)
SoftwareSerial softSerial(10, 11);  // RX: 10, TX: 11 (TX không dùng, chỉ cần khai báo)
Servo updown;
Servo vuon;
Servo kep;
Servo xoay;
void setup() {
  // Khởi tạo cổng Serial để in ra Serial Monitor
  Serial.begin(9600);

  // Khởi tạo cổng UART mềm để nhận dữ liệu
  softSerial.begin(9600);

  // Thông báo khởi động
  Serial.println("Receiver started, waiting for color data...");

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
  // Kiểm tra nếu có dữ liệu từ UART mềm
  if (softSerial.available()) {
    char received_color = softSerial.read();  // Đọc ký tự từ UART mềm

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

    // Bạn có thể thêm hành động khác dựa trên ký tự nhận được
    // Ví dụ: điều khiển LED, buzzer, v.v.
    // if (received_color == 'R') { digitalWrite(LED_PIN, HIGH); }
  }

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

