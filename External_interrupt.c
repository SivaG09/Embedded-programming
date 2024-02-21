
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
    TRISB = 0X01;   //setting RB0 as input
    PORTB = 0x00;   //Clearing PORTB 
    TRISD = 0x00;   //setting PORTD as Output
    PORTD = 0x00;   //Clearing PORTD 
    TRISC = 0x00;   //setting PORTC as Output
    PORTC = 0x00;   //Clearing PORTC
    OPTION_REG &= 0x3F;  //Enable Pullup and making INTEDG(6th Bit) as Falling edge
    INTCON = 0x90;   //10010000 , Enable Global Interrupt and External Interrupt
    while(1)
    {
        PORTD = ~PORTD;   //toggle PORTD
        __delay_ms(200);  //delay for 200 ms
    }
}
void __interrupt() EXTISR()  //Interrupt Function
{
    if(INTCON & 0x02)   //checking Interrupt Occured or not
    {
        if(RB0 == 0)   //checking Switch is Pressed or not
        {
            PORTC = ~PORTC;  //Toggle PORTC
            
        }
         INTCON &= 0xFD;   //clearing flag bit
         __delay_ms(3000);
    }
}