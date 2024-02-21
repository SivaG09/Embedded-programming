
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
//declaring the required functions and variable
void initpwm(void);
void pwmchange(void);
unsigned char pwmhigh20,pwmlow20;
unsigned char pwmhigh60,pwmlow60;
unsigned char pwmhigh90,pwmlow90;

void main()
{
    initpwm();   //calling init function
    while(1)
    {
        pwmchange();   //calling pwmchange function
    }
}
//init function defintion
void initpwm(void)
{
    TRISC = 0xFB;   //1111 1011 , making RC2 as output
    CCP1CON = 0x0C;  //0000 1100 , configuring to PWM mode
    T2CON = 0x06;    //setting prescale value as 1:16
    PR2 = 0x2F ;     //initializing PR2 value as 47
    pwmhigh20 = 0x09;  //CCPR1L value for 20% duty cycle
    pwmlow20 = 0x20;   //storing 4th and 5th bit value of CCP1CON register for 20% DC 
    pwmhigh60 = 0x1C;    //CCPR1L value for 60% duty cycle
    pwmlow60 = 0x00;   //storing 4th and 5th bit value of CCP1CON register for 60% DC 
    pwmhigh90 = 0x2A;    //CCPR1L value for 90% duty cycle
    pwmlow90 = 0x10;   //storing 4th and 5th bit value of CCP1CON register for 90% DC 
}

void pwmchange(void)
{
    CCPR1L = pwmhigh20;       //assigning the pwmhigh20 value  to CCPR1L register
    //assigning the CCP1CON register value by clearing 4th and 5th bit and doing bitwise operation
    CCP1CON = (CCP1CON & 0xCF) | pwmlow20;
    __delay_ms(3000);   //delay for 3 secs
    CCPR1L = pwmhigh60;       //assigning the pwmhigh60 value  to CCPR1L register
    //assigning the CCP1CON register value by clearing 4th and 5th bit and doing bitwise operation
    CCP1CON = (CCP1CON & 0xCF) | pwmlow60;
    __delay_ms(3000);   //delay for 3 secs
    CCPR1L = pwmhigh90;       //assigning the pwmhigh90 value  to CCPR1L register
    //assigning the CCP1CON register value by clearing 4th and 5th bit and doing bitwise operation
    CCP1CON = (CCP1CON & 0xCF) | pwmlow90;
    __delay_ms(3000);   //delay for 3 secs
}