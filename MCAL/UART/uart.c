/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  uart.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "uart.h"


const u16 BaudRateArray[TOTAL_SPEED_MODE][TOTAL_CPU_F][TOTAL_BAUD_RATE]=
		 {
			 {
				 {103, 51, 25, 16, 12,  8},{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34}
			 },
			 {
				 {207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34},{832,416,207,138,103, 68}
			 }
		  };

void UART_Init(void)
{
	u8 UCSRC_var=0;
	u16 UBRR_var=0;
	
	#if (SPEED_MODE == NORMAL_SPEED)
		CLEAR_BIT(UCSRA,U2X);
	#elif (SPEED_MODE == DOUBLE_SPEED)
		SET_BIT(UCSRA,U2X);
	#endif	
	
	SET_BIT(UCSRC_var,URSEL);
	
	#if		(DATE_SIZE == _5_DATA_BITS)
		CLEAR_BIT(UCSRB,UCSZ2);
		CLEAR_BIT(UCSRC_var,UCSZ0);
		CLEAR_BIT(UCSRC_var,UCSZ1);
	#elif	(DATE_SIZE == _6_DATA_BITS)
		CLEAR_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC_var,UCSZ0);
		CLEAR_BIT(UCSRC_var,UCSZ1);
	#elif	(DATE_SIZE == _7_DATA_BITS)
		CLEAR_BIT(UCSRB,UCSZ2);
		CLEAR_BIT(UCSRC_var,UCSZ0);
		SET_BIT(UCSRC_var,UCSZ1);
	#elif	(DATE_SIZE == _8_DATA_BITS)
		CLEAR_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC_var,UCSZ0);
		SET_BIT(UCSRC_var,UCSZ1);
	#elif	(DATE_SIZE == _9_DATA_BITS)
		SET_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRC_var,UCSZ0);
		SET_BIT(UCSRC_var,UCSZ1);
	#endif
	
	#if (SYNCH_MODE == ASYNCH)
		CLEAR_BIT(UCSRC_var,UMSEL);
	#elif	(SYNCH_MODE == SYNCH)
		SET_BIT(UCSRC_var,UMSEL);
	#endif
	
	#if (PARITY_MODE == DISABLE)
		CLEAR_BIT(UCSRC_var,UPM0);
		CLEAR_BIT(UCSRC_var,UPM1);
	#elif (PARITY_MODE == EVEN_PARITY)
		CLEAR_BIT(UCSRC_var,UPM0);
		SET_BIT(UCSRC_var,UPM1);
	#elif (PARITY_MODE == ODD_PARITY)
		SET_BIT(UCSRC_var,UPM0);
		SET_BIT(UCSRC_var,UPM1);
	#endif
	
	#if (STOP_BIT_MODE == ONE_STOP_BITS)
		CLEAR_BIT(UCSRC_var,USBS);
	#elif (STOP_BIT_MODE == ONE_STOP_BITS)
		SET_BIT(UCSRC_var,USBS);
	#endif
	
	UCSRC =	UCSRC_var;
	
	UBRR_var= BaudRateArray[SPEED_MODE][CPU_F][BAUD_RATE];
	UBRRH = (u8) (UBRR_var>>8);
	UBRRL = (u8) UBRR_var;
			
}

void UART_SendByte(u8 byte)
{
	while(!CHECK_BIT(UCSRA,UDRE));
	UDR= byte;
}


void UART_SendString(u8 *Str)
{
	u16 index =0 ;
	while (Str[index] != '\0')
	{
		UART_SendByte(Str[index]);
		index++ ;
	}
	UART_SendByte('\0');
}

u8 UART_ReceiveByte(void)
{
	while(!CHECK_BIT(UCSRA,RXC));
	return UDR;
}

void UART_ReceiveString(u8 *Str)
{
	u16 index =0;
	Str[index]= UART_ReceiveByte();
	while ( (Str[index]!= '\0') && (Str[index] != 0x0D))
	{
		index++;
		Str[index]= UART_ReceiveByte();
	}
	Str[index]= '\0';
}


void UART_Transmitter_Enable(void)
{
	SET_BIT(UCSRB,TXEN);
}
void UART_Receiver_Enable(void)
{
	SET_BIT(UCSRB,RXEN);
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
