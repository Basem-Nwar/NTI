/*
 * timer.c
 *
 * Created: 3/8/2023 10:40:59 AM
 *  Author: basem
 */ 
#include "timer1.h"
#include "dio.h"

volatile fptr TIMER1_ICU_CallBack;

static void TIMER1_OCRA_Mode(OCRA_mode_t OCRA_mode);
static void TIMER1_OCRB_Mode(OCRB_mode_t OCRB_mode);


void TIMER1_Init(timer1_mode_t mode , timer1_prescaller_t prescaller,
OCRA_mode_t OCRA_mode, OCRB_mode_t OCRB_mode)
{
	/*	SELECT TIMER1 MODE	*/
	switch (mode)
	{
		case TIMER1_NORMAL_MODE :
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_FASTPWM_ICR1_TOP_MODE :
			CLEAR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_FASTPWM_OCRA_TOP_MODE :
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
		break;
	}
	
	
	/*	CONFIGURE TIMER1 PRESCALLER*/
	TCCR1B &= 0XF8;			// CLEAR FIRST 3 BITS
	TCCR1B |= prescaller;
	
	/*	CONFIGURE OCRA & OCRB MODE**/
	TIMER1_OCRA_Mode( OCRA_mode );
	TIMER1_OCRB_Mode( OCRB_mode );
	
	/*	clear register and disable interrupts */
	/*	Disable Interrupts*/
	CLEAR_BIT(TIMSK ,TICIE1 );
	CLEAR_BIT(TIMSK ,OCIE1A );
	CLEAR_BIT(TIMSK ,OCIE1B );
	CLEAR_BIT(TIMSK ,TOIE1  );
	/*	CLEAR FLAGS*/
	SET_BIT(TIFR ,ICF1  );
	SET_BIT(TIFR ,OCF1A );
	SET_BIT(TIFR ,OCF1B );
	SET_BIT(TIFR ,TOV1  );
	/*	Clear register*/
	TCNT1 = 0 ;
	OCR1A = 0 ;
	OCR1B = 0 ;
}

void TIMER1_Set_TCNT1Reg(u16 val)
{
	TCNT1= val;
}
void TIMER1_Set_OCR1AReg(u16 val)
{
	OCR1A= val;
}
void TIMER1_Set_OCR1BReg(u16 val)
{
	OCR1B= val;
}
void TIMER1_Set_ICR1Reg(u16 val)
{
	ICR1= val;
}


void TIMER1_Enable_OV_Int(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void TIMER1_Disable_OV_Int(void)
{
	CLEAR_BIT(TIMSK,TOIE1);
}


void TIMER1_Enable_OCA_Int(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void TIMER1_Disable_OCA_Int(void)
{
	CLEAR_BIT(TIMSK,OCIE1A);
}


void TIMER1_Enable_OCB_Int(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void TIMER1_Disable_OCB_Int(void)
{
	CLEAR_BIT(TIMSK,OCIE1B);
}


void TIMER1_Enable_ICU_Int(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void TIMER1_Disable_ICU_Int(void)
{
	CLEAR_BIT(TIMSK,TICIE1);
}

void TIMER1_ICU_Edge(ICU_mode_t edge)
{
	switch(edge)
	{
		case ICU_FALLING_EDGE:
			CLEAR_BIT(TCCR1B,ICES1);
		break;
		case ICU_RISING_EDGE:
			SET_BIT(TCCR1B,ICES1);
		break;
	}
}

void TIMER1_Enable_ICU_NoiseCanceler(void)
{
	SET_BIT(TCCR1B,ICNC1);
}
void TIMER1_Disable_ICU_NoiseCanceler(void)
{
	CLEAR_BIT(TCCR1B,ICNC1);
}



void TIMER1_Set_ICU_CallBack(fptr ptr )
{
	TIMER1_ICU_CallBack = ptr;
}

void __vector_6(void) __attribute__((signal , used));
void __vector_6(void)
{
	TIMER1_ICU_CallBack();
}

















static void TIMER1_OCRA_Mode(OCRA_mode_t OCRA_mode)
{
	//configure OCRB as output;
	dio_VidConfigChannel(DIO_PORTD,DIO_PIN5,OUTPUT);
	switch(OCRA_mode)
	{
		case OCRA_DISCONNECTED:
			CLEAR_BIT(TCCR1A,COM1A0);
			CLEAR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE :
			SET_BIT(TCCR1A,COM1A0);
			CLEAR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
			SET_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
		break;
		case OCRA_INVERTING:
			SET_BIT(TCCR1A,COM1A0);
			SET_BIT(TCCR1A,COM1A1);
		break;
	}
}
static void TIMER1_OCRB_Mode(OCRB_mode_t OCRB_mode)
{
	//configure OCRB as output;
	dio_VidConfigChannel(DIO_PORTD,DIO_PIN4,OUTPUT);
	switch(OCRB_mode)
	{
		case OCRB_DISCONNECTED:
			CLEAR_BIT(TCCR1A,COM1B0);
			CLEAR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE :
			SET_BIT(TCCR1A,COM1B0);
			CLEAR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
			SET_BIT(TCCR1A,COM1B1);
			CLEAR_BIT(TCCR1A,COM1B0);
		break;
		case OCRB_INVERTING:
			SET_BIT(TCCR1A,COM1B0);
			SET_BIT(TCCR1A,COM1B1);
		break;
	}
}
