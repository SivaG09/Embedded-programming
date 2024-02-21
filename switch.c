
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 6000000

void main()
{
    unsigned char input; //declaring variable input to get the port value
    TRISC = 0x0F; //configuring RC0-RC3 as Input
    TRISD = 0x00; //configuring PORTD as Output
    PORTC = 0x00; //Initializing PORTC as 0
    PORTD = 0x00; //Initializing PORTD as 0

    //using while loop for running continuously
    while(1)
    {
        input = PORTC; //getting PORTC value in variable input
        
        //Using switch case to get appropriate Output
        switch(input)
        {            
             case 0x0E: //for pressing RC0
                PORTD = 0x20; //making RD3 as low and RD5 as high
                break;
            case 0x0D://for pressing RC1
                PORTD = 0x08; //making RD3 as high and RD5 as low
                break;            
            case 0x0B: //for pressing RC2
                PORTD = 0x28; //making RD3 as high and RD5 as high
                break;
            case 0x07: //for pressing RC3
                PORTD = 0x00; //making RD3 as low and RD5 as low
                break;
            default: //default case for all other input
                PORTD = 0x00; //making RD3 as low and RD5 as low
                break;
        }
    }

}
