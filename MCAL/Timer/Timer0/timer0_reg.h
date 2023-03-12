/*
 * timer_reg.h
 *
 * Created: 3/4/2023 10:49:28 PM
 *  Author: basem
 */ 


#ifndef TIMER_REG_H_
#define TIMER_REG_H_

#define TCCR0	*((volatile u8 *)(0X53))
#define FOC0	7 
#define WGM00	6
#define COM01	5
#define COM00	4
#define WGM01	3
#define CS02	2
#define CS01	1
#define CS00	0


#define TCNT0	*((volatile u8 *)(0X52))
#define OCR0	*((volatile u8 *)(0X5C))

#define TIMSK	*((volatile u8 *)(0X59))
#define OCIE0	1
#define TOIE0	0

#define TIFR	*((volatile u8 *)(0X58))
#define OCF0	1
#define TOV0	0




#endif /* TIMER_REG_H_ */