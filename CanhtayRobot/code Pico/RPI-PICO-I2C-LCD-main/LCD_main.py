# Nhập các module cần thiết
from machine import I2C, Pin
from pico_i2c_lcd import I2cLcd
import utime

# Khởi tạo các nút
button_pins = [14, 15, 16, 17]  # Nút 1, 2, 3, 4
buttons = [machine.Pin(pin, machine.Pin.IN, machine.Pin.PULL_UP) for pin in button_pins]
previous_states = [1] * len(buttons)  # Mặc định là 1 (nhả, do pull-up)
change_counts = [0] * len(buttons)   # Biến đếm thay đổi trạng thái
press_counts = [0] * 3               # Biến đếm số lần nhấn-nhả cho Btn1, Btn2, Btn3

# Định nghĩa tham số LCD
i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
I2C_ADDR = 0x27      # Địa chỉ I2C của LCD (có thể cần thay đổi)
NUM_LINES = 2        # Số dòng của LCD
NUM_COLUMNS = 16     # Số cột của LCD

# Tạo đối tượng LCD
lcd = I2cLcd(i2c, I2C_ADDR, NUM_LINES, NUM_COLUMNS)

# Xóa màn hình LCD
lcd.clear()

# Hiển thị nhãn các nút trên dòng 1
lcd.move_to(0, 0)
lcd.putstr("Btn1")
lcd.move_to(5, 0)
lcd.putstr("Btn2")
lcd.move_to(10, 0)
lcd.putstr("Btn3")

# Hàm cập nhật hiển thị LCD
def update_lcd():
    lcd.move_to(0, 1)
    lcd.putstr("                ")  # Xóa dòng 2
    lcd.move_to(1, 1)
    lcd.putstr(str(press_counts[0]))  # Btn1
    lcd.move_to(6, 1)
    lcd.putstr(str(press_counts[1]))  # Btn2
    lcd.move_to(11, 1)
    lcd.putstr(str(press_counts[2]))  # Btn3

# Hàm kiểm tra nhấn-nhả và xử lý
def check_buttons():
    global previous_states, change_counts, press_counts
    for i in range(len(buttons)):
        current_state = buttons[i].value()  # Đọc trạng thái hiện tại
        # Kiểm tra nếu trạng thái thay đổi
        if current_state != previous_states[i]:
            change_counts[i] += 1  # Tăng biến đếm thay đổi
            previous_states[i] = current_state  # Cập nhật trạng thái trước đó
            # Nếu hoàn thành một chu kỳ nhấn-nhả (2 thay đổi)
            if change_counts[i] == 2:
                if i < 3:  # Nút 1, 2, 3: Tăng số lần nhấn-nhả
                    press_counts[i] += 1
                    update_lcd()  # Cập nhật LCD
                else:  # Nút 4: Reset tất cả biến đếm
                    press_counts[:] = [0] * 3
                    change_counts[:] = [0] * len(buttons)
                    update_lcd()  # Cập nhật LCD
                change_counts[i] = 0  # Reset biến đếm thay đổi

# Hiển thị ban đầu
update_lcd()

# Vòng lặp chính
while True:
    check_buttons()
    utime.sleep_ms(50)  # Đợi 50ms để chống dội