/*
 * SPI_private.h
 *
 * Created: 3/15/2023 3:28:52 PM
 *  Author: basem
 */ 


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#include "dio.h"


#define SPCR	*( (volatile u8 *) (0x2D) )
#define	SPIE	7
#define	SPE		6
#define	DORD	5
#define	MSTR	4
#define	CPOL	3
#define	CPHA	2
#define	SPR1	1
#define	SPR0	0

#define SPSR	*( (volatile u8 *) (0x2E) )
#define	SPIF	7
#define	WCOL	6
#define	SPI2X	0

#define SPDR	*( (volatile u8 *) (0x2F) )

#define SPI_PORT	DIO_PORTB
#define MOSI		DIO_PIN5
#define MISO		DIO_PIN6
#define SCK			DIO_PIN7
#define SS			DIO_PIN4

#endif /* SPI_PRIVATE_H_ */