
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
unsigned char n,j;
unsigned char k[10],arr[8]={"Dig Val:"},arr1[8]={"Cal Val:"};
unsigned int lovalue,hivalue,m,delaycount,i;
unsigned long value,voltage;

void main()
{ 
    //calling lcdinit functions
    lcdinit();
    while(1)
    {
        lcd_command(0x80);   //command to start from first line first character
        for(i=0;i<8;i++)     //for loop to get characters from arr 
        {
           lcd_data(arr[i]);   //displaying character by character
        }
        lcd_command(0xC0);    //command to start from second line first character
        for(i=0;i<8;i++)     //for loop to get characters from arr1
        {
            lcd_data(arr1[i]);   //displaying character by character
        }
        ADCON0 |= 0x04;           //making the conversion On
        while(ADCON0 & 0x04);     //running while loop until the conversion bit get 0
        lovalue = ADRESL;         //storing the ADRESL register value to lovalue
        hivalue = ADRESH;         //storing the ADRESH register value to hivalue
        value = ((unsigned int) hivalue <<8) + (unsigned int)lovalue;    //adding both the values to get the 10 bit value
        voltage = value*100/1023;    //calibrating the value to 0-48
        lcd_command(0x88);           //command to display from 88
        LcdOutput(value);            //LcdOutput func call
        lcd_command(0xC8);           //command to display from C8
        LcdOutput(voltage);          //LcdOutput func call
        lcd_data(0x56);
    }
}
 
void lcdinit()
{
 TRISA = 0x04;    //setting PORT A as input    
 TRISC = 0x00;    //setting PORT C as output
 TRISD = 0x00;    //setting PORT D as output
 ADCON0 = 0x91;   //configuring ADCON0 register for 10010001 , selecting channel AN2, making AD On and frequency
 ADCON1 = 0x82;   //configuring ADCON1 register for 10000010, Selecting correct bit configuration and frequency
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

//LcdOutput function defintion
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
  if(k[4] > 0)                //checking if last number is greater than 0 or not
  {
      n = 0x30 + k[4];      //if yes, storing the last digit in n
      lcd_data(n);          //printing last digit
      n = 0x30 + k[3];      //storing first last digit to n
      lcd_data(n);          //printing first last digit
      n = 0x30 + k[2];      //storing second last digit to n
      lcd_data(n);          //printing second last digit
      n = 0x30 + k[1];      //storing first digit to n
      lcd_data(n);          //printing first digit
  }
  else if (k[3] > 0)        //if not, checking first last digit is greater than 0 or not
  {
      lcd_data(0x20);       //if yes, printing " "
      n = 0x30 + k[3];      //storing the last digit in n
      lcd_data(n);          //printing last digit
      n = 0x30 + k[2];      //storing first last digit to n
      lcd_data(n);          //printing first last digit
      n = 0x30 + k[1];      //storing first digit to n
      lcd_data(n);          //printing first digit
  }
  else if (k[2] > 0)        //if not, checking second last digit is greater than 0 or not
  {
      //if yes,printing 2 spaces "  "
      lcd_data(0x20);       
      lcd_data(0x20);     
      n = 0x30 + k[2];    //storing last digit to n
      lcd_data(n);        //printing last digit
      n = 0x30 + k[1];    //storing first digit to n
      lcd_data(n);        //printing first digit
  }
  else
  {
      //if yes,printing 3 spaces "   "
      lcd_data(0x20);
      lcd_data(0x20);
      lcd_data(0x20);
      n = 0x30 + k[1];    //storing first digit to n
      lcd_data(n);        //printing first digit
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
