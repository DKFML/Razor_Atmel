/**********************************************************************************************************************
File: user_app.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app as a template:
 1. Copy both user_app.c and user_app.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp2" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp2Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp2RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp2Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */

extern u8 G_au8DebugScanfBuffer[];                     /* From debug.c */
extern u8 G_u8DebugScanfCharCount;                     /* From debug.c  */
/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp2_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp2_StateMachine;            /* The state machine function pointer */
static u32 UserApp2_u32Timeout;                      /* Timeout counter used across states */
static u8 au8UserInputBuffer[USER_INPUT_BUFFER_SIZE];  /* Char buffer */

static u8 User_name[] = "A3.YeChenxiao";
static u8 My_name  [] = "YeChenxiao";
static u8 UserApp2_CursorPosition = 0;

  
/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

void BUZZER(void)
{
  static u8 u8notecounter = 0;
  static u16 u16buzzerrate[]  = {586,586,523,586,697,697,783,
  586,586,523,586,523,879,523,
  586,586,523,586,697,783,879,
  879,783,879,783,697,586,
  586,586,523,586,697,697,783,
  586,586,523,586,523,523,879,
  586,586,523,586,697,697,783,
  879,783,879,783,697,586,
  697,658,586,523,523,523,586,879,783,879,
  };
  static u16 u16counter = 0;
  u16counter++;
  if(u16counter == 80)
  {
    u16counter=0;
    PWMAudioSetFrequency(BUZZER1, u16buzzerrate[u8notecounter]);
    PWMAudioOn(BUZZER1);
    if(++u8notecounter == 63)
    {
      u8notecounter=0;
    }
  }
} /* end UserAppSM_Idle() */
void blinkon()
{
  static u16 u16count_for_500 = 0;
  u16count_for_500++;
  if(u16count_for_500==500)
  {
    u16count_for_500 = 0;
    LedToggle(RED);
  }
}

void blinkoff()
{
  LedOff(RED);
}


