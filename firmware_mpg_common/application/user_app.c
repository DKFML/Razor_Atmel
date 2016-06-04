/**********************************************************************************************************************
File: user_app.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app as a template:
 1. Copy both user_app.c and user_app.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp" with "YourNewTaskName"
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
void UserAppInitialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserAppRunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserAppFlags;                       /* Global state flags */


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
Variable names shall start with "UserApp_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp_StateMachine;            /* The state machine function pointer */
static u32 UserApp_u32Timeout;                      /* Timeout counter used across states */
static u8 au8UserInputBuffer[USER_INPUT_BUFFER_SIZE];  /* Char buffer */

static u8 User_name[] = "A3.YeChenxiao";
static u8 My_name  [] = "YeChenxiao";
static u8 UserApp_CursorPosition = 0;
/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserAppInitialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserAppInitialize(void)
{
  
  /*Display my name and which group i am in*/
  LCDCommand(LCD_CLEAR_CMD);
  LCDMessage(LINE1_START_ADDR, User_name);
  
  /*My favorite backlight color*/
  LedOn(LCD_RED);
  LedOn(LCD_BLUE);
  LedOff(LCD_GREEN);
  
  /* All discrete LEDs to off */
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
  for(u8 i = 0; i < USER_INPUT_BUFFER_SIZE; i++)
  {
    au8UserInputBuffer[i] = 1;
  }

  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp_StateMachine = UserAppSM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp_StateMachine = UserAppSM_FailedInit;
  }

} /* end UserAppInitialize() */


/*----------------------------------------------------------------------------------------------------------------------
Function UserAppRunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserAppRunActiveState(void)
{
  UserApp_StateMachine();

} /* end UserAppRunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for a message to be queued */
static void UserAppSM_Idle(void)
{
  static u8 u8NumCharsMessage[] = "\n\rCharacters in buffer:";
  static u8 u8BufferMessage[]   = "\n\rBuffer contents:\n\r";
  static u8 u8EmptyMessage[]    = "\n\rBuffer is empty !\n\r";
  static u8 memfornote[]={0};
  static u8 buffer_for_my_nameletter []={0};
  static u8 u8buffer_for_my_name_letter_count =0 ;
  static u16 countformemfornote =0;
  static u8 *point_to_My_name_letter; 
  static u16 u16count =0;
  static u16 u16count_for_blink_or_buzzer =0;
  u8 u8CharCount;
  u16count_for_blink_or_buzzer++;
  /* Print message with number of characters in scanf buffer */
  if(WasButtonPressed(BUTTON0))
  {
    ButtonAcknowledge(BUTTON0);
    
    DebugPrintf(u8NumCharsMessage);
    DebugPrintNumber(G_u8DebugScanfCharCount);
    DebugLineFeed();
  }
  u16count++;
  if(u16count == 250)
  {
    
    u16count = 0;
    /* Read the buffer and print the contents */
    u8CharCount = DebugScanf(au8UserInputBuffer);
    au8UserInputBuffer[u8CharCount] = '\0';
    
    /* If there is at least one charater write it into array memfornote.(In fact ,whenever there is at most a letter.)*/
    for(u8 i=0;i<u8CharCount;i++)
    {
      memfornote[countformemfornote]=au8UserInputBuffer[i];
      
      //疑问：当用 &memfornote[countformemfornote]代替 &au8UserInputBuffer[i]时，显示会有其他
      LCDMessage(LINE2_START_ADDR+UserApp_CursorPosition, &au8UserInputBuffer[i]);
      
      /*Comparing the letter to my name.*/
      if(au8UserInputBuffer[i] == *point_to_My_name_letter || au8UserInputBuffer[i] +32 == *point_to_My_name_letter || au8UserInputBuffer[i] -32 == *point_to_My_name_letter)
      {
        point_to_My_name_letter++;
        buffer_for_my_nameletter[u8buffer_for_my_name_letter_count]=au8UserInputBuffer[i];
        u8buffer_for_my_name_letter_count ++ ;
        
      }
      countformemfornote++;
      UserApp_CursorPosition++;
      
      /*一行写满后，从头开始写*/
      if(UserApp_CursorPosition == 20)
      {
        UserApp_CursorPosition = 0;
      }
    }
    memfornote[countformemfornote] = NULL;
    buffer_for_my_nameletter[u8buffer_for_my_name_letter_count] = NULL;
  }
  if(WasButtonPressed(BUTTON3))
  {
    ButtonAcknowledge(BUTTON3);
    LCDMessage(LINE2_START_ADDR, buffer_for_my_nameletter);
  }
  /*Weather my name is detected*/
  if(countformemfornote == 11)
  {
    countformemfornote = 0;
    memfornote[0] = NULL;
    u16count_for_blink_or_buzzer=0;
    LedBlink(RED,LED_1HZ);
  }
  if(u16count_for_blink_or_buzzer == 5000)
  {
    LedOff(RED);
  }

} /* end UserAppSM_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserAppSM_Error(void)          
{
  
} /* end UserAppSM_Error() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserAppSM_FailedInit(void)          
{
    
} /* end UserAppSM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
