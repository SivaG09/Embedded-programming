
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

//declaring the lcd functions
void lcdinit(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);

void main()
{
    unsigned char line1[6] = {0x82,0x83,0x84,0x85,0x86,0x87}; //declaring array for line1 
    unsigned char line2[6] = {0xCD,0xCC,0xCB,0xCA,0xC9,0xC8}; //declaring array for line2
    unsigned char name[6] = {"Siva.G"};   //declaring the array to be printed
    lcdinit();  //calling function lcdinit
    int i;  //declaring variable i 
    for(i=0;i<6;i++)  //for loop to get the columns in 1st line
    {
        lcd_command(line1[i]);   //setting the command to start from 0x82
        lcd_data(name[i]);       //printing the name
    }
    for(i=0;i<6;i++)   //for loop to get the columns in 2nd line
    {
        lcd_command(line2[i]);   //setting the command to start from 0xCD
        lcd_data(name[i]);       //printing the name
    }
    while(1);
}

void lcdinit()
{
 TRISC = 0x00;    //setting PORT C as output
 TRISD = 0x00;    //setting PORT D as output
 lcd_command(0x38);   //setting lcd as 2 lines, 5x7 dot lcd
 __delay_ms(100);        //generating delay for 100ms
  lcd_command(0x38);   //setting lcd as 2 lines, 5x7 dot lcd
 __delay_ms(100);         //generating delay for 100ms
  lcd_command(0x38);   //setting lcd as 2 lines, 5x7 dot lcd
 __delay_ms(100);         //generating delay for 100ms
  lcd_command(0x38);  //setting lcd as 2 lines, 5x7 dot lcd
 __delay_ms(100);        //generating delay for 100ms
 lcd_command(0x0C);  //setting display on and curson off
 __delay_ms(100);        //generating delay for 100ms
 lcd_command(0x01);     //setting clear display
 __delay_ms(100);       //generating delay for 100ms
}
void lcd_command(unsigned char cmd)
{
    RC3 = 0;    //making RS as 0
    RC0 = 1;    //making enable bit 1
    PORTD = cmd;   //assigning the cmd
    RC0 = 0;     //making enable bit 0
    __delay_ms(200);  //generating delay for 200ms
}

void lcd_data(unsigned char data)
{
    RC3 = 1;   //making RS as 1
    RC0 = 1;   //making enable bit 0
    PORTD = data;   //assigning the data
    RC0 = 0;  //making enable bit 1
    __delay_ms(200);  //generating delay for 200ms
}