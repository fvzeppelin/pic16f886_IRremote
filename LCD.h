/* 
 * File:   LCD.h
 * Author: fvzeppelin
 *
 * Created on 10. August 2023, 10:49
 */

#ifndef LCD_H
#define	LCD_H

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
    #include <legacy/pic16f887_legacy.h>
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#pragma warning disable 373

//LCD module connections
#define LCD_RS       RC0
#define LCD_EN       RC1
#define LCD_D4       RC2
#define LCD_D5       RC3
#define LCD_D6       RC4
#define LCD_D7       RC5
#define LCD_RS_DIR   TRISC0
#define LCD_EN_DIR   TRISC1
#define LCD_D4_DIR   TRISC2
#define LCD_D5_DIR   TRISC3
#define LCD_D6_DIR   TRISC4
#define LCD_D7_DIR   TRISC5
//End LCD module connections

#define LCD_FIRST_ROW          0x80
#define LCD_SECOND_ROW         0xC0
#define LCD_THIRD_ROW          0x94
#define LCD_FOURTH_ROW         0xD4
#define LCD_CLEAR              0x01
#define LCD_RETURN_HOME        0x02
#define LCD_ENTRY_MODE_SET     0x04
#define LCD_CURSOR_OFF         0x0C
#define LCD_UNDERLINE_ON       0x0E
#define LCD_BLINK_CURSOR_ON    0x0F
#define LCD_MOVE_CURSOR_LEFT   0x10
#define LCD_MOVE_CURSOR_RIGHT  0x14
#define LCD_TURN_ON            0x0C
#define LCD_TURN_OFF           0x08
#define LCD_SHIFT_LEFT         0x18
#define LCD_SHIFT_RIGHT        0x1E

#ifndef LCD_TYPE
   #define LCD_TYPE 2           // 0=5x7, 1=5x10, 2=2 lines
#endif

__bit RS;

void LCD_Write_Nibble(uint8_t n);
void LCD_Cmd(uint8_t Command);
void LCD_Goto(uint8_t col, uint8_t row);
void LCD_PutC(char LCD_Char);
void LCD_Print(char* LCD_Str);
void LCD_Begin();

#endif	/* LCD_H */

