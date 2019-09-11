/*
 * HC05.c
 *
 *  Created on: Sep 6, 2019
 *      Author: 16138
 */

#include "HC05.h"
#include "usart.h"

static uint8_t data;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	HAL_UART_Transmit(&huart1, &data, 1, 10);
	HAL_UART_Receive_IT(&huart1, &data, 1);
}

void HC05_app(){
	HAL_UART_Receive_IT(&huart1, &data, 1);
}
