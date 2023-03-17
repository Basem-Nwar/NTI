/*
 * I2C_cfg.h
 *
 * Created: 3/17/2023 2:00:51 AM
 *  Author: basem
 */ 


#ifndef I2C_CFG_H_
#define I2C_CFG_H_

/*	ENABLE>> 1 /  DIABL>> 0	E*/
#define I2C_GENERAL_CALL_ENABLE			DISABLE
#define I2C_Acknowledge_Enable			ENABLE

/*
 *		I2C_PRESCALLER_1,
 *		I2C_PRESCALLER_4,
 *		I2C_PRESCALLER_16,
 *		I2C_PRESCALLER_64
*/
#define I2C_PRESCALLER					I2C_PRESCALLER_1



#endif /* I2C_CFG_H_ */