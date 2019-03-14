/* 
 * File:   adc.h
 * Author: Dipanjan Saha
 *
 * Created on March 14, 2019, 6:32 AM
 */

#ifndef ADC_H
#define	ADC_H


void ADC_Init()
{
    //TRISA |=((1<<5)|(1<<3)|(1<<2)|(1<<1)|(1<<0)); // 
    //TRISE |=((1<<0)|(1<<1)|(1<<2));
    TRISA=0xff;
    TRISE=0xff;
    ADCON1 &=~((1<<0)|(1<<1)|(1<<2)|(1<<3)); // all analog with internal reference RIGHT justified
    ADCON1 |=((1<<6)|(1<<7));
    ADCON0 &=~(1<<7);
    ADCON0 |=(1<<6);

    ADCON0|=(1<<0);
   
    
}

unsigned int ADC_Read(char channel)
{
   // unsigned int retval;
    char portval=ADCON0;
    portval &=0b11000111;
    portval |=(channel<<3);
    ADCON0 = portval;
    //ADCON0 &=~((1<<5)|(1<<4)|(1<<3));
    ADCON0 |=(1<<2);
    while((ADCON0 & (1<<2)) >= 1) // wait while conversion going on
    {  
    }

    unsigned int retval=((ADRESH & 0b00000111)<<8)|ADRESL; 
    return retval;
}

#endif	/* ADC_H */

