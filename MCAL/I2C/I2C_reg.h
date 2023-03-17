/*
 * I2C_reg.h
 *
 * Created: 3/16/2023 8:30:10 PM
 *  Author: basem
 */ 


#ifndef I2C_REG_H_
#define I2C_REG_H_

#define TWBR		*((volatile u8 *)(0x20))

#define	TWCR		*((volatile u8 *)(0x56))
#define	TWINT		7
#define TWEA		6
#define	TWSTA		5	
#define	TWSTO		4
#define	TWWC		3
#define	TWEN		2
#define	TWIE		0

#define TWSR		*((volatile u8 *)(0x21))
#define	TWPS1		1
#define	TWPS0		0

#define TWDR		*((volatile u8 *)(0x23))
#define TWD0		0


#define TWAR		*((volatile u8 *)(0x22))
#define TWGCE		0


#endif /* I2C_REG_H_ */