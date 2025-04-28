#include <Servo.h>

// Mảng chứa dữ liệu cảm biến và biến đếm
unsigned char Re_buf[11], counter = 0;
unsigned char sign = 0;
byte rgb[3] = {0};
String currentColor = "None";  // Biến lưu trữ màu hiện tại

// Khai báo các Servo
Servo updown;
Servo vuon;
Servo kep;
Servo xoay;

void setup() {
  // Khởi tạo servo
  kep.attach(3);
  vuon.attach(5);
  xoay.attach(6);
  updown.attach(9);

  // Đặt vị trí ban đầu cho servo
  updown.write(0);
  vuon.write(0);
  kep.write(0);
  xoay.write(0);

  // Khởi tạo giao tiếp Serial cho monitor và cảm biến GY-33
  Serial.begin(9600);
  delay(10);
  // Gửi lệnh khởi tạo cho cảm biến GY-33
  Serial.write(0xA5);
  Serial.write(0x01);
  Serial.write(0xA6);
}

void loop() {
  unsigned char i = 0, sum = 0;
  
  if (sign) {
    sign = 0;
    // Tính tổng cho 7 byte đầu
    for (i = 0; i < 7; i++) {
      sum += Re_buf[i];
    }
    // Kiểm tra tổng khớp với byte kiểm tra
    if (sum == Re_buf[i]) { // i đã tăng thành 7
      rgb[0] = Re_buf[4];
      rgb[1] = Re_buf[5];
      rgb[2] = Re_buf[6];

      // Xác định màu có giá trị lớn nhất
      byte maxValue = rgb[0];
      String maxColor = "Red";
      if (rgb[1] > maxValue) {
        maxValue = rgb[1];
        maxColor = "Green";
      }
      if (rgb[2] > maxValue) {
        maxValue = rgb[2];
        maxColor = "Blue";
      }

      // Kiểm tra nếu giá trị lớn nhất vượt ngưỡng và khác màu hiện tại
      if (maxValue > 200 && maxColor != currentColor) {
        Serial.print(maxColor);
        Serial.print(": ");
        Serial.println(maxValue);
        currentColor = maxColor;  // Cập nhật màu hiện tại

        // Gọi hàm điều khiển tương ứng với màu
        if (maxColor == "Red") {
          RED();
        } else if (maxColor == "Green") {
          GREEN();
        } else if (maxColor == "Blue") {
          BLUE();
        }
      } else if (maxValue <= 0 && currentColor != "None") {
        Serial.println("No color detected above threshold");
        currentColor = "None"; // Đặt lại khi không có màu nào vượt ngưỡng
      }
    }
  }
}

// Hàm tự động được gọi khi có dữ liệu đến Serial
void serialEvent() {
  while (Serial.available()) {
    Re_buf[counter] = (unsigned char)Serial.read();
    // Kiểm tra byte đầu tiên, nếu không phải 0x5A thì bỏ qua
    if (counter == 0 && Re_buf[0] != 0x5A) return;
    counter++;
    if (counter == 8) {
      counter = 0;
      sign = 1;
    }
  }
}

// Hàm điều khiển cho màu Red
void RED() {
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

// Hàm điều khiển cho màu Green
void GREEN() {
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

// Hàm điều khiển cho màu Blue
void BLUE() {
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
