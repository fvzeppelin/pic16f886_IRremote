/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "globals.h"

#pragma warning disable 373

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

// interrupt ISRs
void __interrupt() ISR(void)
{
/*************** start external interrupt ISR ***************/
  if (RBIF && (RB0 || !RB0))   // PORTB change ISR (& clear mismatch condition)
  {
    RBIF = 0;   // clear PORTB interrupt flag bit
    if(nec_state != 0)
    {
      timer_value = (TMR1H << 8) | TMR1L;  // store Timer1 value
      TMR1H = TMR1L = 0;     // reset Timer1
    }
 
    switch(nec_state)
    {
     case 0 :              // start receiving IR data (we're at the beginning of 9ms pulse)
       TMR1H = TMR1L = 0;  // reset Timer1
       TMR1ON = 1;         // enable Timer1
       nec_state = 1;      // next state: end of 9ms pulse (start of 4.5ms space)
       bit_n = 0;
       break;
 
     case 1 :                                       // End of 9ms pulse
       if((timer_value > 9500) || (timer_value < 8500))
       { // invalid interval ==> stop decoding and reset
         nec_state = 0;  // reset decoding process
         TMR1ON = 0;     // disable Timer1
       }
       else
         nec_state = 2;  // next state: end of 4.5ms space (start of 562탎 pulse)
       break;
 
     case 2 :                                       // End of 4.5ms space
       if((timer_value > 5000) || (timer_value < 4000))
       { // invalid interval ==> stop decoding and reset
         nec_state = 0;  // reset decoding process
         TMR1ON = 0;     // disable Timer1
       }
       else
         nec_state = 3; // next state: end of 562탎 pulse (start of 562탎 or 1687탎 space)
       break;
 
     case 3 :    // End of 562탎 pulse
       if((timer_value > 700) || (timer_value < 400))
       { // invalid interval ==> stop decoding and reset
         TMR1ON = 0;     // disable Timer1
         nec_state = 0;  // reset decoding process
       }
       else
         nec_state = 4;  // next state: end of 562탎 or 1687탎 space
       break;
 
       case 4 :
       if((timer_value > 1800) || (timer_value < 400))
       { // invalid interval ==> stop decoding and reset
         TMR1ON = 0;     // disable Timer1
         nec_state = 0;  // reset decoding process
       }
 
       else
       {
         if( timer_value > 1000)  // if space width > 1ms (short space)
           nec_code |=   (uint32_t)1 << (31 - bit_n);   // write 1 to bit (31 - bit_n)
 
         else    // if space width < 1ms (long space)
           nec_code &= ~((uint32_t)1 << (31 - bit_n));  // write 0 to bit (31 - bit_n)
         bit_n++;
 
         if(bit_n > 31)
         {
           nec_ok = 1;   // decoding process OK
           RBIE = 0;     // disable PORTB change interrupt 
         }
 
         else
           nec_state = 3;  // next state: end of 562탎 pulse (start of 562탎 or 1687탎 space)
         
         break;
       }  // end " else "
       
    }  // end " switch(nec_state) "
 
  }  // end " if (RBIF && (RB0 || !RB0)) "
/*************** end external interrupt ISR ***************/
 
/*************** start Timer1 ISR ***************/
  if (TMR1IF)         // Timer1 ISR
  {
    TMR1IF    = 0;   // clear Timer1 overflow flag bit
    nec_state = 0;   // reset decoding process
    TMR1ON    = 0;   // disable Timer1
  }
/*************** end Timer1 ISR ***************/
 
}
#endif


