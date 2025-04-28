#include <SoftwareSerial.h>

// Khai báo biến chung, không lặp lại
unsigned char Re_buf[11], counter = 0;
unsigned char sign = 0;
byte rgb[3] = {0};

// Khởi tạo giao tiếp UART
SoftwareSerial mySerial(10, 11); // RX, TX - Kết nối với GY-33

void setup() {
   Serial.begin(9600);      // Khởi tạo giao tiếp UART cho Serial Monitor
   mySerial.begin(9600);    // Khởi tạo SoftwareSerial cho cảm biến GY-33
   mySerial.listen();       // Chuyển quyền nghe về SoftwareSerial
   delay(10);               // Đợi cảm biến ổn định

   // Gửi lệnh khởi tạo tới cảm biến GY-33
   mySerial.write(0xA5);    // Lệnh khởi tạo
   mySerial.write(0x01);    // Khởi động chế độ xuất liên tục
   mySerial.write(0xA6);    // Khởi động chế độ xuất liên tục
} 

void loop() {
  unsigned char i = 0, sum = 0;
  
  // Đọc dữ liệu từ cảm biến GY-33
  while (mySerial.available()) {   
    Re_buf[counter] = (unsigned char)mySerial.read();  // Đọc từng byte dữ liệu
    if (counter == 0 && Re_buf[0] != 0x5A) return;     // Kiểm tra khung đầu của dữ liệu
    counter++;       
    if (counter == 8) {  // Nhận đủ dữ liệu cho một khung
      counter = 0;       // Đặt lại bộ đếm cho khung tiếp theo
      sign = 1;          // Đặt cờ báo hiệu dữ liệu hợp lệ
    }      
  }

  if (sign) {
    sign = 0;  // Reset cờ báo hiệu
    sum = 0;
    
    // Tính tổng kiểm tra
    for (i = 0; i < 7; i++) sum += Re_buf[i]; 

    if (sum == Re_buf[i]) {  // Nếu tổng kiểm tra khớp
      rgb[0] = Re_buf[4];    // Giá trị Red
      rgb[1] = Re_buf[5];    // Giá trị Green
      rgb[2] = Re_buf[6];    // Giá trị Blue

      // In giá trị màu ra Serial Monitor
      Serial.print("r: ");
      Serial.print(rgb[0]);
      Serial.print(", g: ");
      Serial.print(rgb[1]);
      Serial.print(", b: ");
      Serial.println(rgb[2]);
    }
  } 
}
