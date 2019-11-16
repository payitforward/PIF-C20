#include "stdbool.h"
#include "stdio.h"
#include "stdint.h"

/*include Library*/
#include "UART.h"

volatile RX_STATE  state;
volatile unsigned char nindex,lastRxData,flag_frame_receive;
volatile dataPackage    Data_RX_Package;

bool valid_Data_Package(ptr_dataPackage mesg)
	{
			return((mesg ->data[0] ==	START_BYTE ) && (mesg -> data[mesg->length -1] == STOP_BYTE));
	}

/* ma hoa data tu buff len message*/	
void EncoderDataPackage(unsigned char buff[MAX],ptr_dataPackage pmesg)
	{
		  uint8_t i = 1;
			pmesg->data[0] = START_BYTE;
			unsigned char *pBuff = buff;
		  while(*pBuff !='\0')
				{
				  	if (*pBuff == START_BYTE || *pBuff == STOP_BYTE  || *pBuff == ESC_BYTE)	
							{
							   	pmesg -> data[i++] = ESC_BYTE;
							}
						pmesg->data[i++] = *pBuff;
						pBuff++;				
				}
			pmesg->data[i++] = STOP_BYTE;
			pmesg->length = i;
			pmesg->data[i] = '\0';	
	}

/* giai ma data tu message ve buff*/
void DecoderDataPackage(unsigned char result[MAX],ptr_dataPackage pmesg)
	{
			uint8_t  j = 1;
		  unsigned char *pData = result;
		  for (j = 1;j < pmesg->length -1;j++)
				{
						if (pmesg->data[j] == ESC_BYTE )
							{
									j+=1;
									*pData = pmesg->data[j];
							}
						else
							{
									*pData = pmesg->data[j];
							}
						pData++;
				}
		   *pData ='\0';
	}
void ReceiveDataPackage(unsigned char Rx_buff[MAX])
	{
			unsigned char *pRx_buff = Rx_buff;
			switch(state)
				{
				case Wait_startbyte:
					{
						  lastRxData = '\0';
							nindex = 0;
							if (*pRx_buff == START_BYTE)
								{
										Data_RX_Package.data[nindex++] = START_BYTE;
										lastRxData = *pRx_buff;
										state = In_msg;
								}
							break;
					}
				case In_msg:
					{
							if (*pRx_buff == STOP_BYTE && lastRxData != ESC_BYTE)
								{
										state = Stop_byte;
										break;
								}
							if (*pRx_buff == START_BYTE && lastRxData != ESC_BYTE)
								{
										// truyen lai du lieu
										nindex = 0;
										Data_RX_Package.data[nindex++] = *pRx_buff;
										lastRxData = *pRx_buff;
										break;
								}
								Data_RX_Package.data[nindex++] = *pRx_buff;
								lastRxData = *pRx_buff;
								break;

					}
				case Stop_byte:
					{
							Data_RX_Package.data[nindex++] = STOP_BYTE;
							Data_RX_Package.data[nindex] = '\0';
							Data_RX_Package.length = nindex;
							flag_frame_receive =1; //set flag to process frame data
							state = Wait_startbyte;
							break;
					}
				}
	}
	
	
