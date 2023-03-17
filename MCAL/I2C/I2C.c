/*
 * I2C.c
 *
 * Created: 3/16/2023 8:29:31 PM
 *  Author: basem
 */ 

#include "bit_math.h"
#include "std_types.h"

#include "I2C.h"
#include "I2C_private.h"
#include "I2C_reg.h"
#include "I2C_types.h"

#define	STATUS_REGISTER_MASK	0xF8


void I2C_MasterInit(u8 master_address)
{
	#if		(I2C_PRESCALLER == I2C_PRESCALLER_1)
		CLEAR_BIT(TWSR,TWPS0);
		CLEAR_BIT(TWSR,TWPS1);
	#elif	(I2C_PRESCALLER == I2C_PRESCALLER_4)
		SET_BIT(TWSR,TWPS0);
		CLEAR_BIT(TWSR,TWPS1);
	#elif	(I2C_PRESCALLER == I2C_PRESCALLER_16)
		CLEAR_BIT(TWSR,TWPS0);
		SET_BIT(TWSR,TWPS1);
	#elif	(I2C_PRESCALLER == I2C_PRESCALLER_64)
		SET_BIT(TWSR,TWPS0);
		SET_BIT(TWSR,TWPS1);
	#endif
	
	if(master_address != 0 )
	{
		TWAR= master_address<<1;
	}
	
	// bit rate register value
	TWBR=	0 ; //////////////////////
	
	// ack mode
	#if (I2C_Acknowledge_Enable == ENABLE)
		SET_BIT(TWCR,TWEA);
	#elif (I2C_Acknowledge_Enable == DISABLE)
		CLEAR_BIT(TWCR,TWEA);
	#endif
	
	// general call mode
	#if (I2C_GENERAL_CALL_ENABLE == ENABLE)
		SET_BIT(TWAR,TWGCE);
	#elif (I2C_GENERAL_CALL_ENABLE == DISABLE)
		CLEAR_BIT(TWAR,TWGCE);
	#endif
	
	// enable twi interface
	SET_BIT(TWCR,TWEN);
}
void I2C_SlaveInit(u8 slave_address)
{
	if(slave_address != 0 )
	{
		TWAR= slave_address<<1;
	}
	
	// ack mode
	#if (I2C_Acknowledge_Enable == ENABLE)
		SET_BIT(TWCR,TWEA);
	#elif (I2C_Acknowledge_Enable == DISABLE)
		CLEAR_BIT(TWCR,TWEA);
	#endif
	
	// general call mode
	#if (I2C_GENERAL_CALL_ENABLE == ENABLE)
		SET_BIT(TWAR,TWGCE);
	#elif (I2C_GENERAL_CALL_ENABLE == DISABLE)
		CLEAR_BIT(TWAR,TWGCE);
	#endif
	
	// enable twi interface
	SET_BIT(TWCR,TWEN);
}
I2C_Error_Status I2C_MasterWriteData(u8 data)
{
	I2C_Error_Status Local_Error_status = I2C_NoError;
	
	/*	write data on TWDR	*/
	TWDR = data;
	
	/*	Clear interrupt flag to start Operation */
	SET_BIT(TWCR,TWINT);
	
	/*	Wait until the interrupt flag is set again to make sure the previous OP is complete */
	while(!(CHECK_BIT(TWCR,TWINT)));
	
	/*	check the operation status in status register	*/
	if ((TWSR & STATUS_REGISTER_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_Error_status = I2C_MT_DATA_ERROR;
	}

	return Local_Error_status;
}
I2C_Error_Status I2C_MasterReadData(u8 * revieved_data)
{
	I2C_Error_Status Local_Error_status = I2C_NoError;
	
	/*	Clear interrupt flag to START the slave sending data */
	SET_BIT(TWCR,TWINT);
	
	/*	Wait until the interrupt flag is set again to make sure the previous OP is complete */
	while(!(CHECK_BIT(TWCR,TWINT)));
	
	/*	check the operation status in status register	*/
	#if (I2C_Acknowledge_Enable == ENABLE)
		if ((TWSR & STATUS_REGISTER_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			Local_Error_status = I2C_MR_DATA_ERROR;
		}
		else
		{
			/*	READ REVIEVED DATA	*/
			*revieved_data = TWDR;
		}

	#elif (I2C_Acknowledge_Enable == DISABLE)
		if ((TWSR & STATUS_REGISTER_MASK) != MSTR_RD_BYTE_WITH_NACK)
		{
			Local_Error_status = I2C_MR_DATA_ERROR;
		}
		else
		{
			/*	READ REVIEVED DATA	*/
			*revieved_data = TWDR;
		}
	#endif

	
	return Local_Error_status;
	
}


I2C_Error_Status I2C_StartCondition(void)
{
	I2C_Error_Status Local_Error_status = I2C_NoError;
	/*	Send start condition	*/
	SET_BIT(TWCR,TWSTA);
	/*	Clear interrupt flag to start Operation */
	SET_BIT(TWCR,TWINT);
	
	/*	Wait until the interrupt flag is set again to make sure the previous OP is complete */
	while(!(CHECK_BIT(TWCR,TWINT)));
	
	/*	check the operation status in status register	*/
	if ((TWSR & STATUS_REGISTER_MASK) != START_ACK)
	{
		Local_Error_status = I2C_SC_ERROR;
	}

	/*	CLEAR START CONDITION BIT */
	CLEAR_BIT(TWCR,TWSTA);
	
	return Local_Error_status;
}


I2C_Error_Status I2C_Repeated_StartCondition(void)
{
	I2C_Error_Status Local_Error_status = I2C_NoError;
	/*	Send start condition	*/
	SET_BIT(TWCR,TWSTA);
	/*	Clear interrupt flag to start Operation */
	SET_BIT(TWCR,TWINT);
	
	/*	Wait until the interrupt flag is set again to make sure the previous OP is complete */
	while(!(CHECK_BIT(TWCR,TWINT)));
	
	/*	check the operation status in status register	*/
	if ((TWSR & STATUS_REGISTER_MASK) != REP_START_ACK)
	{
		Local_Error_status = I2C_RSC_ERROR;
	}

	/*	CLEAR START CONDITION BIT */
	CLEAR_BIT(TWCR,TWSTA);
	return Local_Error_status;
	
}
//slave address with write
I2C_Error_Status I2C_Send_Slave_AddressWithWrite(u8 slave_address)
{ 
	I2C_Error_Status Local_Error_status = I2C_NoError;

	/*	write SLAVE	address on TWDR MS 7 bits	*/
	TWDR = slave_address<<1;
	/*	clear bit 0 in TWDR to send write operation on slave */
	CLEAR_BIT(TWDR,TWD0);
	
	/*	Clear interrupt flag to start Operation */
	SET_BIT(TWCR,TWINT);
	
	/*	Wait until the interrupt flag is set again to make sure the previous OP is complete */
	while(!(CHECK_BIT(TWCR,TWINT)));
	
	/*	check the operation status in status register	*/
	if ((TWSR & STATUS_REGISTER_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_Error_status = I2C_MT_SLA_W_ERROR;
	}

	
	return Local_Error_status;
	
	
}
// slave address with read
I2C_Error_Status I2C_Send_Slave_AddressWithRead(u8 slave_address)
{
	I2C_Error_Status Local_Error_status = I2C_NoError;

	/*	write SLAVE	address on TWDR MS 7 bits	*/
	TWDR = slave_address<<1;
	/*	set bit 0 in TWDR to send Read operation on slave */
	SET_BIT(TWDR,TWD0);
	
	/*	Clear interrupt flag to start Operation */
	SET_BIT(TWCR,TWINT);
	
	/*	Wait until the interrupt flag is set again to make sure the previous OP is complete */
	while(!(CHECK_BIT(TWCR,TWINT)));
	
	/*	check the operation status in status register	*/
	if ((TWSR & STATUS_REGISTER_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_Error_status = I2C_MT_SLA_R_ERROR;
	}

	
	return Local_Error_status;
}


//Stop Condition
void I2C_StopCondition(void)
{
	/*	Send stop condition	*/
	SET_BIT(TWCR,TWSTO);
	/*	Clear interrupt flag to start the Operation */
	SET_BIT(TWCR,TWINT);

}