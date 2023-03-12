/*
 * timer.c
 *
 * Created: 3/4/2023 10:48:30 PM
 *  Author: basem
 */ 
#include "timer0.h"
#include "GIE.h"
#include "dio.h"

volatile fptr TIMER0_OV_CallBack;
volatile fptr TIMER0_CTC_CallBack;


void TIMER0_Init(timer0_mode_t mode , timer0_prescaller_t prescaller)
{
	/*	SELECT TIMER0 MODE	*/
	switch (mode)
	{
		case TIMER0_NORMAL_MODE :
			CLEAR_BIT(TCCR0,WGM00);
			CLEAR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASE_CORRECT_MODE :
			SET_BIT(TCCR0,WGM00);
			CLEAR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE :
			SET_BIT(TCCR0,WGM01);
			CLEAR_BIT(TCCR0,WGM00);
		break;
		case TIMER0_FAST_PWM_MODE :
			SET_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);
		break;
	}
	
	/*	CONFIGURE TIMER0 PRESCALLER*/
		TCCR0 &= 0XF8;			// CLEAR FIRST 3 BITS
		TCCR0 |= prescaller; 
	
	/*	clear register and disable interrupts */
	/*Disable Interrupts*/
	CLEAR_BIT(TIMSK , TOIE0);
	CLEAR_BIT(TIMSK , OCIE0);
	/*CLEAR FLAGS*/
	SET_BIT(TIFR , TOV0);
	SET_BIT(TIFR , OCF0);
	/*Clear register*/
	TCNT0 = 0 ;
	OCR0 = 0 ;
}

void TIMER0_OC0Mode(oc0_mode_t mode)
{
	//configure OC0 as output;
	dio_VidConfigChannel(DIO_PORTB,DIO_PIN3,OUTPUT);
	switch(mode)
	{
		case DISCONNECTED_OC0:
			CLEAR_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);
		break;
		case TOGGLE_OC0 :
			SET_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);
		break;
		case NON_INVERTING_OC0:
			SET_BIT(TCCR0,COM01);
			CLEAR_BIT(TCCR0,COM00);
		break;
		case INVERTING_OC0:
			SET_BIT(TCCR0,COM00);
			SET_BIT(TCCR0,COM01);
		break;
	}
}

void TIMER0_EnableOVInt(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_DisableOVInt(void)
{
	CLEAR_BIT(TIMSK,TOIE0);
}

void TIMER0_EnableCTCInt(void)
{
	SET_BIT(TIMSK,OCIE0);
}
void TIMER0_DisableCTCInt(void)
{
	CLEAR_BIT(TIMSK,OCIE0);
}

void TIMER0_SetTimerReg(u8 val)
{
	TCNT0= val;
}
void TIMER0_SetCompareVal(u8 val)
{
	OCR0=val;
}


void TIMER0_SetOVCallBack(fptr ptr )
{
	TIMER0_OV_CallBack = ptr;
}
void TIMER0_SetCTCCallBack(fptr ptr )
{
	TIMER0_CTC_CallBack = ptr;
}

void __vector_11(void) __attribute__((signal , used));
void __vector_11(void)
{
	
	TIMER0_OV_CallBack();
}

void __vector_10(void) __attribute__((signal , used));
void __vector_10(void)
{
	
	TIMER0_CTC_CallBack();
}