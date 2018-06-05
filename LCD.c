#include "LCD.h"
#include "delayRTOS.h"

void lcd_ini() {
    //Inc�cio da fun��o lcd_ini()
    static char i; //Vari�vel de controle para envio dos comandos
    TRISD = 0b00000000; //Todos os pinos da porta D configurados como sa�da
    TRISEbits.TRISE1 = 0; //Pino 1 da porta E configurado como sa�da
    TRISEbits.TRISE0 = 0; //Pino 0 da porta E configurado como sa�da
    PORTD = 0b00000000; //Toda porta D em n�vel l�gico 0
    PORTEbits.RE0 = 0; //Pino 0 da porta E em n�vel 0
    PORTEbits.RE1 = 0; //Pino 1 da porta E em n�vel 0
    delay_ms(15); //Atraso de 15ms
    //Envia o comando 0x30 ao LCD por 3 vezes, em intervalos de 5ms
    for (i = 0; i <= 2; i++) {
        lcd_cmd(0x30);
        delay_ms(5);
    }
    lcd_cmd(0x38); //Comunica��o em 8 bits, display de 2 linhas e matriz 7X5
    __delay_us(40); //Atraso de 40us
    lcd_cmd(0x01); //Limpa a mem�ria do LCD
    delay_ms(2); //Atraso de 2ms
    lcd_cmd(0x0C); //Liga o display sem cursor
    __delay_us(40); //Atraso de 40us
    lcd_cmd(0x06); //Deslocamento do cursor � direita ap�s um novo caractere
    __delay_us(40); //Atraso de 40us
} //Final da fun��o lcd_ini()

void lcd_cmd(char c) { //In�cio da fun��o lcd_cmd

    static char cmd;
    cmd = c;
    PORTD = cmd; //Coloca na porta D o valor correspondente � vari�vel cmd
    PORTEbits.RE1 = 1; //Coloca o pino 1 da porta E (EN) em 1
    PORTEbits.RE1 = 0; //Coloca o pino 1 da porta E (EN) em 0
} //Final da fun��o lcd_cmd

void lcd_envia_byte(char nivel, char dado) { //In�cio da fun��o lcd_envia_byte()

    static char data, level;

    data = dado;
    level = nivel;

    PORTEbits.RE0 = level; //Habilita comando ou escrita para o LCD
    __delay_us(100); //Atraso de 100us
    PORTEbits.RE1 = 0; //Coloca o pino 1 da porta E (EN) em 0
    lcd_cmd(data); //chama a fun��o lcd_cmd com o par�metro 'dado'
}

void lcd_pos_xy(char x, char y) //Fun��o de posicionamento do cursor			
{
    static char endereco, line; //Vari�vel de informa��o para o endere�o do cursor

    line = y;

    if (line != 1) //Se o valor de y for 2
        endereco = 0xC0; //ent�o endereco vai ser igual a 0xC0 (endere�o da segunda linha)
    else //Sen�o
        endereco = 0x80; //endere�o vai ser igual a 0x80 (endere�o da primeira linha) 
    endereco += (char) (x - 1); //Aqui decrementa o valor da vari�vel x e o resultado � somado com
    //a vari�vel endere�o...
    lcd_envia_byte(0, endereco); //Chama a fun��o lcd_envia_byte, com o valor 0, informando para
    //o LCD que ser� enviado um dado e o dado est� contido na
    //vari�vel endere�o...		
}

void lcd_escreve(char charLCD) //Fun��o para envio dos caracteres e/ou dados para o LCD
{
    static char c;
    c = charLCD;
    switch (c) //comando switch com a vari�vel c
    {
        case '\f': lcd_envia_byte(0, 1); //Caso c seja ?\f?, o dado 1 ser� enviado ao LCD para 
            //limpar todo o seu conte�do.
            delay_ms(2); //Atraso de 2 ms
            break; //Comando break, terminou o processo acima, j� n�o testa 
            //nenhum outro caso... 
        case '\n': //Caso c seja ?\n?
        case '\r': lcd_pos_xy(1, 2); //ou ?\r?, muda o cursor para a segunda linha do LCD
            break; //Comando break
        case '\b': lcd_envia_byte(0, 0x10); //Caso c seja ?\b? ent�o desloca o cursor para a esquerda
            break; //Comando break
        default: lcd_envia_byte(1, c); //caso seja um caractere qualquer, ent�o este ser� escrito no 
            //LCD pela fun��o lcd_envia_byte?
            break; //Comando break
    }
}

void putsLCD(const char *str) {


    static const char *string;

    string = str;

    while (*string) {
        lcd_escreve(*string);
        string++;
    }


}
