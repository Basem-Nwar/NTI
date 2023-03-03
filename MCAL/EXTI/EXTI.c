
#include "bit_math.h"
#include "std_types.h" 

#include "EXTI.h"
#include "EXTI_types"
#include "EXTI_private"




static volatile fptr EXTI0_HandlerFptr = NULLPTR;
static volatile fptr EXTI1_HandlerFptr = NULLPTR;
static volatile fptr EXTI2_HandlerFptr = NULLPTR;



void EXTI_VoidInit(void)
{
	// CLEAR ALL FLAGS AND DISABLE ALL INTERRUPTS

	CLEAR_BIT(GICR,INT0);
	SET_BIT(GIFR,INTF0);
	
	CLEAR_BIT(GICR,INT1);
	SET_BIT(GIFR,INTF1);
	
	CLEAR_BIT(GICR,INT2);
	SET_BIT(GIFR,INTF2);

}

void EXTI_VoidEnable(EXTI_Source_t interrupt)
{
	switch(interrupt)
	{
		case EX_INT0:
			SET_BIT(GICR,INT0);
		break;
		case EX_INT1:
			SET_BIT(GICR,INT1);
		break;
		case EX_INT2:
			SET_BIT(GICR,INT2);
		break;
	}
}

void EXTI_VoidDisEnable(EXTI_Source_t interrupt)
{
	switch(interrupt)
	{
		case EX_INT0:
			CLEAR_BIT(GICR,INT0);
		break;
		case EX_INT1:
			CLEAR_BIT(GICR,INT1);
		break;
		case EX_INT2:
			CLEAR_BIT(GICR,INT2);
		break;
	}
}
void EXTI_VoidSenseControl(EXTI_Source_t interrupt, EXTI_SenseControl_t source)
{
	switch(interrupt)
	{
		case EX_INT0:
			switch(source)
			{
				case LOW_LEVEL:
					CLEAR_BIT(MCUCR,ISC00);
					CLEAR_BIT(MCUCR,ISC01);
				break;
				
				case ANY_LOGICAL_CHANGE:
					CLEAR_BIT(MCUCR,ISC01);
					SET_BIT(MCUCR,ISC00);
				break;
				
				case FALLING_EDGE:
					CLEAR_BIT(MCUCR,ISC00);
					SET_BIT(MCUCR,ISC01);
				break;
				
				case RISING_EDGE :
					SET_BIT(MCUCR,ISC00);
					SET_BIT(MCUCR,ISC01);
				break;
				
				default:
				break;
					
			}
		case EX_INT1:
			switch(source)
			{
				case LOW_LEVEL:
					CLEAR_BIT(MCUCR,ISC10);
					CLEAR_BIT(MCUCR,ISC11);
				break;
				
				case ANY_LOGICAL_CHANGE:
					CLEAR_BIT(MCUCR,ISC11);
					SET_BIT(MCUCR,ISC10);
				break;
				
				case FALLING_EDGE:
					CLEAR_BIT(MCUCR,ISC10);
					SET_BIT(MCUCR,ISC11);
				break;
				
				case RISING_EDGE :
					SET_BIT(MCUCR,ISC10);
					SET_BIT(MCUCR,ISC11);
				break;
				
				default:
				break;
					
			}
		case EX_INT0:
			switch(source)
			{
				
				case FALLING_EDGE:
					CLEAR_BIT(MCUCSR,ISC2);
				break;
				
				case RISING_EDGE :
					SET_BIT(MCUCSR,ISC2);
				break;
				
				default:
				break:
			}
			
		default;
		break;
	}
}

void EXTI_VoidSetCallBack(EXTI_Source_t interrupt,fptr addresscpy)
{
	if(addresscpy != Null )
	{
		switch(interrupt)
		{
			case EX_INT0:
				EXTI0_HandlerFptr = addresscpy;
			break;
			case EX_INT1:
				EXTI1_HandlerFptr = addresscpy;
			break;
			case EX_INT2:
				EXTI2_HandlerFptr = addresscpy;
			break;
			default;
			break;
		}
	}
	else
	{
		
	}
}

void __vector_1(void) __attribute__((signal,used));
void __vector_1(void)
{
	EXTI0_HandlerFptr();
}

void __vector_2(void) __attribute__((signal,used));
void __vector_2(void)
{
	EXTI1_HandlerFptr();
}

void __vector_3(void) __attribute__((signal,used));
void __vector_3(void)
{
	EXTI2_HandlerFptr();
}