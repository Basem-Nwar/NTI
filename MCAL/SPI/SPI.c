/*
 * SPI.c
 *
 * Created: 3/15/2023 3:28:13 PM
 *  Author: basem
 */ 
#include "SPI.h"
#include "SPI_private.h"
#include "std_types.h"
#include "bit_math.h"

static void SPI_Sampling_mode(SPI_data_sampling_mode_t spi_mode);
static void SPI_data_direction(SPI_data_direction_t dir);

void SPI_MasterInit(SPI_clk_prescaller_t prescaller, SPI_data_sampling_mode_t spi_mode, SPI_data_direction_t dir)
{
	// configure PRESCALLER
	switch(prescaller)
	{
		case SPI_PRESCALLER_4:
			CLEAR_BIT(SPCR,SPR0);
			CLEAR_BIT(SPCR,SPR1);
			CLEAR_BIT(SPSR,SPI2X);
		break;
		case SPI_PRESCALLER_16:
			SET_BIT(SPCR,SPR0);
			CLEAR_BIT(SPCR,SPR1);
			CLEAR_BIT(SPSR,SPI2X);
		
		break;
		case SPI_PRESCALLER_64:
			CLEAR_BIT(SPCR,SPR0);
			SET_BIT(SPCR,SPR1);
			CLEAR_BIT(SPSR,SPI2X);
		
		break;
		case SPI_PRESCALLER_128:
			SET_BIT(SPCR,SPR0);
			SET_BIT(SPCR,SPR1);
			CLEAR_BIT(SPSR,SPI2X);
		break;
		case SPI_PRESCALLER_2:
			CLEAR_BIT(SPCR,SPR0);
			CLEAR_BIT(SPCR,SPR1);
			SET_BIT(SPSR,SPI2X);
		break;
		case SPI_PRESCALLER_8:
			SET_BIT(SPCR,SPR0);
			CLEAR_BIT(SPCR,SPR1);
			SET_BIT(SPSR,SPI2X);
		break;
		case SPI_PRESCALLER_32:
			CLEAR_BIT(SPCR,SPR0);
			SET_BIT(SPCR,SPR1);
			SET_BIT(SPSR,SPI2X);
		break;
		
	}
	
	SPI_Sampling_mode(spi_mode);
	SPI_data_direction(dir);
	//enable SPI in master mode
		SET_BIT(SPCR,MSTR);
	//configure pins
		dio_VidConfigChannel(SPI_PORT,MOSI,OUTPUT);
		dio_VidConfigChannel(SPI_PORT,MISO,INPUT);
		dio_VidConfigChannel(SPI_PORT,SCK,OUTPUT);
		// ss output to make sure it can not drive from outside and master turn into slave
		dio_VidConfigChannel(SPI_PORT,SS,OUTPUT);
	//enable SPI 
		SET_BIT(SPCR,SPE);
	
}

void SPI_SlaveInit(SPI_data_sampling_mode_t spi_mode, SPI_data_direction_t dir)
{
	SPI_Sampling_mode(spi_mode);
	SPI_data_direction(dir);
	//SPI slave pin configuration
	dio_VidConfigChannel(SPI_PORT,MOSI,INPUT);
	dio_VidConfigChannel(SPI_PORT,MISO,OUTPUT);
	dio_VidConfigChannel(SPI_PORT,SCK,INPUT);
	dio_VidConfigChannel(SPI_PORT,SS,INPUT);
	//enable SPI in Slave mode
	CLEAR_BIT(SPCR,MSTR);
	//enable SPI
	SET_BIT(SPCR,SPE);
}
void SPI_SendData(u8 data)
{
	SPDR = data;
	while(!CHECK_BIT(SPSR,SPIF));

}

u8 SPI_RecieveData(void)
{
	while(!CHECK_BIT(SPSR,SPIF));
	return SPDR;
}



static void SPI_Sampling_mode(SPI_data_sampling_mode_t spi_mode)
{
	// configure data sampling mode
	switch(spi_mode)
	{
		case SPI_MODE_0:
		CLEAR_BIT(SPCR,CPHA);
		CLEAR_BIT(SPCR,CPOL);
		break;
		case SPI_MODE_1:
		SET_BIT(SPCR,CPHA);
		CLEAR_BIT(SPCR,CPOL);
		break;
		case SPI_MODE_2:
		CLEAR_BIT(SPCR,CPHA);
		SET_BIT(SPCR,CPOL);
		break;
		case SPI_MODE_3:
		SET_BIT(SPCR,CPHA);
		SET_BIT(SPCR,CPOL);
		break;
	}
	
}

static void SPI_data_direction (SPI_data_direction_t dir)
{
	// configure data direction
	switch(dir)
	{
		case SPI_MS_FIRST:
		CLEAR_BIT(SPCR,DORD);
		break;
		case SPI_LS_FISRT:
		SET_BIT(SPCR,DORD);
		break;
	}
}