
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

//declaring the lcd functions and variables
void lcdinit(void);
void lcd_data(unsigned char data);
void lcd_command(unsigned char cmd);
void LcdOutput(unsigned int i);
unsigned char j,k[10],Equal,sub,plus; 
unsigned int num1,num2,res,m,n;     

void main()
{
    //initializing lcd
    lcdinit(); 
    num1=200;    //num1 value
    num2=100;    //num2 value
    Equal='=';   //assigning =
    sub='-';     //assigning -
    plus='+';    //assigning +
    
    lcd_command(0x80);   //command to display from first row first column
    LcdOutput(num1);     //displaying num1
    lcd_command(0x83);   //command to display from 0x83
    lcd_data(sub);       //displaying '-'
    lcd_command(0x84);   //command to display from 0x84
    LcdOutput(num2);     //displaying num2
    lcd_command(0x87);   //command to display from 0x87
    lcd_data(Equal);     //displaying '='
    lcd_command(0x88);   //command to display from 0x88
    if(num1 > num2)      //checking num1 is greater than num2 or not
    {
        lcd_data(plus);      //displaying '+'
        lcd_command(0x89);   //command to display from 0x89
        res = num1-num2;     //calculating the res
        LcdOutput(res);     //displaying num1
    }
    else
    {
        lcd_data(sub);       //displaying '-'
        res = num2-num1;     //calculating the result
        lcd_command(0x89);  //command to display from 0x89
        LcdOutput(res);     //displaying num1
    } 
    while(1);    //while loop to do nothing
}
 
//lcdiniti definition
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
 lcd_command(0x06);    //setting entry mode, increments to right shift
 __delay_ms(100);       //generating delay for 100ms
 lcd_command(0x01);     //setting clear display
 __delay_ms(100);       //generating delay for 100ms
}

//lcdOutput definition
void LcdOutput(unsigned int i)
{
  unsigned char s,j=1;     //declaring the required variables
  m=i;                     //assigning the i value to m
  while(m!=0)              //while loop to run until m == 0
  {
      s = m -((m/10)*10);     //logic to get the last digit and storing in variable s
      k[j] = s;               //assigning the s value array k[]
      j++;                    //incrementing the j value
      m=m/10;                 //storing the remaining digits
  }
  k[j] = '\0';               //once all the numbers are stored, making the last member as NULL
  j=j-1;                     //decrementing j value
  while(j!=0)                //while loop to run till j == 0
  {
      n = 0x30 + k[j];      //making the number as character 
      lcd_data(n);          //displaying the character 
      j--;                  //decrementing the j 
  }
}


void lcd_command(unsigned char cmd)
{
    PORTC &= 0xF7;      //making RS as 0 
    PORTD = cmd;       //assigning the command
    PORTC |= 0x01;       //making EN as 1
    PORTC &= ~0x01;      //making EN as 0
    __delay_ms(200);   //delay for 200 ms
}
void lcd_data(unsigned char data)
{
    PORTC |= 0x08;      //making RS as 1 
    PORTD = data;       //assigning the command
    PORTC |= 0x01;       //making EN as 1
    PORTC &= ~0x01;      //making EN as 0
    __delay_ms(200);   //delay for 200 ms
}

