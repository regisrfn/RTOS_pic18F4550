//LCD Functions Developed by electroSome
#include "LCD.h"
#include "delayRTOS.h"
#include <stdbool.h>
#define _XTAL_FREQ 48000000

void Lcd_Port(char c) {
    static char a;
    a = c;
    if (a & 1)
        D4 = 1;
    else
        D4 = 0;

    if (a & 2)
        D5 = 1;
    else
        D5 = 0;

    if (a & 4)
        D6 = 1;
    else
        D6 = 0;

    if (a & 8)
        D7 = 1;
    else
        D7 = 0;
}

void Lcd_Cmd(char c) {
    static char a;
    a = c;
    RS = 0; // => RS = 0
    Lcd_Port(a);
    EN = 1; // => E = 1
    delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear() {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char row, char column) {
    static char temp, z, y,a,b;
    a = row;
    b = column;
    if (a == 1) {
        temp = 0x80U + b - 1U;
        z = temp >> 4;
        y = temp & 0x0FU;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    } else if (a == 2) {
        temp = 0xC0U + b - 1U;
        z = temp >> 4U;
        y = temp & 0x0FU;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}

void Lcd_Init() {
    Lcd_Port(0x00);
    delay_ms(20);
    Lcd_Cmd(0x03);
    delay_ms(5);
    Lcd_Cmd(0x03);
    delay_ms(11);
    Lcd_Cmd(0x03);
    /////////////////////////////////////////////////////
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a) {
    static char temp, y;
    temp = a & 0x0FU;
    y = a & 0xF0U;
    RS = 1; // => RS = 1
    Lcd_Port(y >> 4); //Data transfer
    EN = 1;
    delay_us(40);
    EN = 0;
    Lcd_Port(temp);
    EN = 1;
    delay_us(40);
    EN = 0;
}

void Lcd_Write_String(const char *a) {
    static int i;
    static const char *string;
    string = a;
    
    for (i = 0; string[i] != '\0'; i++)
        Lcd_Write_Char(string[i]);
}

void Lcd_Shift_Right() {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left() {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}


