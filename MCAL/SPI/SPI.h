/*
 * SPI.h
 *
 * Created: 3/15/2023 3:28:30 PM
 *  Author: basem
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "SPI_types.h"
#include "std_types.h"

void SPI_MasterInit(SPI_clk_prescaller_t prescaller,SPI_data_sampling_mode_t spi_mode, SPI_data_direction_t dir);
void SPI_SlaveInit(SPI_data_sampling_mode_t spi_mode, SPI_data_direction_t dir);
void SPI_SendData(u8 data);
u8 SPI_RecieveData(void);



#endif /* SPI_H_ */