/*
 * led_cfg.h
 *
 * Created: 2/22/2023 8:30:51 PM
 *  Author: basem
 */ 

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Write File Name>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef _LED_CFG_H_
#define _LED_CFG_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* LCD PORT AND PINS CONNECTOIN */
#define LCD_PORT	DIO_PORTA
#define LCD_RS_PIN	DIO_PIN1
#define LCD_EN_PIN	DIO_PIN2
#define LCD_D4_PIN	DIO_PIN3
#define LCD_D5_PIN	DIO_PIN4
#define LCD_D6_PIN	DIO_PIN5
#define LCD_D7_PIN	DIO_PIN6

/* LCD COMMANDS	 DEFINITIONS */
#define LCD_RETURN_HOME_HEX				0x02
#define LCD_CLEAR_HEX					0X01	
#define LCD_ENTRY_MODE_HEX				0X06
#define LCD_DISPLAY_CURSOR_ON_OFF_HEX	0X0F
#define LCD_FUNCTION_SET_HEX			0X28
#define LCD_SET_CGRAM_ADD_HEX			0X40
#define LCD_SET_DDRAM_ADD_HEX			0X80



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* _LED_CFG_H_	*/

/**********************************************************************************************************************
 *  END OF FILE: FILE_NAME.h
 *********************************************************************************************************************/