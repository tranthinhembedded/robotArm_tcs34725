#define KEY 7  // Chân điều khiển vào chế độ AT cho HC-05
#define LED 13 // Chân điều khiển LED trên bo mạch

bool ok;      // Biến kiểm tra cấu hình HC-05 thành công hay không
int var;      // Biến lưu giá trị đọc từ Serial
String bf = ""; // Chuỗi tạm (chưa sử dụng trong chương trình này)

void setup() {
  pinMode(KEY, OUTPUT);           // Cấu hình chân KEY là OUTPUT
  digitalWrite(KEY, LOW);         // Bắt đầu với trạng thái LOW (không vào chế độ AT)
  
  pinMode(LED, OUTPUT);           // Cấu hình chân LED là OUTPUT
  digitalWrite(LED, HIGH);        // Bật LED (trạng thái HIGH)
  
  delay(3000);                    // Chờ 3 giây
  
  Serial.begin(9600);             // Khởi tạo Serial ở tốc độ 9600 baud
  
  ok = configure_HC05();          // Gọi hàm configure_HC05 để cấu hình HC-05
}

void loop() {
  if (ok) {                       // Nếu cấu hình HC-05 thành công
    if (Serial.available() > 0) { // Nếu có dữ liệu từ Serial
      var = Serial.read();        // Đọc giá trị từ Serial
      
      Serial.println(var);        // In giá trị ra Serial Monitor
      
      // Kiểm tra nếu var là '1' thì bật LED
      if (var == '1') {
        digitalWrite(LED, HIGH);  // Bật LED
      }
      // Nếu var là '2' thì tắt LED
      else if (var == '2') {
        digitalWrite(LED, LOW);   // Tắt LED
      }
    }
  }
}

// Hàm cấu hình module HC-05
bool configure_HC05() {
  digitalWrite(KEY, HIGH);        // Đưa chân KEY lên HIGH để vào chế độ AT
  
  Serial.println("AT");           // Gửi lệnh "AT" để kiểm tra phản hồi
  delay(2000);                    // Chờ 2 giây
  
  if (!Serial.find("OK"))         // Nếu không tìm thấy "OK" trong phản hồi
    return false;                 // Trả về false, báo lỗi
  
  Serial.println("AT+RMAAD");     // Gửi lệnh "AT+RMAAD" để xóa tất cả các kết nối đã lưu
  delay(2000);                    // Chờ 2 giây
  
  if (!Serial.find("OK"))         // Nếu không có phản hồi "OK"
    return false;                 // Trả về false, báo lỗi

  Serial.println("AT+PSWD=1234"); // Đặt mã PIN là 1234
  delay(2000);                    // Chờ 2 giây
  
  if (!Serial.find("OK"))         // Nếu không có phản hồi "OK"
    return false;                 // Trả về false, báo lỗi

  Serial.println("AT+ROLE=0");    // Đặt module làm Slave (ROLE = 0)
  delay(2000);                    // Chờ 2 giây
  
  if (!Serial.find("OK"))         // Nếu không có phản hồi "OK"
    return false;                 // Trả về false, báo lỗi

  digitalWrite(KEY, LOW);         // Đưa chân KEY xuống LOW để thoát chế độ AT

  Serial.println("AT+RESET");     // Gửi lệnh khởi động lại HC-05
  delay(2000);                    // Chờ 2 giây
  
  if (!Serial.find("OK"))         // Nếu không có phản hồi "OK"
    return false;                 // Trả về false, báo lỗi
  
  delay(5000);                    // Chờ 5 giây để module khởi động lại

  Serial.println("Bluetooth Ready!"); // In thông báo Bluetooth đã sẵn sàng
  return true;                     // Trả về true nếu thành công
}
