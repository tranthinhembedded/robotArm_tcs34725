#define F_CPU 16000000UL
#define BAUD 115200
#define MYUBRR F_CPU/16/BAUD-1

void UART_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

unsigned char UART_receive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void UART_sendString(const char *str) {
    while (*str) {
        UART_transmit(*str++);
    }
}

void setup() {
    UART_init(MYUBRR);
    UART_sendString("UART Initialized\r\n");
}

void loop() {
    if (UCSR0A & (1 << RXC0)) {
        unsigned char receivedChar = UART_receive();
        UART_transmit(receivedChar);
    }
}
