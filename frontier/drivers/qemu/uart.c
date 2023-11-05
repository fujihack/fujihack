#include <stdint.h>

#define SYS_UART0 0x101f1000

void uart_char(char c) {
	((volatile uint32_t *)(SYS_UART0))[0] = (uint32_t)(c);
}

void uart_str(char *s) {
	while(*s != '\0') {
		uart_char(*s);
		s++;
	}
}
