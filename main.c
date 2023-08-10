/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
    #include <legacy/pic16f887_legacy.h>
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdio.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "LCD.h"
#include "globals.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();


    while(1)
    {
        char text[5];
        
        while (!nec_ok);   // wait until NEC code receiver

        nec_ok    = 0;   // reset decoding process
        nec_state = 0;
        TMR1ON    = 0;   // disable Timer1

        uint16_t address = nec_code >> 16;
        uint8_t  command = nec_code >> 8;
        uint8_t  inv_command = nec_code;

        sprintf(text,"%04X",address);
        LCD_Goto(11, 1);   // move cursor to column 11 line 1
        LCD_Print(text);   // print address

        sprintf(text,"%02X",command);
        LCD_Goto(7, 2);    // move cursor to column 7 line 2
        LCD_Print(text);   // print command

        sprintf(text,"%02X",inv_command);
        LCD_Goto(15, 2);    // move cursor to column 15 line 2
        LCD_Print(text);    // print inverted command

        RBIE = 1;    // enable PORTB change interrupt
    }

}

