#include <xc.h>
#include <p18f4550.h>
#include "CONFIG.h" // Configuration Bit Settings
#include "TASK.h"   // Configuration of RTOS variables
#include "delayRTOS.h"
#include "memoryRTOS.h"
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
    static char *semaphore;
    semaphore = malloc(2);
    semaphore[0] = 1;
    semaphore[1] = 2;
    while (1) {
        //Pulse1 = (unsignd) ~Pulse1;
    }
}

void TASK2() {
    initTask(2, 1);
    static int a;
    while (1) {
        while (1) {
            Lcd_Clear();
            Lcd_Set_Cursor(1, 1);
            Lcd_Write_String("LCD LIBRARY FOR");
            Lcd_Set_Cursor(2, 1);
            Lcd_Write_String("MPLAB XC8");
            delay_ms(1000);
            Lcd_Clear();
            Lcd_Set_Cursor(1, 1);
            Lcd_Write_String("TESTING");
            Lcd_Set_Cursor(2, 1);
            Lcd_Write_String("RTOS");
            delay_ms(1000);
            Lcd_Clear();
            Lcd_Set_Cursor(1, 1);
            Lcd_Write_String("TASK 2 IS RUNNING");

            for (a = 0; a < 17; a++) {
                delay_ms(300);
                Lcd_Shift_Left();
            }

            for (a = 0; a < 17; a++) {
                delay_ms(300);
                Lcd_Shift_Right();
            }

            Lcd_Clear();
            Lcd_Set_Cursor(2, 1);
            Lcd_Write_Char('e');
            Lcd_Write_Char('S');
            delay_ms(1000);
        }
    }
}

void TASK3() {
    initTask(3, 1);
    while (1) {
        writeStringSerial("TASK 3 IS RUNNNING\r");
    }
}