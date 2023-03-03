/*
 * button.c
 *
 * Created: 2/21/2023 8:42:03 PM
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
#include "button.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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
void button_init(button_id_t button_id)
{
	switch (button_id)
	{
		case BUTTON1:
			dio_VidConfigChannel(BUTTON1_PORT,BUTTON1_PIN,INPUT);
		break;
		case BUTTON2:
			dio_VidConfigChannel(BUTTON2_PORT,BUTTON2_PIN,INPUT);
		break;
		case BUTTON3:
			dio_VidConfigChannel(BUTTON3_PORT,BUTTON3_PIN,INPUT);
		break;
		case BUTTON4:
			dio_VidConfigChannel(BUTTON4_PORT,BUTTON4_PIN,INPUT);
		break;
		default:
			dio_VidConfigChannel(BUTTON1_PORT,BUTTON1_PIN,INPUT);
			dio_VidConfigChannel(BUTTON2_PORT,BUTTON2_PIN,INPUT);
			dio_VidConfigChannel(BUTTON3_PORT,BUTTON3_PIN,INPUT);
			dio_VidConfigChannel(BUTTON4_PORT,BUTTON4_PIN,INPUT);
		break;
	}
}

button_status_t button_readStatus(button_id_t button_id)
{		
		button_status_t button_satus = NOT_PRESSED;
		switch(button_id)
		{
			case BUTTON1:
				#if (BUTTON1_CONNECTION == PULL_UP)
					button_satus=(dio_LevelReadChannel(BUTTON1_PORT,BUTTON1_PIN)== STD_LOW)? PRESSED: NOT_PRESSED;
				#else
					button_satus=(dio_LevelReadChannel(BUTTON1_PORT,BUTTON1_PIN)== STD_HIGH)? PRESSED: NOT_PRESSED;
				#endif
			break;
			
			case BUTTON2:
				#if (BUTTON2_CONNECTION == PULL_UP)
					button_satus=(dio_LevelReadChannel(BUTTON2_PORT,BUTTON2_PIN)== STD_LOW)? PRESSED: NOT_PRESSED;
				#else
					button_satus=(dio_LevelReadChannel(BUTTON2_PORT,BUTTON2_PIN)== STD_HIGH)? PRESSED: NOT_PRESSED;
				#endif
			break;
			
			case BUTTON3:
				#if (BUTTON3_CONNECTION == PULL_UP)
					button_satus=(dio_LevelReadChannel(BUTTON3_PORT,BUTTON3_PIN)== STD_LOW)? PRESSED: NOT_PRESSED;
				#else
					button_satus=(dio_LevelReadChannel(BUTTON3_PORT,BUTTON3_PIN)== STD_HIGH)? PRESSED: NOT_PRESSED;
				#endif
			break;
			
			case BUTTON4:
				#if (BUTTON4_CONNECTION == PULL_UP)
					button_satus=(dio_LevelReadChannel(BUTTON4_PORT,BUTTON4_PIN)== STD_LOW)? PRESSED: NOT_PRESSED;
				#else
					button_satus=(dio_LevelReadChannel(BUTTON4_PORT,BUTTON4_PIN)== STD_HIGH)? PRESSED: NOT_PRESSED;
				#endif
			break;
		}
	return button_satus;
}


/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
