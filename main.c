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

    TRISBbits.RB0 = 0;
    TRISBbits.RB1 = 0;

    PORTB = 0;

    //inicializacao do LCD
    ADCON1 = 0x0F; //Desabilita todos os canais A/D
    lcd_ini(); //Inicializa LCD 
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
        delay_ms(200);
        putsLCD("\fPIC18F4550\r");
        putsLCD("TASK 2\r");
        delay_ms(200);
        putsLCD("\fTASK 2\r");
        putsLCD("PIC18F4550\r");
        Pulse2 = (unsigned) ~Pulse2;
        test++;
    }
}

void TASK3() {
    initTask(3, 1);
    int test = 255;
    while (1) {
        test++;
        writeStringSerial("TASK 3 IS RUNNNING\r");
    }
}