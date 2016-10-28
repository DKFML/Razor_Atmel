/**********************************************************************************************************************
File: timer.h                                                                

Description:
Header file for yournewtaskname.c

**********************************************************************************************************************/

#ifndef __TIMER_H
#define __TIMER_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/
typedef enum {TIMER_CHANNEL0 = 0, TIMER_CHANNEL1 = 0x40, TIMER_CHANNEL2 = 0x80} TimerChannelType;


/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/
/* Timer Channel 1 Setup
Note:
PA26 Peripheral B is an open pin avaialble as external clock input TCLK2
PB5 Peripheral A is an open pin available for TIOA1 I/O function
PB6 Peripheral A is an open pin available for TIOB1 I/O function
*/

/* Timer 1 interrupt period (1 tick = 2.67us); max 65535 */
#define TC1_RC_INIT (u32)  0x0000ffff

#define TC1_CCR_INIT (u32) 0x00000002
/*
    31-04 [0] Reserved

    03 [0] Reserved
    02 [0] SWTRG 
    01 [1] CLKDIS 
    00 [0] CLKEN 
*/


#define TC1_CMR_INIT (u32) 0x000cc403
/*
    31 [0] BSWTRG  //I set 0x0404c000 for the register
    30 [0] "
    29 [0] BEEVT 
    28 [0] "

    27 [0] BCPC 
    26 [0] "
    25 [0] BCPB
    24 [0] "

    23 [0] ASWTRG
    22 [0] "
    21 [0] AEEVT
    20 [0] "

    19 [1] ACPC 
    18 [1] "
    17 [0] ACPA
    16 [0] "

    15 [1] WAVE 
    14 [1] WAVSEL 
    13 [0] "
    12 [0] ENETRG 

    11 [0] EEVT 
    10 [1] "
    09 [0] EEVTEDG 
    08 [0] "

    07 [0] CPCDIS 
    06 [0] CPCSTOP 
    05 [0] BURST 
    04 [0] "

    03 [0] CLKI 
    02 [0] TCCLKS 
    01 [1] "
    00 [1] "
*/

#define TC1_IER_INIT (u32)0x00000010
/*
    31 -08 [0] Reserved 

    07 [0] ETRGS RC Load interrupt not enabled
    06 [0] LDRBS RB Load interrupt not enabled
    05 [0] LDRAS RA Load interrupt not enabled
    04 [1] CPCS RC compare interrupt is enabled

    03 [0] CPBS RB compare interrupt not enabled
    02 [0] CPAS RA Compare Interrupt enabled
    01 [0] LOVRS Lover's bit? Load Overrun interrupt not enabled 
    00 [0] COVFS Counter Overflow interrupt not enabled
*/

#define TC1_IDR_INIT (u32)0x000000ef
/*
    31-08 [0] Reserved 

    07 [1] ETRGS RC Load interrupt disabled
    06 [1] LDRBS RB Load interrupt disabled
    05 [1] LDRAS RA Load interrupt disabled
    04 [0] CPCS RC compare interrupt not disabled

    03 [1] CPBS RB compare interrupt disabled
    02 [1] CPAS RA Compare Interrupt not disabled
    01 [1] LOVRS Lover's bit?!? Load Overrun interrupt disabled 
    00 [1] COVFS Counter Overflow interrupt disabled
*/


/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/
void TimerStart(?);//which timer
void TimerStop(?);//which timer


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
void TimerInitialize(void);
void TimerRunActiveState(void);


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
inline void TimerDefaultCallback(void);


/***********************************************************************************************************************
State Machine Declarations
***********************************************************************************************************************/
static void TimerAppSM_Idle(void);    

static void TimerAppSM_Error(void);         
static void TimerAppSM_FailedInit(void);        


#endif /* __TIMER_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
