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
#ifndef MATH_H
#define MATH_H
#include <math.h>
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
    
    while ((TXSTA & (1<<1)) ==0)
    {
       //wait till TXREG buffer is free
    }
    TXREG=data;
    
}

void UART_SendString(char *str)
{  
    while(*str!='\0')
    {
        while ((TXSTA & (1<<1)) ==0)
        {
            //wait till TXREG buffer is free
        }
        TXREG=*str;
    //__delay_ms(100);
    str++;
    }
}
void UART_SendIntToString(int data,char numberOfDigits)
{
    char cnt=0;
    if(data<0)
    {
        UART_SendChar(45);// send negative
        data*=-1;
    }
    int data1=data;
    while((data1/pow(10,cnt))>=1)
    {
        cnt++;
    }
    char h_val;
    if(numberOfDigits!=0 && numberOfDigits>=cnt)
    {
        cnt=numberOfDigits;
    }
    //for(char i=(numberOfDigits-1);i>=1;i--)
    for(char i=(cnt-1);i>=1;i--)
    {
        h_val=data/(pow(10,i));
        UART_SendChar(h_val+48);
        data=data-(h_val*(pow(10,i)));
    }
    UART_SendChar(data+48);
}

void UART_SendFloatToString(float val, char numberOfDigits,char decPoints)
{
    if(val<0) // checking for negative
    {
        UART_SendChar(45);// send negative
        val=(float)val*(float)(-1);
    }
    int int_val=val;
    int dec_val=((float)val-(float)int_val)*pow(10,decPoints);
    
    char h_val;
    for(char i=(numberOfDigits-1);i>=1;i--) // printing integer part
    {
        h_val=int_val/(pow(10,i));
        UART_SendChar(h_val+48);
        int_val-=(h_val*(pow(10,i)));
    }
    UART_SendChar(int_val+48);
    UART_SendChar(46); // decimal point
    
    for(char i=(decPoints-1);i>=1;i--)
    {
        h_val=dec_val/(pow(10,i));
        UART_SendChar(h_val+48);
        dec_val-=(h_val*(pow(10,i)));
    }
    UART_SendChar(dec_val+48);
    
}
#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

