
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include<p18cxxx.h>

//Protótipos das funções para o LCD
void lcd_ini();
void lcd_cmd(char cmd);
void lcd_envia_byte(char nivel, char dado);
void lcd_pos_xy(char x, char y);
void lcd_escreve(char c);
void putsLCD(const char *str);
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

