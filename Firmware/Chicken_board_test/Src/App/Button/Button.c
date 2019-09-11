/*
 * Button.c
 *
 *  Created on: Sep 11, 2019
 *      Author: 16138
 */

#include "Button.h"

static void Button_callback(uint8_t *cnt){
	GPIO_PinState pinState1 = HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin);
	GPIO_PinState pinState2 = HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin);
	  if(pinState1 == GPIO_PIN_RESET || pinState2 == GPIO_PIN_RESET){
		  HAL_GPIO_WritePin(LED_ONBOARD_GPIO_Port, LED_ONBOARD_Pin, GPIO_PIN_RESET);
	  }
	  else{
		  HAL_GPIO_WritePin(LED_ONBOARD_GPIO_Port, LED_ONBOARD_Pin, GPIO_PIN_SET);
	  }
}

void Button_app(){
	timer_register_callback(Button_callback, 10, 0, TIMER_MODE_REPEAT);
}
