/* 
 * File:   newmain.c
 * Author: Dipanjan Saha
 *
 * Created on March 13, 2019, 7:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "config.h"
#define _XTAL_FREQ 8000000UL
#include <xc.h>
#include "uart.h"
#include "adc.h"

int main(int argc, char** argv) {
    UART_Init(9600);
    while(1)
    {
        UART_SendChar('A');
        __delay_ms(100);
        //UART_SendString("Dips");
        //__delay_ms(1000);
    }
    
    return (EXIT_SUCCESS);
}


