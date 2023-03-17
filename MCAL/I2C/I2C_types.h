/*
 * I2C_types.h
 *
 * Created: 3/16/2023 8:30:24 PM
 *  Author: basem
 */ 


#ifndef I2C_TYPES_H_
#define I2C_TYPES_H_

#define ENABLE		1
#define DISABLE		0

typedef enum
{
	I2C_PRESCALLER_1,
	I2C_PRESCALLER_4,
	I2C_PRESCALLER_16,
	I2C_PRESCALLER_64
	}I2C_prescaller_t;




#endif /* I2C_TYPES_H_ */