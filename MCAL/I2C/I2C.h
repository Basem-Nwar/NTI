/*
 * I2C.h
 *
 * Created: 3/16/2023 8:29:47 PM
 *  Author: basem
 */ 


#ifndef I2C_H_
#define I2C_H_

typedef enum
{
	I2C_NoError = 0,
	I2C_SC_ERROR,
	I2C_RSC_ERROR,
	I2C_MT_SLA_R_ERROR,
	I2C_MT_SLA_W_ERROR,
	I2C_MT_DATA_ERROR,
	I2C_MR_DATA_ERROR,
	I2C_SR_DATA_ERROR
}I2C_Error_Status;

void I2C_MasterInit(u8 master_address);
void I2C_SlaveInit(u8 slave_address);
I2C_Error_Status I2C_MasterWriteData(u8 data);
I2C_Error_Status I2C_MasterReadData(u8 * revieved_data);
I2C_Error_Status I2C_StartCondition(void);
I2C_Error_Status I2C_Repeated_StartCondition(void);
//slave address with write 
I2C_Error_Status I2C_Send_Slave_AddressWithWrite(u8 slave_address);
// slave address with read
I2C_Error_Status I2C_Send_Slave_AddressWithRead(u8 slave_address);
//Stop Condition
void I2C_StopCondition(void);


#endif /* I2C_H_ */