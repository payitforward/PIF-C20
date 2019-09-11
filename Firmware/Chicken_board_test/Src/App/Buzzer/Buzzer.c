/*
 * Buzzer.c
 *
 *  Created on: Sep 8, 2019
 *      Author: 16138
 */

#ifndef APP_BUZZER_BUZZER_C_
#define APP_BUZZER_BUZZER_C_

#include "Buzzer.h"

#include "gpio.h"
#include "Timer/timer.h"

static timer_ID_t goff_id = 0;
static void Buzzer_off_callback(uint8_t *cnt){
	Buzzer_off();
}

static void Buzzer_on_callback(uint8_t *cnt){
	Buzzer_on();
	goff_id = timer_register_callback(Buzzer_off_callback, 100, 0, TIMER_MODE_ONE_SHOT);
}

void Buzzer_app(){
	timer_register_callback(Buzzer_on_callback, 5000, 0, TIMER_MODE_REPEAT);
	Buzzer_on();
	HAL_Delay(100);
	Buzzer_off();
}

void Buzzer_on(){
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
}

void Buzzer_off(){
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
}

#endif /* APP_BUZZER_BUZZER_C_ */
