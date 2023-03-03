#ifndef EXTIS_TYPES_H_
#define EXTIS_TYPES_H_


typedef void (*pf)(void)

typedef enum {
	
	EX_INT0,
	EX_INT1,
	EX_INT2
	
}EXTI_Source_t;

typedef enum {
	
	LOW_LEVEL,
	ANY_LOGICAL_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
	
}EXTI_SenseControl_t;


#endif