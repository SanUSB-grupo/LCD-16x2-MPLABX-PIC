#ifndef __LCD_H
#define __LCD_H

//******Biblioteca LCD SanUSB**************
//  Escreve ate 4 linhas com lcd_escreve    *
//  Controle em 4 pinos                     *
//  tinyurl.com/SanUSB                      *
/****************************************** 

#define LCD_RD7     LATBbits.LATB5      // D7
#define TRIS_RD7    TRISBbits.TRISB5

#define LCD_RD6     LATBbits.LATB4      // D6
#define TRIS_RD6    TRISBbits.TRISB4

#define LCD_RD5     LATBbits.LATB3      // D5
#define TRIS_RD5    TRISBbits.TRISB3

#define LCD_RD4     LATBbits.LATB2      // D4
#define TRIS_RD4    TRISBbits.TRISB2

#define LCD_EN     LATBbits.LATB1       // EN
#define TRIS_EN    TRISBbits.TRISB1

#define LCD_RS     LATBbits.LATB0       // RS
#define TRIS_RS    TRISBbits.TRISB0

  Commandos LCD                      //*/

//******************************************

#define LCD_RD7     LATBbits.LATB3      // D7
#define TRIS_RD7    TRISBbits.TRISB3

#define LCD_RD6     LATBbits.LATB2      // D6
#define TRIS_RD6    TRISBbits.TRISB2

#define LCD_RD5     LATBbits.LATB1      // D5
#define TRIS_RD5    TRISBbits.TRISB1

#define LCD_RD4     LATBbits.LATB0      // D4
#define TRIS_RD4    TRISBbits.TRISB0

#define LCD_EN     LATBbits.LATB4       // EN
#define TRIS_EN    TRISBbits.TRISB4

#define LCD_RS     LATBbits.LATB5       // RS
#define TRIS_RS    TRISBbits.TRISB5

//  Commandos LCD                      //*/

//não usado // #define TRIS_RW  TRISBbits.TRISB2

#define      LCD_FIRST_ROW           128
#define      LCD_SECOND_ROW          192
#define      LCD_THIRD_ROW           148
#define      LCD_FOURTH_ROW          212
#define      LCD_CLEAR               1
#define      LCD_RETURN_HOME         2
#define      LCD_CURSOR_OFF          12
#define      LCD_UNDERLINE_ON        14
#define      LCD_BLINK_CURSOR_ON     15
#define      LCD_MOVE_CURSOR_LEFT    16
#define      LCD_MOVE_CURSOR_RIGHT   20
#define      LCD_TURN_OFF            0
#define      LCD_TURN_ON             8
#define      LCD_SHIFT_LEFT          24
#define      LCD_SHIFT_RIGHT         28


void lcd_ini(void);
void lcd_escreve(unsigned char y, unsigned char x, const rom char *buffer);
void lcd_escreve2(unsigned char y, unsigned char x, char *buffer);
void Lcd_Chr_CP(char data);
void lcd_comando(unsigned char Cmd);

void Delay_5us(void);
void Delay_5500us(void);

void Delay_5us(void){
tempo_us(5);
}

void Delay_5500us(void){ //tempo_ms(5);
tempo_ms(6);
}


void lcd_ini(void){
unsigned char data;

TRIS_RD7 = 0; TRIS_RD6 = 0; TRIS_RD5 = 0; TRIS_RD4 = 0; TRIS_EN = 0; TRIS_RS = 0;
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 0; LCD_RD4 = 0; LCD_EN = 0; LCD_RS = 0;
Delay_5500us(); Delay_5500us(); Delay_5500us();
EEADR =0B11111101; EECON1bits.WREN = 0;
EECON1bits.EEPGD = 0; EECON1bits.CFGS = 0;
EECON1bits.RD = 1; while(EEDATA);
Delay_5500us(); Delay_5500us(); Delay_5500us();
Delay_5500us(); Delay_5500us(); Delay_5500us();

for(data = 1; data < 4; data ++)
{
    LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 1; LCD_EN = 0; LCD_RS = 0;
    LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 1; LCD_EN = 1; LCD_RS = 0;
    Delay_5us();
    LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 1; LCD_EN = 0; LCD_RS = 0;
    Delay_5500us();
}
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 0; LCD_EN = 0; LCD_RS = 0;
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 0; LCD_EN = 1; LCD_RS = 0;
Delay_5us();
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 0; LCD_EN = 0; LCD_RS = 0;
Delay_5500us();

data = 40; lcd_comando(data);
data = 16; lcd_comando(data);
data = 1;  lcd_comando(data);
data = 15; lcd_comando(data);
}


void lcd_escreve(unsigned char y, unsigned char x, const rom char *buffer)
{
unsigned char data;

switch (y)
{
    case 1:
    data = 128 + x;
    break;
    case 2:
    data = 192 + x;
    break;
    case 3:
    data = 148 + x;
    break;
    case 4:
    data = 212 + x;
    break;
    default:
    break;
}

lcd_comando(data);

while(*buffer)              // Write data to LCD up to null
{                
    Lcd_Chr_CP(*buffer);
    buffer++;               // Increment buffer
}
return;
}

void lcd_escreve2(unsigned char y, unsigned char x, char *buffer) //com dados da RAM
{
unsigned char data;
switch (y)
{
    case 1:
    data = 128 + x;
    break;
    case 2:
    data = 192 + x;
    break;
    case 3:
    data = 148 + x;
    break;
    case 4:
    data = 212 + x;
    break;
    default:
    break;
}

lcd_comando(data);

while(*buffer)              // Escreve bytes no LCD até buffer=0
{                
    Lcd_Chr_CP(*buffer);
    buffer++;               // Incrementa buffer
}
return;
}

void Lcd_Chr_CP(char data){
LCD_EN = 0; LCD_RS = 1;
LCD_RD7 = (data & 0b10000000)>>7; LCD_RD6 = (data & 0b01000000)>>6;
LCD_RD5 = (data & 0b00100000)>>5; LCD_RD4 = (data & 0b00010000)>>4;
Delay_5us();Delay_5us();
LCD_EN = 1; Delay_5us(); LCD_EN = 0;
    
LCD_RD7 = (data & 0b00001000)>>3; LCD_RD6 = (data & 0b00000100)>>2;
LCD_RD5 = (data & 0b00000010)>>1; LCD_RD4 = (data & 0b00000001);
Delay_5us();Delay_5us();
LCD_EN = 1; Delay_5us(); LCD_EN = 0;
Delay_5us(); Delay_5500us();
}

void lcd_comando(unsigned char Cmd){
unsigned char data;
data = Cmd;
LCD_EN = 0; LCD_RS = 0;
LCD_RD7 = (data & 0b10000000)>>7; LCD_RD6 = (data & 0b01000000)>>6;
LCD_RD5 = (data & 0b00100000)>>5; LCD_RD4 = (data & 0b00010000)>>4;
Delay_5us();Delay_5us();Delay_5us();
LCD_EN = 1; Delay_5us(); LCD_EN = 0;

LCD_RD7 = (data & 0b00001000)>>3; LCD_RD6 = (data & 0b00000100)>>2;
LCD_RD5 = (data & 0b00000010)>>1; LCD_RD4 = (data & 0b00000001);
Delay_5us();Delay_5us();
LCD_EN = 1; Delay_5us(); LCD_EN = 0;
Delay_5500us();
}

#endif
























