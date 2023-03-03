/*
 * led.c
 *
 * Created: 2/19/2023 10:55:24 PM
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
#include "led.h"

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
void led_init(led_id_t led_id)
{
	switch (led_id)
	{
		case Red_LED:
			dio_VidConfigChannel(RED_LED_PORT, RED_LED_CHANNEL, OUTPUT);
		break;
		case GREEN_LED:
			dio_VidConfigChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL, OUTPUT);
		break;
		case BLUE_LED:
			dio_VidConfigChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL, OUTPUT);
		break;
		/*case YELLOW_LED:
			dio_VidConfigChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL, OUTPUT);
		break;*/
		default:
			dio_VidConfigChannel(RED_LED_PORT, RED_LED_CHANNEL, OUTPUT);
			dio_VidConfigChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL, OUTPUT);
			dio_VidConfigChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL, OUTPUT);
			//dio_VidConfigChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL, OUTPUT);
		break;
	}
	
}

void led_on(led_id_t led_id )
{
	
		switch (led_id)
		{
			case Red_LED:
				#if(Red_LED_CONNECTION == SOURCE)
					dio_VidWriteChannel(RED_LED_PORT, RED_LED_CHANNEL, STD_HIGH);
				#else
					dio_VidWriteChannel(RED_LED_PORT, RED_LED_CHANNEL, STD_LOW);		
				#endif
			break;
			case GREEN_LED:
				#if	(GREEN_LED_CONNECTION == SOURCE)	
					dio_VidWriteChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL, STD_HIGH);
				#else
					dio_VidWriteChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL, STD_LOW);
				#endif
			break;
			case BLUE_LED:
				#if (BLUE_LED_CONNECTION == SOURCE)
					dio_VidWriteChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL, STD_HIGH);
				#else
					dio_VidWriteChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL, STD_LOW);		
				#endif
			break;
			/*case YELLOW_LED:
				#if (YELLOW_LED_CONNECTION == SOURCE)
					dio_VidWriteChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL, STD_HIGH);
				#else
					dio_VidWriteChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL, STD_LOW);
				#endif
			break;*/
			default:
				dio_VidWriteChannel(RED_LED_PORT, RED_LED_CHANNEL, STD_HIGH);
				dio_VidWriteChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL, STD_HIGH);
				dio_VidWriteChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL, STD_HIGH);
				//dio_VidWriteChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL, STD_HIGH);
			break;
		}
		
}

void led_of(led_id_t led_id )
{ 
		switch (led_id)
		{
			case Red_LED:
				#if(Red_LED_CONNECTION == SOURCE)
					dio_VidWriteChannel(RED_LED_PORT, RED_LED_CHANNEL, STD_LOW);
				#else
					dio_VidWriteChannel(RED_LED_PORT, RED_LED_CHANNEL, STD_HIGH);		
				#endif
			break;
			case GREEN_LED:
				#if	(GREEN_LED_CONNECTION == SOURCE)	
					dio_VidWriteChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL, STD_LOW);
				#else
					dio_VidWriteChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL, STD_HIGH);
				#endif
			break;
			case BLUE_LED:
				#if (BLUE_LED_CONNECTION == SOURCE)
					dio_VidWriteChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL, STD_LOW);
				#else
					dio_VidWriteChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL, STD_HIGH);		
				#endif
			break;
			/*case YELLOW_LED:
				#if (YELLOW_LED_CONNECTION == SOURCE)
					dio_VidWriteChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL, STD_LOW);
				#else
					dio_VidWriteChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL, STD_HIGH);
				#endif
			break;*/
			default:
				dio_VidWriteChannel(RED_LED_PORT, RED_LED_CHANNEL, STD_LOW);
				dio_VidWriteChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL, STD_LOW);
				dio_VidWriteChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL, STD_LOW);
				//dio_VidWriteChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL, STD_LOW);
			break;
		}
}

void led_toggle(led_id_t led_id )
{
	switch (led_id)
		{
			case Red_LED:
				dio_VidFilpChannel(RED_LED_PORT, RED_LED_CHANNEL);
			break;
			case GREEN_LED:
				dio_VidFilpChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL);
			break;
			case BLUE_LED:
				dio_VidFilpChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL);
			break;
			/*case YELLOW_LED:
				dio_VidFlipChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL);
			break;*/
			default:
				dio_VidFilpChannel(RED_LED_PORT, RED_LED_CHANNEL);
				dio_VidFilpChannel(GREEN_LED_PORT, GREEN_LED_CHANNEL);
				dio_VidFilpChannel(BLUE_LED_PORT, BLUE_LED_CHANNEL);
				//dio_VidFlipChannel(YELLOW_LED_PORT, YELLOW_LED_CHANNEL);
			break;
		}
		
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
