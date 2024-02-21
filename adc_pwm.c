
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
unsigned char k[10],arr[10]={"POT 1 VAL:"},arr1[10]={"POT 2 VAL:"};
unsigned int lovalue,hivalue,delaycount,i,x,m;
unsigned long voltage,value;

void main()
{ 
    //calling lcdinit functions
    lcdinit();
    while(1)
    {
        lcd_command(0x80);     //command to display from 80
        for(x=0;x<10;x++)
        {
            lcd_data(arr[x]);
        }
        lcd_command(0xC0);    //command to display from C0
        for(x=0;x<10;x++)
        {
            lcd_data(arr1[x]);
        }
        ADCON0 = 0x81;            //initializing for channel AN0
        ADCON0 |= 0x04;           //making the conversion On
        while(ADCON0 & 0x04);     //running while loop until the conversion bit get 0
        lovalue = ADRESL;         //storing the ADRESL register value to lovalue
        hivalue = ADRESH;         //storing the ADRESH register value to hivalue
        value = ((unsigned int) hivalue <<8) + (unsigned int)lovalue;    //adding both the values to get the 10 bit valuE
        lcd_command(0x8A);         //command to display from 8A
        LcdOutput(value);          //LcdOutput func call
        ADCON0 = 0x91;            //initializing for channel AN2
        ADCON0 |= 0x04;           //making the conversion On
        while(ADCON0 & 0x04);     //running while loop until the conversion bit get 0
        lovalue = ADRESL;         //storing the ADRESL register value to lovalue
        hivalue = ADRESH;         //storing the ADRESH register value to hivalue
        value = ((unsigned int) hivalue <<8) + (unsigned int)lovalue;    //adding both the values to get the 10 bit value
        voltage = value*337/1023;    //calibrating the value to 0-337
        lcd_command(0xCA);           //command to display from CA
        LcdOutput(voltage);          //LcdOutput func call
        lcd_data(0x56);              //displaying "V"
        CCPR1L  = (voltage)>>2;      //storing CCPR1L 8 bits after doing right shift of voltage
        CCP1CON = (CCP1CON&0xCF)+((voltage&0x03)<<4);   //logic to store the 5:4 bit of CCP1CON
        __delay_ms(1000);            //delay for 1 sec
    }
}
 
void lcdinit()
{
 TRISA = 0x05;    //setting PORT A as input for RA0 and RA2    
 TRISC = 0x00;    //setting PORT C as output
 TRISD = 0x00;    //setting PORT D as output
 ADCON0 = 0x81;   //configuring ADCON0 register for 10000001 , selecting channel AN0, making AD On and frequency
 ADCON1 = 0x82;   //configuring ADCON1 register for 10000010, Selecting correct bit configuration and frequency, right justified or left justified
 CCP1CON = 0x0C;  //0000 1100 , configuring to PWM mode
 T2CON = 0x06;    //setting prescale value as 1:16 and timer 2 on
 PR2 = 0x5E;      //Setting PR2 value as 94
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
  if( (j == 4) && (k[4] > 0))  //checking if last number is greater than 0 or not and j equal to 4 or not
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
  else if ((j== 3) && (k[3] > 0)) //if not, checking first last digit is greater than 0 or not and j equal to 3 or not
  {
      lcd_data(0x20);       //if yes, printing " "
      n = 0x30 + k[3];      //storing the last digit in n
      lcd_data(n);          //printing last digit
      n = 0x30 + k[2];      //storing first last digit to n
      lcd_data(n);          //printing first last digit
      n = 0x30 + k[1];      //storing first digit to n
      lcd_data(n);          //printing first digit
  }
  else if ((j== 2) && (k[2] > 0)) //if not, checking second last digit is greater than 0 or not and j equal to 2 or not
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
    PORTC &= ~0x08;      //making RS as 0 
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