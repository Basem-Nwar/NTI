#ifndef _EXTIS_PRIVATE_H_
#define _EXTIS_PRIVATE_H_


#define MCUCR		*((volatile u8 * ) (0X55))
#define ISC00		0
#define ISC01		1
#define ISC10		2
#define ISC11		3

#define MCUCSR      *((volatile u8 * ) (0X54))
#define ISC2		6

#define GICR        *((volatile u8 * ) (0X5B))
#define	INT2		5
#define INT0		6
#define INT1		7

#define GIFR        *((volatile u8 * ) (0X5A))
#define	INTF2		5
#define INTF0		6
#define INTF1		7



#endif