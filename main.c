#include <xc.h>
#include <p18f4550.h>
#include "CONFIG.h" // Configuration Bit Settings
#include "TASK.h"   // Configuration of RTOS variables
#include "delayRTOS.h"
#include "LCD.h"
#include "EUSART.h"
#define Pulse1 PORTBbits.RB0
#define Pulse2 PORTBbits.RB1
#define Pulse3 PORTBbits.RB2
#define _XTAL_FREQ 48000000


void TASK1();
void TASK2();
void TASK3();

void main(void) {
    unsigned int a;
    TRISD = 0x00;
    TRISE = 0x00;
    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    PORTB = 0;
    // inicializacao do LCD
    ADCON1 = 0x0F; //Desabilita todos os canais A/D
    Lcd_Init();
    UART_Init(9000);

    TASK1();
    TASK2();
    TASK3();
    startRTOS();

}

void TASK1() {
    initTask(1, 1);
    int test = 100;
    while (1) {
        test++;
        //Pulse1 = (unsigned) ~Pulse1;
    }
}

void TASK2() {
    initTask(2, 1);
    int test = 7;
    while (1) {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("LCD Library for");
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String("MPLAB XC8");
        delay_ms(400);
        Pulse1 = (unsigned) ~Pulse1;
        test++;
    }
}

void TASK3() {
    initTask(3, 1);
    int test = 255;
    while (1) {
        test++;
        // writeStringSerial("TASK 3 IS RUNNNING\r");
    }
}