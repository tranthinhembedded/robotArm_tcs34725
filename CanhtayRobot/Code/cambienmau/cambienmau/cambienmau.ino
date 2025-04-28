#include <SoftwareSerial.h>

// Khai báo cổng UART mềm (RX, TX)
SoftwareSerial softSerial(10, 11); // RX: 10, TX: 11

// Khai báo biến chung
unsigned char Re_buf[11], counter = 0; 
unsigned char sign = 0;
byte rgb[3] = {0};
char current_color = 'N'; // Biến lưu trạng thái màu hiện tại (N: None, R: Red, G: Green, B: Blue)

void setup() {
  // Khởi tạo cổng Serial cho cảm biến GY-33 và Serial Monitor
  Serial.begin(9600);
  
  // Khởi tạo cổng UART mềm
  softSerial.begin(9600);
  
  delay(10); // Đợi cảm biến ổn định
  
  // Gửi lệnh khởi tạo tới cảm biến GY-33
  Serial.write(0xA5); // Lệnh khởi tạo
  Serial.write(0x01); // Khởi động chế độ xuất liên tục
  Serial.write(0xA6); // Khởi động chế độ xuất liên tục
}

void loop() {
  unsigned char i = 0, sum = 0;
  
  // Đọc dữ liệu từ cảm biến GY-33
  while (Serial.available()) {
    Re_buf[counter] = (unsigned char)Serial.read(); // Đọc từng byte dữ liệu
    if (counter == 0 && Re_buf[0] != 0x5A) return; // Kiểm tra khung đầu của dữ liệu
    counter++;
    if (counter == 8) { // Nhận đủ dữ liệu cho một khung
      counter = 0; // Đặt lại bộ đếm cho khung tiếp theo
      sign = 1; // Đặt cờ báo hiệu dữ liệu hợp lệ
    }
  }
  
  if (sign) {
    sign = 0; // Reset cờ báo hiệu
    sum = 0;
    
    // Tính tổng kiểm tra
    for (i = 0; i < 7; i++) sum += Re_buf[i];
    
    if (sum == Re_buf[i]) { // Nếu tổng kiểm tra khớp
      rgb[0] = Re_buf[4]; // Giá trị Red
      rgb[1] = Re_buf[5]; // Giá trị Green
      rgb[2] = Re_buf[6]; // Giá trị Blue
      
      char new_color = 'N'; // Biến tạm để xác định màu mới
      
      // Tìm màu có giá trị lớn nhất
      if (rgb[0] >= rgb[1] && rgb[0] >= rgb[2] && rgb[0] > 200) {
        new_color = 'R';
      }
      else if (rgb[1] >= rgb[0] && rgb[1] >= rgb[2] && rgb[1] > 180) {
        new_color = 'G';
      }
      else if (rgb[2] >= rgb[0] && rgb[2] >= rgb[1] && rgb[2] > 200) {
        new_color = 'B';
      }
      
      // Chỉ xử lý khi màu thay đổi
      if (new_color != current_color) {
        current_color = new_color; // Cập nhật trạng thái màu hiện tại
        
        // Gửi ký tự màu qua UART mềm
        softSerial.write(current_color);
        
        // In ra Serial Monitor để kiểm tra
        switch (current_color) {
          case 'R':
            Serial.print("Red: ");
            Serial.println(rgb[0]);
            break;
          case 'G':
            Serial.print("Green: ");
            Serial.println(rgb[1]);
            break;
          case 'B':
            Serial.print("Blue: ");
            Serial.println(rgb[2]);
            break;
          default:
            Serial.println("NONE");
            break;
        }
      }
    }
  }
}