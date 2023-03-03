/************************************************************/
/* 	Author 	 	 : Ahmed Atia Atia                          */
/* 	Date   		 : 2 May 2019	                            */
/* 	Version 	 : 1V 									    */
/* 	Description	 : prog.c for ADC		                    */
/************************************************************/


/****************************************************************/
/*********************** STD LIB DIRECTIVES *********************/
/****************************************************************/

#include "std_types.h"
#include "bit_math.h"


/****************************************************************/
/*********************** Component DIRECTIVES *******************/
/****************************************************************/

#include "ADC_int.h"
#include "ADC_config.h"
#include "ADC_private.h" 



static volatile fptr ADC_HandlerFptr = NULLPTR;

/****************************************************************/
/*********************** Function Implementation  ***************/
/****************************************************************/


/****************************************************************/
/* Description    :  This function used to initialize ADC 	    */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/

void ADC_voidInit (void)
{
	/* End ( if ) condition for Macros */	
	/*	--------------------------	*/
	#if(VOLTAGE_REFERENCE == AVCC)
		SET_BIT(ADMUX,REFS0);		
		CLEAR_BIT(ADMUX,REFS1);		
	#elif (VOLTAGE_REFERENCE == AREF)
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
	#elif (VOLTAGE_REFERENCE == INTERNAL)
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
	#endif
	/*	---------------------------	*/
	#if (ADJUSTMENT == LEFT_ADJUSTMENT)
		SET_BIT(ADMUX, ADLAR );
	#elif (ADJUSTMENT == RIGHT_ADJUSTMENT)
		CLEAR_BIT(ADMUX, ADLAR );
	#endif	
	/*	---------------------------	*/
	/*	DISABLE ADC				*/
	CLEAR_BIT(ADCSRA, ADEN);
	/*	DISABLE ADC INTERRUPT	*/
	CLEAR_BIT(ADCSRA, ADIE);
	/*	DISABLE AUTO TRIGGER	*/
	CLEAR_BIT( ADCSRA , ADATE );
	/*	CLEAR INTERRUPT FLAG	*/
	SET_BIT( ADCSRA , ADIF );
	
}


/****************************************************************/
/* Description    : This function used to Enable ADC			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidEnable()
{
	
	SET_BIT( ADCSRA , ADEN );
	
}

/****************************************************************/
/* Description    : This function used to Enable ADC Interrput	*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidInterrputEnable()
{

	
	SET_BIT( ADCSRA , 3 );
	
}


/****************************************************************/
/* Description    : This function used to DisEnable ADC Interrput	*/
/*																	*/
/*					Inputs : void					  				*/
/*					Return : void		 							*/
/********************************************************************/
/* Pre_condition  :  this function must be used after ADC			*/
/*     				 initialized 									*/
/********************************************************************/

void ADC_voidInterrputDisEnable()
{

	
	CLEAR_BIT( ADCSRA , ADIE );
	
}


/****************************************************************/
/* Description    : This function used to Disable ADC			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC 		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidDisable()
{
	
	CLEAR_BIT( ADCSRA , ADEN );
	
}


/****************************************************************/
/* Description    : This function used to Start converting		*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC 		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidStartConversion()
{
	
	SET_BIT( ADCSRA , ADSC );
	
}


/****************************************************************/
/* Description    : This function used to Set lach Interrupt	*/
/*									 happens.					*/ 
/*																*/
/*					Inputs : Sense Mode				  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/
void ADC_voidAutoTriggerDisable()
{
	 CLEAR_BIT( ADCSRA , ADATE );
}
void ADC_voidAutoTriggerEnable()
{
	
/****************************************************************/	
/** !comment : From Data Sheet : Starting conversion on positive*/
/*			   edge when ADATE = 1						    	*/
/****************************************************************/
	/** Enable ADC Auto Trigger	 							   **/
	/** ADATE = 1 =====> 	SET_BIT( ADATE , 5 ); 			   **/

    SET_BIT( ADCSRA , ADATE );
	
}

/****************************************************************/
/* Description    : This function used to Read ADC and 			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : u16 Digital Converting melli Volt	*/
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC 		*/
/*     				 initialized 							    */
/****************************************************************/

u16 ADC_u16ReadADCInMV()
{
	u16 mv_result = 0 ;
	ADC_voidStartConversion();
	// polling
	while(CHECK_BIT(ADCSRA , ADIF) == 0);
	// clear the flag
	SET_BIT(ADCSRA , ADIF );
	
	/*  ( if / else if ) condition for Macros */
	#if (ADJUSTMENT == RIGHT_ADJUSTMENT)
	mv_result = ((ADCH) * (5000UL) )/(256));
	//mv_result  *= 1000;
	
	//mv_result = (((ADCH) * (5000UL) )/(256));
	#elif (ADJUSTMENT == LEFT_ADJUSTMENT)
	mv_result = ( ( (u16)(ADCH) ) | ( (u16)(ADCL<<8) ) );

	#endif

	return mv_result;
	
}

/* Set ADC Prescaller */
void ADC_SetPrescaller(ADC_PRESCALLER_t prescaller)
{
	ADCSRA = (ADCSRA & (0xF8));
	switch(prescaller)
	{
		case DIVID_BY_2:
			ADCSRA = ADCSRA | DIVID_BY_2;		// ADCSRA | 1
		break;
		case DIVID_BY_4:
			ADCSRA = ADCSRA | DIVID_BY_4;		// ADCSRA | 2
		break;
		case DIVID_BY_8:
			ADCSRA = ADCSRA | DIVID_BY_8;		// ADCSRA | 3
		break;
		case DIVID_BY_16:
			ADCSRA = ADCSRA | DIVID_BY_16;		// ADCSRA | 4
		break;
		case DIVID_BY_32:
			ADCSRA = ADCSRA | DIVID_BY_32;		// ADCSRA | 5
		break;
		case DIVID_BY_64:
			ADCSRA = ADCSRA | DIVID_BY_64;		// ADCSRA | 6
		break;
		case DIVID_BY_128:
			ADCSRA = ADCSRA | DIVID_BY_128;		// ADCSRA | 7
		break;
	}
}

/*	set ADC channel	*/
void ADC_SetSignleEndChannel(ADC_CHANNEL_t channel)
{
	ADMUX = ADMUX & (0xE0);		// 0xE0 mask to clear first 5 bits of ADMUX register
	switch(channel)
	{
		case ADC0:
			ADMUX = ADMUX | ADC0;
		break;
		case ADC1:
			ADMUX = ADMUX | ADC1;
		break;
		case ADC2:
			ADMUX = ADMUX | ADC2;		
		break;
		case ADC3:
			ADMUX = ADMUX | ADC3;		
		break;
		case ADC4:
			ADMUX = ADMUX | ADC4;		
		break;
		case ADC5:
			ADMUX = ADMUX | ADC5;		
		break;
		case ADC6:
			ADMUX = ADMUX | ADC6;		
		break;
		case ADC7:
			ADMUX = ADMUX | ADC7;		
		break;
	}
}

/*	set ADC Auto trigger source in Auto trigger mode */
void ADC_AutoTriggerSource(ADC_AUTO_TRIGGER_SOURCE_t trigger_source)
{
	SFIOR = (SFIOR & 0x1F);
	switch(trigger_source)
	{
		case FREE_RUNNING_MODE:
			SFIOR = (SFIOR & (FREE_RUNNING_MODE<<ADTS0));
		break;
		case ANALOG_COMPARATOR:
			SFIOR = (SFIOR & (ANALOG_COMPARATOR<<ADTS0));
		break;
		case EXTERNAL_INTERRPUT_REQUEST_0:
			SFIOR = (SFIOR & (EXTERNAL_INTERRPUT_REQUEST_0<<ADTS0));
		break;
		case TIMER_COUNTER_0_COMPARE_MATCH:
			SFIOR = (SFIOR & (TIMER_COUNTER_0_COMPARE_MATCH<<ADTS0));
		break;
		case TIMER_COUNTER_0_OVERFLOW:
			SFIOR = (SFIOR & (TIMER_COUNTER_0_OVERFLOW<<ADTS0));
		break;
		case TIMER_COUNTER_COMPARE_MATCH_B:
			SFIOR = (SFIOR & (TIMER_COUNTER_COMPARE_MATCH_B<<ADTS0));
		break;
		case TIMER_COUNTER_1_OVERFLOW:
			SFIOR = (SFIOR & (TIMER_COUNTER_1_OVERFLOW<<ADTS0));
		break;
		case TIMER_COUNTER_1_CAPTURE_EVENT:
			SFIOR = (SFIOR & (TIMER_COUNTER_1_CAPTURE_EVENT<<ADTS0));
		break;
		
	}
}

void ADC_VoidSetCallBack(fptr adderesscpy)
{
	if(adderesscpy != NULLPTR)
	{
		ADC_HandlerFptr = adderesscpy;
	}
	
}

void __vector_16(void) __attribute__((signal,used));
void __vector_16(void)
{
	ADC_HandlerFptr();
}
/***********************************************************************************************/
/************************************* END OF PROGRAM ******************************************/
/***********************************************************************************************/