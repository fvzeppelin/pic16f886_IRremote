/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <string.h>
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "system.h"
#include "user.h"
#include "LCD.h"
#include "globals.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
  char text[17];
  
  ANSELH = 0;      // configure all PORTB pins as digital 
  TMR1IF = 0;     // clear Timer1 overflow interrupt flag bit
  RBIF   = 0;     // clear PORTB change interrupt flag bit
  TMR1IE = 1;     // enable Timer1 overflow interrupt
  T1CON  = 0x10;  // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
  INTCON = 0xC8;  // enable global, peripheral and PORTB change interrupts
  IOCB0  = 1;     // enable RB0 pin change interrupt  

  nec_ok = 0;
  nec_state = 0;
 
  __delay_ms(1000);   // wait 1 second
 
  LCD_Begin();       // initialize LCD module
  LCD_Goto(1, 1);    // move cursor to column 1, row 1
  strcpy(text, "Address:0x0000");
  LCD_Print(text);
  LCD_Goto(1, 2);    // move cursor to column 1, row 2
  strcpy(text, "Com:0x00 In:0x00");
  LCD_Print(text);   
}

