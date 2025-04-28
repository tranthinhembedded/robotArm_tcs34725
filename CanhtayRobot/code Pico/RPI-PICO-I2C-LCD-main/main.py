from machine import UART, I2C, Pin
from pico_i2c_lcd import I2cLcd
import time

# Khởi tạo UART cho cảm biến GY-33 (GP16 TX, GP17 RX)
uart_sensor = UART(0, 9600, tx=Pin(16), rx=Pin(17))
# Khởi tạo UART để gửi dữ liệu màu (GP4 TX, GP5 RX)
uart_send = UART(1, 9600, tx=Pin(4), rx=Pin(5))

# Khởi tạo I2C cho LCD (GP0 SDA, GP1 SCL)
i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
I2C_ADDR = 0x27  # Địa chỉ I2C của LCD
NUM_LINES = 2
NUM_COLUMNS = 16
lcd = I2cLcd(i2c, I2C_ADDR, NUM_LINES, NUM_COLUMNS)

button_pins = [6, 7, 8, 9, 10]  # Nút 1, 2, 3, 4, 5
buttons = [machine.Pin(pin, machine.Pin.IN, machine.Pin.PULL_UP) for pin in button_pins]
previous_states = [1] * len(buttons)  # Mặc định là 1 (nhả, do pull-up)
change_counts = [0] * len(buttons)

# Biến đếm số lượng màu
color_counts = {'R': 0, 'G': 0, 'B': 0}
auto_mode = True
# Hiển thị ban đầu trên LCD
lcd.clear()
lcd.move_to(0, 0)
lcd.putstr("Mode: Auto")
lcd.move_to(0, 1)
lcd.putstr("R:0 G:0 B:0")
#reset biến đếm
def reset_counts():
    global color_counts
    color_counts = {'R': 0, 'G': 0, 'B': 0}
    update_lcd()

# Hàm cập nhật LCD
def update_lcd():
    lcd.move_to(0, 0)
    lcd.putstr("Mode: Auto  " if auto_mode else "Mode: Manual")
    lcd.move_to(0, 1)
    lcd.putstr("R:{} G:{} B:{}".format(color_counts['R'], color_counts['G'], color_counts['B']))
# Khởi tạo cảm biến
uart_sensor.write(b'\xA5\x01\xA6')
time.sleep(0.01)

# Biến lưu trữ
Re_buf = bytearray(8)
counter = 0
current_color = 'N'

def check_buttons():
    global previous_states, change_counts, auto_mode
    for i in range(len(buttons)):
        current_state = buttons[i].value()
        if current_state != previous_states[i]:
            time.sleep_ms(5)  # Chống dội 5ms
            if buttons[i].value() == current_state:  # Kiểm tra lại để xác nhận
                change_counts[i] += 1
                previous_states[i] = current_state
                if change_counts[i] == 2:
                    if i == 0:  # Nút 1: Chuyển chế độ
                        auto_mode = not auto_mode
                        update_lcd()
                    elif i == 1:  # Nút 2: Reset biến đếm
                        reset_counts()
                    elif not auto_mode:  # Nút 3, 4, 5: Gửi R, G, B
                        if i == 2:
                            uart_send.write('R'.encode('ascii'))
                            color_counts['R'] += 1
                        elif i == 3:
                            uart_send.write('G'.encode('ascii'))
                            color_counts['G'] += 1
                        elif i == 4:
                            uart_send.write('B'.encode('ascii'))
                            color_counts['B'] += 1
                        update_lcd()
                    change_counts[i] = 0


while True:
    check_buttons()
    if uart_sensor.any():
        if(auto_mode):
            byte = uart_sensor.read(1)[0]
            if counter == 0 and byte != 0x5A:
                continue
            Re_buf[counter] = byte
            counter += 1
            if counter == 8:
                sum = 0
                for i in range(7):
                    sum = (sum + Re_buf[i]) % 256
                if sum == Re_buf[7]:
                    R = Re_buf[4]
                    G = Re_buf[5]
                    B = Re_buf[6]
                    new_color = 'N'
                    if R >= G and R >= B and R > 180:
                        new_color = 'R'
                    elif G >= R and G >= B and G > 100:
                        new_color = 'G'
                    elif B >= R and B >= G and B > 180:
                        new_color = 'B'
                    if new_color != current_color:
                        if new_color in color_counts:
                            color_counts[new_color] += 1
                            update_lcd()
                        uart_send.write(new_color.encode('ascii'))
                        if new_color == 'R':
                            print("Red:", R)
                        elif new_color == 'G':
                            print("Green:", G)
                        elif new_color == 'B':
                            print("Blue:", B)
                        else:
                            print("NONE")
                        current_color = new_color
                counter = 0