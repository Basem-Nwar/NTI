/*
 * uart_types.h
 *
 * Created: 3/9/2023 7:17:44 PM
 *  Author: basem
 */ 


#ifndef UART_TYPES_H_
#define UART_TYPES_H_

/*********************speed mode*************************/
#define NORMAL_SPEED      0
#define DOUBLE_SPEED      1
#define TOTAL_SPEED_MODE  2
/********************cpu freqs***************************/
#define   _4_MHZ         0
#define   _8_MHZ         1
#define  _16_MHZ         2
#define  TOTAL_CPU_F     3
/*******************baud rate *****************************/
#define  BAUD_2400       0
#define  BAUD_4800       1
#define  BAUD_9600       2
#define  BAUD_14400      3
#define  BAUD_19200      4
#define  BAUD_28800      5
#define  TOTAL_BAUD_RATE 6

/*******************UART SYNCH MODE*********************/
#define		ASYNCH					0
#define		SYNCH					2

/***************PARITY MODE********************/
#define		DISABLE					0
#define		EVEN_PARITY				2
#define		ODD_PARITY				3

/*************NUMBER OF STOP BITS**************/
#define		ONE_STOP_BITS			0
#define		TWO_STOP_BITS			1

/*************DATA SIZE***********************/
#define		_5_DATA_BITS			0
#define		_6_DATA_BITS			1
#define		_7_DATA_BITS			2
#define		_8_DATA_BITS			3
#define		_9_DATA_BITS			7





#endif /* UART_TYPES_H_ */