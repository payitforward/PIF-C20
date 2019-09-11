/*
 * LM32.c
 *
 *  Created on: Sep 6, 2019
 *      Author: 16138
 */

#include "stdio.h"
#include "string.h"
#include "LM35.h"

#include "Timer/timer.h"
#include "adc.h"
#include "usart.h"

static uint32_t temperature = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc1)
{
	temperature = HAL_ADC_GetValue(hadc1);
}

void LM35_Conv_callback(uint8_t* context){
	HAL_ADC_Start_IT(&hadc1);
}

void LM35_callback(uint8_t* context){
	char string[20];
	sprintf(string, "Temperature: %d\r\n", (int)temperature);
	HAL_UART_Transmit(&huart1, (uint8_t*)string, (uint16_t)strlen(string), HAL_MAX_DELAY);
}

void LM35_app(){
	HAL_ADC_Start_IT(&hadc1);
	timer_register_callback(LM35_callback, 1000, 0, TIMER_MODE_REPEAT);
	timer_register_callback(LM35_Conv_callback, 200, 0, TIMER_MODE_REPEAT);
}

uint8_t LM35_get_temperature(){
	return temperature;
}
