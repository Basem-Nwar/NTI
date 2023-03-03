/****************************************************************/
/*   Author             :    Ahmed Atia Atia 				    */
/*	 Date 				:    2 May 2019  						*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:   public Accessing mechanism prototype*/ 
/*							and Sense Mode Definition [int.h] 	*/
/****************************************************************/



/****************************************************************/
/* Description   : Guard to protect this File from include more */
/*                 than one time .                              */
/****************************************************************/

#ifndef _ADC_INT_H
#define _ADC_INT_H


/****************************************************************/	
/** !comment : Sense Mode Definition					   		*/
/****************************************************************/

#define AVCC 					5
#define AREF 					4
#define INTERNAL				2.56

#define RIGHT_ADJUSTMENT 		0
#define LEFT_ADJUSTMENT 		1


typedef enum
{
	DIVID_BY_2	= 1,
	DIVID_BY_4	= 2,
	DIVID_BY_8	= 3,
	DIVID_BY_16	= 4,
	DIVID_BY_32	= 5,
	DIVID_BY_64	= 6,
	DIVID_BY_128= 7
	}ADC_PRESCALLER_t;
	

typedef enum
{
	FREE_RUNNING_MODE,
	ANALOG_COMPARATOR,
	EXTERNAL_INTERRPUT_REQUEST_0,
	TIMER_COUNTER_0_COMPARE_MATCH,
	TIMER_COUNTER_0_OVERFLOW,
	TIMER_COUNTER_COMPARE_MATCH_B,
	TIMER_COUNTER_1_OVERFLOW,
	TIMER_COUNTER_1_CAPTURE_EVENT	
	}ADC_AUTO_TRIGGER_SOURCE_t;

typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
	}ADC_CHANNEL_t;


/****************************************************************/
/* Description    :  This function used to initialize ADC 	    */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/

void ADC_voidInit (void);


//****************************************************************/
/* Description    : This function used to Enable ADC			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidEnable();


/****************************************************************/
/* Description    : This function used to Enable ADC Interrput	*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidInterrputEnable();

/****************************************************************/
/* Description    : This function used to DisEnable ADC Interrput	*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidInterrputDisEnable();

/****************************************************************/
/* Description    : This function used to Disable ADC			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC 		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidDisable();


/****************************************************************/
/* Description    : This function used to communicate with the	*/
/*					function in App Layer(The Callback function)*/ 
/*						[ Layer Architecture Problem Solved ]	*/
/*																*/
/*					Inputs : Pointer to function that points to	*/
/*							 the first line of the function(ISR)*/
/*					Return : void								*/
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/
void ADC_VoidSetCallBack(fptr adderesscpy);


//u8 ADC_u8ReadADC(fptr addresscpy);



/****************************************************************/
/* Description    : This function used to Start converting		*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC 		*/
/*     				 initialized 							    */
/****************************************************************/

void ADC_voidStartConversion();


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

void ADC_voidAutoTriggerEnable();
void ADC_voidAutoTriggerDisable();



/****************************************************************/
/* Description    : This function used to Read ADC and 			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : u16 Digital Converting melli Volt	*/
/****************************************************************/
/* Pre_condition  :  this function must be used after ADC 		*/
/*     				 initialized 							    */
/****************************************************************/

u16 ADC_u16ReadADCInMV();

/* Set ADC Prescaller */
void ADC_SetPrescaller(ADC_PRESCALLER_t);

/*	set ADC channel	*/
void ADC_SetSignleEndChannel(ADC_CHANNEL_t);

/*	set ADC Auto trigger source in Auto trigger mode */
void ADC_AutoTriggerSource(ADC_AUTO_TRIGGER_SOURCE_t);


u16 ADC_u16ReadADCInMV();


#endif	/** !comment  :  End of guard                          **/