/*
 * keypad.c
 *
 * Created: 2/23/2023 8:05:31 PM
 *  Author: basem
 */ 
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "keypad.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define NO_OF_ROWS 4
#define NO_OF_COLS 4
#define PIN_PORT_SIZE 4
#define Forbidden_VALUE 'k'
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
/* Arrays map ports and pins for rows and cols*/
static u8 Rows_Ports[PIN_PORT_SIZE]={ROW1_PORT,ROW2_PORT,ROW3_PORT,ROW4_PORT};
static u8 Rows_Pins[PIN_PORT_SIZE]={ROW1_PIN,ROW2_PIN,ROW3_PIN,ROW4_PIN};
static u8 Cols_Ports[PIN_PORT_SIZE]={COL1_PORT,COL2_PORT,COL3_PORT,COL4_PORT};
static u8 Cols_pins[PIN_PORT_SIZE]={COL1_PIN,COL2_PIN,COL3_PIN,COL4_PIN};
	
static u8 Key_mapped_char[NO_OF_ROWS][NO_OF_COLS]=
{
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                                                                         
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void Keypad_Init()
{
	/* configure row as output */
	dio_VidConfigChannel(ROW1_PORT,ROW1_PIN,OUTPUT);
	dio_VidConfigChannel(ROW2_PORT,ROW2_PIN,OUTPUT);
	dio_VidConfigChannel(ROW3_PORT,ROW3_PIN,OUTPUT);
	dio_VidConfigChannel(ROW4_PORT,ROW4_PIN,OUTPUT);
	
	/* configure col as input*/
	dio_VidConfigChannel(COL1_PORT,COL1_PIN,INPUT);
	dio_VidConfigChannel(COL2_PORT,COL2_PIN,INPUT);
	dio_VidConfigChannel(COL3_PORT,COL3_PIN,INPUT);
	dio_VidConfigChannel(COL4_PORT,COL4_PIN,INPUT);
	
	/* Pull-up for input pins*/
	dio_vidEnablePullUp(COL1_PORT,COL1_PIN);
	dio_vidEnablePullUp(COL2_PORT,COL2_PIN);
	dio_vidEnablePullUp(COL3_PORT,COL3_PIN);
	dio_vidEnablePullUp(COL4_PORT,COL4_PIN);

	/*	initialize Rows with logic high*/
	dio_VidWriteChannel(ROW1_PORT,ROW1_PIN,STD_HIGH);
	dio_VidWriteChannel(ROW2_PORT,ROW2_PIN,STD_HIGH);
	dio_VidWriteChannel(ROW3_PORT,ROW3_PIN,STD_HIGH);
	dio_VidWriteChannel(ROW4_PORT,ROW4_PIN,STD_HIGH);
	
}

u8 keypad_GetKey()
{
	u8 loc_row=0;
	u8 loc_col=0;
	u8 pressed_char=Forbidden_VALUE;
	
	for (loc_row=0 ; loc_row < PIN_PORT_SIZE; loc_row++)
	{
		//deactivate row 
		dio_VidWriteChannel(Rows_Ports[loc_row],Rows_Pins[loc_row],STD_LOW);	
		for (loc_col=0 ; loc_col < PIN_PORT_SIZE ; loc_col++)
		{
			if(!(dio_LevelReadChannel(Cols_Ports[loc_col],Cols_pins[loc_col])))
			{
				pressed_char = Key_mapped_char[loc_row][loc_col];
				
				// avoid multiple presses
				while(!(dio_LevelReadChannel(Cols_Ports[loc_col],Cols_pins[loc_col])));
				
				/*
				 *
				 */
				_delay_ms(30); // avoid bouncing
				
			}
		}
		
		
		// activate row
		dio_VidWriteChannel(Rows_Ports[loc_row],Rows_Pins[loc_row],STD_HIGH); 	
	}
	return pressed_char;
	
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
