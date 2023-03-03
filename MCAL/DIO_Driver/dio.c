/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  dio.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "dio.h"

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
* \Syntax          : void dio_config(dio_portId_t port,
									dio_channelId_t channel, dio_direction_t direction)
* \Description     : Configure the direction of I/O channel                                    
*                                                                             
* \Sync\Async      :                                                
* \Reentrancy      :                                              
* \Parameters (in) :	port	->  Mc Port ID
						channel ->  MC channel ID
						direction -> MC channel direction
* \Return value:   : None
*                                                                    
*******************************************************************************/
 void dio_VidConfigChannel(dio_portId_t port,	dio_channelId_t channel, dio_direction_t direction)
 {
	 switch(port)
	 {
		 case DIO_PORTA:
			if (direction == OUTPUT)
			{
				SET_BIT(DIO_DDRA_REG,channel);
			}
			else
			{
				CLEAR_BIT(DIO_DDRA_REG,channel);
			}
			break;
			
		case DIO_PORTB:
			if (direction == OUTPUT)
			{
				SET_BIT(DIO_DDRB_REG,channel);
			}
			else
			{
				CLEAR_BIT(DIO_DDRB_REG,channel);
			}
			break;
		case DIO_PORTC:
			if (direction == OUTPUT)
			{
				SET_BIT(DIO_DDRC_REG,channel);
			}
			else
			{
				CLEAR_BIT(DIO_DDRC_REG,channel);
			}
			break;
		case DIO_PORTD:
			if (direction == OUTPUT)
			{
				SET_BIT(DIO_DDRD_REG,channel);
			}
			else
			{
				CLEAR_BIT(DIO_DDRD_REG,channel);
			}
			break;
	 }
 }

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
void dio_VidWriteChannel(dio_portId_t port,dio_channelId_t channel, dio_level_t level)
{
	switch(port)
	{
		case DIO_PORTA:
			if (level == STD_HIGH)
			{
				SET_BIT(DIO_PORTA_REG,channel);
			}
			else
			{
				CLEAR_BIT(DIO_PORTA_REG,channel);
			}
			break;
		
		case DIO_PORTB:
			if (level == STD_HIGH)
			{
				SET_BIT(DIO_PORTB_REG,channel);
			}
			else
			{
				CLEAR_BIT(DIO_PORTB_REG,channel);
			}
			break;
		case DIO_PORTC:
			if (level == STD_HIGH)
			{
				SET_BIT(DIO_PORTC_REG,channel);
			}
			else
			{
				CLEAR_BIT(DIO_PORTC_REG,channel);
			}
			break;
		case DIO_PORTD:
			if (level == STD_HIGH)
			{
				SET_BIT(DIO_PORTD_REG,channel);
			}
			else
			{
				CLEAR_BIT(DIO_PORTD_REG,channel);
			}
			break;
	}
}
/******************************************************************************
* \Syntax          :void dio_vidWriteChannelGroup
						(dio_portId_t port,u8 value,u8 mask)
* \Description     : this service for writting on group of IO channels                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port  -> MC port ID
					 value -> data value
					 mask  -> data mask
* \Return value:   : None                            
*******************************************************************************/
void dio_vidWriteChannelGroup(dio_portId_t port,u8 value,u8 mask,u8 pos )
{
	switch(port)
	{
		case DIO_PORTA:
			DIO_DDRA_REG &= ~mask;
			DIO_PORTA_REG = (value<<pos) & mask;
		break;
		
		case DIO_PORTB:
			DIO_PORTB_REG &= ~mask;
			DIO_PORTB_REG = (value<<pos) & mask;
		break;
		
		case DIO_PORTC:
			DIO_PORTC_REG &= ~mask;
			DIO_PORTC_REG = (value<<pos) & mask;
		break;
		
		case DIO_PORTD:
			DIO_PORTD_REG &= ~mask;
			DIO_PORTD_REG = (value<<pos) & mask;
		break;
	}
	
}

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
dio_level_t dio_LevelReadChannel(dio_portId_t port,	dio_channelId_t channel)
{	
	dio_level_t channelRead = STD_LOW;
	switch(port)
	{
		case DIO_PORTA:
			channelRead = CHECK_BIT(DIO_PINA_REG,channel);
			break;
		case DIO_PORTB:
			channelRead = CHECK_BIT(DIO_PINB_REG,channel);
			break;
		case DIO_PORTC:
			channelRead = CHECK_BIT(DIO_PINC_REG,channel);
			break;
		case DIO_PORTD:
			channelRead = CHECK_BIT(DIO_PIND_REG,channel);
			break;
	}
	return channelRead;
}
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
void dio_VidFilpChannel(dio_portId_t port,	dio_channelId_t channel)
{
	switch(port)
	{
		case DIO_PORTA:
			FLIP_BIT(DIO_PORTA_REG,channel);
			break;
		case DIO_PORTB:
			FLIP_BIT(DIO_PORTB_REG,channel);
			break;
		case DIO_PORTC:
			FLIP_BIT(DIO_PORTC_REG,channel);
			break;
		case DIO_PORTD:
			FLIP_BIT(DIO_PORTD_REG,channel);
			break;
	}
}

/******************************************************************************
* \Syntax          :void dio_vidEnablePullUp
						(dio_portId_t port, dio_channelId_t channel)
* \Description     : this service for enabling pull up resistor for IO channel                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : port  -> MC port ID
					 channel  -> MC channel ID
* \Return value:   : None                            
*******************************************************************************/
void dio_vidEnablePullUp(dio_portId_t port, dio_channelId_t channel)
{
	/*	show me your code */
	switch (port)
	{
		case DIO_PORTA:
			SET_BIT(DIO_PORTA_REG, channel);
			break;
		case DIO_PORTB:
			SET_BIT(DIO_PORTB_REG, channel);
			break;
		case DIO_PORTC:
			SET_BIT(DIO_PORTC_REG, channel);
			break;
		case DIO_PORTD:
			SET_BIT(DIO_PORTC_REG, channel);
			break;
	}
			
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
