/* 
 * File:   uart.h
 * Author: Dipanjan Saha
 *
 * Created on March 14, 2019, 6:31 AM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

void UART_Init(int baudrate)
{
   RCSTA |=(1<<7);
   TRISC &=~(1<<6);
   TRISC |=(1<<7);
   TXSTA |=((1<<5)|(1<<2));
   TXSTA &=~(1<<4);
   RCSTA |=(1<<7); // SPEN=7 
   SPBRG=(unsigned char)((_XTAL_FREQ/(16*(unsigned long)(baudrate)))-1);
}


void UART_SendChar(unsigned char data)
{
    TXREG=data;
}

void UART_SendString(char *str)
{  
    while(*str!='s')
    {
    TXREG=*str;
    __delay_ms(100);
    str++;
    }
}


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

