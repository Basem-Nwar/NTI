/*
 * led.c
 *
 * Created: 2/22/2023 8:30:05 PM
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
#include "lcd.h"


/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define  NO_CSTOM_CHAR 8
#define NO_CSTOM_CHAR_BYTES 8 
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
u8 customChar[NO_CSTOM_CHAR][NO_CSTOM_CHAR_BYTES]=
{
	{0x0A,0x1F,0x1F,0x1F,0x1F,0x0E,0x04,0x00},	/* Heart symbol	 */
	{0x04,0x1F,0x11,0x11,0x11,0x11,0x11,0x1F},	/* Empty battery */
	{0x04,0x1F,0x11,0x11,0x11,0x11,0x1F,0x1F},	/*	20% battery  */
	{0x04,0x1F,0x11,0x11,0x11,0x1F,0x1F,0x1F},  /*	40% battery  */
	{0x04,0x1F,0x11,0x11,0x1F,0x1F,0x1F,0x1F},	/*	60% battery  */
	{0x04,0x1F,0x11,0x1F,0x1F,0x1F,0x1F,0x1F},	/*	80% battery  */
	{0x04,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F},	/*	100% battery */
	{0x00,0x00,0x01,0x01,0x05,0x05,0x15,0x15},	/*	Mobile Signal*/
};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void LCD_Pins_Init();
void LCD_Pulse_Enable();

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
void LCD_Pins_Init()
{
	dio_VidConfigChannel(LCD_PORT, LCD_RS_PIN, OUTPUT);
	dio_VidConfigChannel(LCD_PORT, LCD_EN_PIN, OUTPUT);
	dio_VidConfigChannel(LCD_PORT, LCD_D4_PIN, OUTPUT);
	dio_VidConfigChannel(LCD_PORT, LCD_D5_PIN, OUTPUT);
	dio_VidConfigChannel(LCD_PORT, LCD_D6_PIN, OUTPUT);
	dio_VidConfigChannel(LCD_PORT, LCD_D7_PIN, OUTPUT);
}
void LCD_Pulse_Enable()
{
	dio_VidWriteChannel(LCD_PORT,LCD_EN_PIN,STD_HIGH);
	_delay_us(1);
	dio_VidWriteChannel(LCD_PORT,LCD_EN_PIN,STD_LOW);
	_delay_us(200);
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Description                                                                         
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void LCD_Clear()
{
	LCD_SendCmd(LCD_CLEAR_HEX);
	_delay_ms(2);
}
void LCD_Init()
{	
	/* LCD Pins Initialization to be output */
	LCD_Pins_Init();
	_delay_ms(40);				//delay after power on 
	
	dio_VidWriteChannel(LCD_PORT,LCD_EN_PIN,STD_LOW);
	
	/* initialize LCD*/
	LCD_SendCmd(LCD_RETURN_HOME_HEX);
	LCD_SendCmd(LCD_FUNCTION_SET_HEX);
	_delay_us(40);
	LCD_SendCmd(LCD_DISPLAY_CURSOR_ON_OFF_HEX);
	_delay_us(40);
	LCD_Clear();
	_delay_ms(3);
	LCD_SendCmd(LCD_ENTRY_MODE_HEX);
	_delay_ms(30);
	
	LCD_InitCustomeChar();
	LCD_GotoRowColumn(0,0);
}

void LCD_SendCmd(u8 cmd)
{
	dio_VidWriteChannel(LCD_PORT,LCD_RS_PIN,STD_LOW);
	
	dio_VidWriteChannel(LCD_PORT,LCD_D4_PIN,CHECK_BIT(cmd,D4));
	dio_VidWriteChannel(LCD_PORT,LCD_D5_PIN,CHECK_BIT(cmd,D5));
	dio_VidWriteChannel(LCD_PORT,LCD_D6_PIN,CHECK_BIT(cmd,D6));
	dio_VidWriteChannel(LCD_PORT,LCD_D7_PIN,CHECK_BIT(cmd,D7));
	
	LCD_Pulse_Enable();
	
	dio_VidWriteChannel(LCD_PORT,LCD_D4_PIN,CHECK_BIT(cmd,D0));
	dio_VidWriteChannel(LCD_PORT,LCD_D5_PIN,CHECK_BIT(cmd,D1));
	dio_VidWriteChannel(LCD_PORT,LCD_D6_PIN,CHECK_BIT(cmd,D2));
	dio_VidWriteChannel(LCD_PORT,LCD_D7_PIN,CHECK_BIT(cmd,D3));
	
	LCD_Pulse_Enable();
}

void LCD_SendData(u8 data)
{
	dio_VidWriteChannel(LCD_PORT,LCD_RS_PIN,STD_HIGH);
	
	dio_VidWriteChannel(LCD_PORT,LCD_D4_PIN,CHECK_BIT(data,D4));
	dio_VidWriteChannel(LCD_PORT,LCD_D5_PIN,CHECK_BIT(data,D5));
	dio_VidWriteChannel(LCD_PORT,LCD_D6_PIN,CHECK_BIT(data,D6));
	dio_VidWriteChannel(LCD_PORT,LCD_D7_PIN,CHECK_BIT(data,D7));
	
	LCD_Pulse_Enable();
	
	dio_VidWriteChannel(LCD_PORT,LCD_D4_PIN,CHECK_BIT(data,D0));
	dio_VidWriteChannel(LCD_PORT,LCD_D5_PIN,CHECK_BIT(data,D1));
	dio_VidWriteChannel(LCD_PORT,LCD_D6_PIN,CHECK_BIT(data,D2));
	dio_VidWriteChannel(LCD_PORT,LCD_D7_PIN,CHECK_BIT(data,D3));
	
	LCD_Pulse_Enable();
	
}

void LCD_DisplayChar(u8 chr)
{
	LCD_SendData(chr);
}

void LCD_DisplayString(u8 *str)
{
	while (*str != '\0')
	{
		LCD_DisplayChar(*str);
		str++;
	}
}

void LCD_GotoRowColumn(u8 row, u8 column)
{
	switch (row)
	{
		case 0:
		/*	Row 0	*/
			LCD_SendCmd(0x80+column);
		break;

		case 1:
		/* Row 1 */
			LCD_SendCmd(0xC0+column);
		break;
	}
}

void LCD_InitCustomeChar(void)
{
	u8 loc_ByteIndex=0;
	u8 loc_CharIndx=0;
	
	for (loc_CharIndx=0;loc_CharIndx<NO_CSTOM_CHAR;loc_CharIndx++)
	{
		LCD_SendCmd(LCD_SET_CGRAM_ADD_HEX +(loc_CharIndx*8));
		for (loc_ByteIndex =0; loc_ByteIndex<NO_CSTOM_CHAR_BYTES;loc_ByteIndex++)
		{
			LCD_DisplayChar(customChar[loc_CharIndx][loc_ByteIndex]);
		}
	}
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
