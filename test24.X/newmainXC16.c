/*
 * File:   newmainXC16.c
 * Author: tuxrox
 *
 * Created on August 5, 2016, 10:31 AM
 */


#include <xc.h>
#define FCY 8000000UL
#include <libpic30.h>

void __attribute__((interrupt, auto_psv))  _INT0Interrupt(void) {
    // turn on all lights.
    LATA = 0xFFFF;
    LATAbits.LATA4 = 0;
    LATB = 0xFF;
    
    IFS0bits.INT0IF = 0;    //Clear the INT0 interrupt flag or else
                            //the CPU will keep vectoring back to the ISR
}

int main(void) {
    AD1PCFG	 =	0xFFFF;	 //set to all digital I/O

    // Set TRISA to output on pins 1 and 2
    TRISA = 0x00;
    TRISB = 0x00;
    
    // Pre set RA0 and RA1 to initial values
    LATAbits.LATA0 = 1;
    LATAbits.LATA1 = 1;
    LATAbits.LATA2 = 1;
    LATAbits.LATA3 = 0; // This pin seams to not work currently, may be setting issue
    LATAbits.LATA4 = 1;
    
    LATBbits.LATB0 = 1;
    LATBbits.LATB1 = 1;
    LATBbits.LATB2 = 1;
    LATBbits.LATB3 = 1;
    
    INTCON2 = 0x001F;       /*Setup INT1, INT2, INT3 & INT4 pins to interupt */
                                /*on falling edge and set up INT0 pin to interupt */
                                /*on rising edge */
    IFS0bits.INT0IF = 0;    /*Reset INT0 interrupt flag */
    IEC0bits.INT0IE = 1;    /*Enable INT0 Interrupt Service Routine */
    
    //Toggle after delay
    unsigned int i = 0;
    while(1){
        __delay_ms(50);
        switch(i) {
            case 0:
                __builtin_btg((unsigned int *)&LATA, 0);
                break;
            case 1:
                __builtin_btg((unsigned int *)&LATA, 1);
                break;
            case 2:
                __builtin_btg((unsigned int *)&LATA, 2);
                break;
            case 3:
                __builtin_btg((unsigned int *)&LATA, 4);
                break;
            case 4:
                __builtin_btg((unsigned int *)&LATB, 0);
                break;
            case 5:
                __builtin_btg((unsigned int *)&LATB, 1);
                break;
            case 6:
                __builtin_btg((unsigned int *)&LATB, 2);
                break;
            case 7:
                __builtin_btg((unsigned int *)&LATB, 3);
                break;
            default:
                break;
        }
        i++;
        if(i>7){
            i=0;
        }
        
    }
    return 0;
}
