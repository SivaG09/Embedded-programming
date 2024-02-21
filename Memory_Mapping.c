
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
    unsigned char *option_reg = 0x81;   //storing the address of OPTION_REG in pointer option_reg
    unsigned char *trisb = 0x86;        //storing the address of TRISB in pointer trisb
    unsigned char *portb = 0x06;        //storing the address of PORTB in pointer portb
    unsigned char *trisc = 0x87;        //storing the address of TRISC in pointer trisc
    unsigned char *portc = 0x07;        //storing the address of PORTC in pointer portc   
    
    *trisb = 0xF0;       //making RB4 - RB7 pin as input
    *trisc = 0x00;       //setting PORTB as Output
    *portc = 0x00;       //setting PORTC in OFF STATE
    *portb = 0x00;        //setting PORTB in OFF STATE
    *option_reg &= 0x7F;     //Enable internal Pullup  
    
    while(1)
    {
        if(*portb == 0xE0)     //checking sw1(RB4) is pressed
            *portc = 0x04;     //if yes, making LED1 OFF LED ON
        else if(*portb == 0xD0)   //checking sw1(RB4) is pressed
            *portc = 0x02;       //if yes, making LED1 ON LED OFF
        else if(*portb == 0xB0)  //checking sw1(RB4) is pressed
            *portc = 0x00;      //if yes, making LED1 OFF LED OFF
        else if(*portb == 0x70) //checking sw1(RB4) is pressed
            *portc = 0x06;       //if yes, making LED1 ON LED ON
    }    
}