/*
 * timer_types.h
 *
 * Created: 3/4/2023 10:49:51 PM
 *  Author: basem
 */ 


#ifndef TIMER_TYPES_H_
#define TIMER_TYPES_H_

typedef enum
{
	TIMER0_NORMAL_MODE,
	TIMER0_PHASE_CORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FAST_PWM_MODE
	}timer0_mode_t;
	
typedef enum 
{
	TIMER0_STOP = 0,
	TIMER0_PRESCALLER_1,
	TIMER0_PRESCALLER_8,
	TIMER0_PRESCALLER_64,
	TIMER0_PRESCALLER_256,
	TIMER0_PRESCALLER_1024,
	TIMER0_FALLING_EDGE,
	TIMER0_RISING_EDGE
	}timer0_prescaller_t;
	
typedef enum
{
	DISCONNECTED_OC0=0,
	TOGGLE_OC0,
	NON_INVERTING_OC0,
	INVERTING_OC0
	}oc0_mode_t;



#endif /* TIMER_TYPES_H_ */