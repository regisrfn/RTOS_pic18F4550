
#include <p18cxxx.h>
#include <stdio.h>
#include "EUSART.h"

//Função de inicialização do módulo EUSART

char UART_Init(const long int baudrate) {

    unsigned int x;
    x = (_XTAL_FREQ - baudrate * 64) / (baudrate * 64); //SPBRG for Low Baud Rate
    if (x > 255) //If High Baud Rage Required
    {
        x = (_XTAL_FREQ - baudrate * 16) / (baudrate * 16); //SPBRG for High Baud Rate
        BRGH = 1; //Setting High Baud Rate
    }
    if (x < 256) {
        SPBRG = x; //Writing SPBRG Register
        SYNC = 0; //Setting Asynchronous Mode, ie UART
        SPEN = 1; //Enables Serial Port
        TRISC7 = 1; //As Prescribed in Datasheet
        TRISC6 = 1; //As Prescribed in Datasheet
        CREN = 1; //Enables Continuous Reception
        TXEN = 1; //Enables Transmission
        return 1; //Returns 1 to indicate Successful Completion
    }
    return 0; //Returns 0 to indicate UART initialization failed
}//Função auxiliar para a função printf

void writeCharSerial(char c) {

    static char x;
    x = c;

    while (!TRMT);
    TXREG = x;

}

void writeStringSerial(const char *str) {

    static int i;
    static const char *string;
    string = str;
    
    while(*string){
        writeCharSerial(*string);
        string++;
    }
    
}