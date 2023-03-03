/****************************************************************/
/*   Author             :    Ahmed Atia Atia 				    */
/*	 Date 				:    2 May 2019 						*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:    contain the Memory mapped of		*/	
/*							 [MCUCR,MCUCSR,GICR,GIFR] Registers */
/****************************************************************/


/****************************************************************/
/* Description   : Guard to protect this File from include more */
/*                 than one time .                              */
/****************************************************************/

#ifndef _ADC_PRIV_H
#define _ADC_PRIV_H


/****************************************************************/	
/** !comment : From Data Sheet :  Memory mapped of ADCSRA    	*/
/**			   Register	is  0X26						    	*/
/****************************************************************/
/**			   ADCSRA : MCU Control Register contains control	*/
/** 		   bits for interrupt sense control and general 	*/
/**            MCU functions.							    	*/
/****************************************************************/

#define ADCSRA		*((volatile u8 * ) (0X26))
#define ADPR0	0
#define ADPS1	1
#define ADPS2	2
#define ADIE	3
#define ADIF	4
#define ADATE	5
#define ADSC	6
#define ADEN	7


/****************************************************************/	
/** !comment : From Data Sheet :  Memory mapped of MCUCSR   	*/
/**			   Register	is  0X54.								*/
/****************************************************************/
/**			   MCUCSR : MCU Control and Status Register			*/
/****************************************************************/

#define ADMUX       *((volatile u8 * ) (0X27))
#define MUX0	0
#define MUX1	1
#define MUX2	2
#define MUX3	3
#define MUX4	4
#define	ADLAR	5
#define REFS0	6
#define REFS1	7


/****************************************************************/	
/** !comment : From Data Sheet :  Memory mapped of GICR     	*/
/**			   Register	is  0X5B.								*/
/****************************************************************/
/**			   GICR : General Interrupt Control Register		*/
/****************************************************************/

#define ADCL        *((volatile u8 * ) (0X24))

#define ADC		    *((volatile u16 * ) (0X24))
/****************************************************************/	
/** !comment : From Data Sheet :  Memory mapped of GIFR     	*/
/**			   Register	is  0X5A.						    	*/
/****************************************************************/
/**			   GIFR : General Interrupt Flag Register			*/
/****************************************************************/

#define ADCH        *((volatile u8 * ) (0X25))

#define SFIOR       *((volatile u8 * ) (0X50))
#define ADTS0	5
#define ADTS1	6
#define ADTS2	7



#endif	/**!comment : End of the guard [_ADC_PRIV_H]		   **/