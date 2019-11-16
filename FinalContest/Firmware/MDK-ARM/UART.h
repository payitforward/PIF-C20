#ifndef _UART_H_
#define _UART_H_

#include "stm32f1xx_hal.h"
#include "stdbool.h"
/* Constant definitions  */
#define MAX   			 255
#define START_BYTE   0x55
#define STOP_BYTE    0xAA
#define ESC_BYTE		 0x7D


/* Data type definitions */
typedef enum
	{
		control,
		detect_line
	}operation_mode;
typedef struct 
	{
		unsigned char data[MAX];
		unsigned char length;
	}dataPackage,*ptr_dataPackage;
// state of receive data
typedef enum
	{
			Wait_startbyte,
			In_msg,
			Stop_byte
	}RX_STATE;
typedef enum
	{
			Left,
			Right,
			Forward,
			Backward
	}State_CONTROL;

bool valid_Data_Package(ptr_dataPackage mesg);
void EncoderDataPackage(unsigned char buff[MAX],ptr_dataPackage pmesg);
void DecoderDataPackage(unsigned char result[MAX],ptr_dataPackage pmesg);
void ReceiveDataPackage(unsigned char Rx_buff[MAX]);


#endif  /* _UART_H_*/