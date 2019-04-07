#include <msp430.h> 
#include "Basic_config/Basic_config.h"
#include "uart/UART.h"
#include <stdio.h>
#include <string.h>
void set_ISR(void);

char TXbuffer[30] ="PIF_lab\r\n";
/*
 * main.c
 */
int main(void)
{
	P1DIR |= BIT6;
	P1OUT |= BIT6;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    // set mode PORT2 in GPIO
	P2SEL = 0;
	P2SEL2= 0;
	// config clock 1MHZ + source DCOCLK + divede 0
	Config_Clocks();
	// set p1.1 and p1.2 mode uart +clock source select SMCLK
	uart_init();
	// set interrupt global
	set_ISR();
	while (1)
	{
    uart_puts(&TXbuffer);
	}
}
void set_ISR(void)
{
	    _BIS_SR(GIE);
		IE2 |= UCA0RXIE;
		IE2 |= UCA0TXIE;
}

