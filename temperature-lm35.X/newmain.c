/* 
 * File:   newmain.c
 * Author: Dipanjan Saha
 *
 * Created on March 13, 2019, 7:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
//#include <math.h>

#include "config.h"
#define _XTAL_FREQ 8000000UL
#include <xc.h>
#include "uart.h"
#include "adc.h"
void __interrupt(low_priority) my_low_priority_isr_routine (void) {
}// interrupt routine

void __interrupt(high_priority) my_high_priority_isr_routine (void) {
}// interrupt routine

int main() {
    UART_Init(9600);
    unsigned int val,val1;
    //float val1;
    ADC_Init();
    __delay_ms(500);
    unsigned int data=0;
  
    while(1)
    {
        
        val=ADC_Read(0);
        val1 = ((float)val*((float)500/(float)1023));
        UART_SendString("ADC VAL=");
        UART_SendIntToString(val,4);
        UART_SendChar(0x0D);
        UART_SendString("TEMP=");
        UART_SendIntToString(val1,4);
       // UART_SendFloatToString(val1,4,3);
        UART_SendChar(0x0D);
        __delay_ms(1000);
    }
    
    return (EXIT_SUCCESS);
}



