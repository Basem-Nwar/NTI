/*
 * timer1_reg.h
 *
 * Created: 3/8/2023 10:41:36 AM
 *  Author: basem
 */ 


#ifndef TIMER1_REG_H_
#define TIMER1_REG_H_

#define TCCR1A	*((volatile u8 *)(0X4F))
#define COM1A1	7
#define COM1A0	6
#define COM1B1	5
#define COM1B0	4
#define FOC1A	3
#define FOC1B	2
#define WGM11	1
#define WGM10	0

#define TCCR1B	*((volatile u8 *)(0X4E))
#define ICNC1	7
#define ICES1	6
#define WGM13	4
#define WGM12	3
#define CS12	2
#define CS11	1
#define CS10	0

#define TCNT1	*((volatile u16 *)(0X4C))
#define TCNT1H	*((volatile u8 *)(0X4D))
#define TCNT1L	*((volatile u8 *)(0X4C))

#define OCR1A	*((volatile u16 *)(0X4A))
#define OCR1AH	*((volatile u8 *)(0X4B))
#define OCR1AL	*((volatile u8 *)(0X4A))

#define OCR1B	*((volatile u16 *)(0X48))
#define OCR1BH	*((volatile u8 *)(0X49))
#define OCR1BL	*((volatile u8 *)(0X48))

#define ICR1	*((volatile u16 *)(0X46))
#define ICR1H	*((volatile u8 *)(0X47))
#define ICR1L	*((volatile u8 *)(0X46))
	
#define TIMSK	*((volatile u8 *)(0X59))
#define TICIE1	5
#define OCIE1A	4
#define OCIE1B	3
#define TOIE1	2

#define TIFR	*((volatile u8 *)(0X58))
#define ICF1	5
#define OCF1A	4
#define OCF1B	3
#define TOV1	2


#endif /* TIMER1_REG_H_ */