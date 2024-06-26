#include <stdbool.h>

#include <xc.h>

#include "uart.h"

void uart_end(void);

void uart_start(void)
{
	OSCCONbits.IRCF = 14;
	
	#ifndef SIMULATOR
	while (!OSCSTATbits.PLLR);
	#endif
	
	BAUDCONbits.BRG16 = 1;
	TXSTAbits.BRGH = 1;
	SPBRG = 68;
	
	RCSTAbits.SPEN = 1;
	TXSTAbits.TXEN = 1;
}

void uart_stop(void)
{
	while (!TXSTAbits.TRMT);
	
	TXSTAbits.TXEN = 0;
	RCSTAbits.SPEN = 0;
	
	uart_end();
}

void uart_end(void)
{
	while (true);
}

int uart_putchar(int c)
{
	while (!PIR1bits.TXIF);
	TXREG = (unsigned char) c;
	return c;
}

void putch(char c)
{
	(void) uart_putchar(c);
}
