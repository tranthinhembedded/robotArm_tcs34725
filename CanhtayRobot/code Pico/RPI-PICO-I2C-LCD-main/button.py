import machine
import utime

# Định nghĩa các chân GPIO cho 4 nút nhấn và 3 LED
button_pins = [14, 15, 16, 17]  # Nút 1, 2, 3, 4
led_pins = [0, 1, 2]            # LED 1, 2, 3

# Khởi tạo các đối tượng Pin cho nút nhấn (pull-up) và LED (output)
buttons = [machine.Pin(pin, machine.Pin.IN, machine.Pin.PULL_UP) for pin in button_pins]
leds = [machine.Pin(pin, machine.Pin.OUT) for pin in led_pins]

# Biến lưu trạng thái trước đó và biến đếm cho từng nút
previous_states = [1] * len(buttons)  # Mặc định là 1 (nhả, do pull-up)
change_counts = [0] * len(buttons)   # Biến đếm số lần thay đổi trạng thái
# Hàm tắt tất cả LED
def turn_off_all_leds():
    for led in leds:
        led.value(0)
# Hàm kiểm tra và điều khiển LED dựa trên nhấn-nhả
def check_buttons():
    global previous_states, change_counts
    for i, button in enumerate(buttons):
        current_state = button.value()
        # Kiểm tra nếu trạng thái thay đổi
        if current_state != previous_states[i]:
            change_counts[i] += 1  # Tăng biến đếm
            previous_states[i] = current_state  # Cập nhật trạng thái trước đó
            # Nếu biến đếm đạt 2 (một lần nhấn và một lần nhả)
            if change_counts[i] == 2:
                if i < 3:  # Nút 1, 2, 3 điều khiển LED tương ứng
                    turn_off_all_leds()
                    leds[i].value(1)  # Bật LED tương ứng
                    print(f"LED {i+1} sáng")
                else:  # Nút 4 tắt tất cả LED
                    for led in leds:
                        led.value(0)  # Tắt tất cả LED
                    print("Nút 4 đã nhấn-nhả, LED tắt")
                change_counts[i] = 0  # Reset biến đếm

# Tắt tất cả LED khi khởi động
turn_off_all_leds()

# Vòng lặp chính
while True:
    check_buttons()
    utime.sleep(0.05)  # Đợi 50ms để tránh đọc quá nhanh