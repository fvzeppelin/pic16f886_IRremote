/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

#ifndef SYSTEM_H
#define	SYSTEM_H

/* Microcontroller MIPs (FCY) */
#define _XTAL_FREQ      8000000L
#define SYS_FREQ        _XTAL_FREQ
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

#endif