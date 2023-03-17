/*
 * SPI_types.h
 *
 * Created: 3/15/2023 3:29:08 PM
 *  Author: basem
 */ 


#ifndef SPI_TYPES_H_
#define SPI_TYPES_H_



typedef enum
{
	//spi_MODES
	SPI_MODE_0,
	SPI_MODE_1,
	SPI_MODE_2,
	SPI_MODE_3
	
	}SPI_data_sampling_mode_t;

typedef enum
{
	//SPI PRESECALLER
	SPI_PRESCALLER_4,
	SPI_PRESCALLER_16,
	SPI_PRESCALLER_64,
	SPI_PRESCALLER_128,
	SPI_PRESCALLER_2,
	SPI_PRESCALLER_8,
	SPI_PRESCALLER_32,
	
	}SPI_clk_prescaller_t;
	
typedef enum
{
	SPI_MS_FIRST,
	SPI_LS_FISRT
	}SPI_data_direction_t;


#endif /* SPI_TYPES_H_ */