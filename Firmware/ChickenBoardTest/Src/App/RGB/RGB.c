/*
 * RGB.c
 *
 *  Created on: Sep 6, 2019
 *      Author: 16138
 */

#include "stdbool.h"

#include "RGB.h"

#include "tim.h"
#include "Timer/timer.h"

static void setColor(uint8_t r, uint8_t g, uint8_t b){
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, r);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, g);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, b);
}

static void setColorHex(uint32_t rgb){
	setColor(rgb >> 16 & 0x0000FF, rgb >> 8 & 0x0000FF, rgb & 0x0000FF);
}

static uint32_t i = 0;
static bool dir = true;
static void RGB_Callback(uint8_t *cnt){
	if(dir){
		i++;
	}
	else{
		i--;
	}
	setColorHex(0x707000 + i);
	if(i == 0xFF || i==0){
		dir = !dir;
	}
}

void RGB_app(){
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	  timer_register_callback(RGB_Callback, 5, 0, TIMER_MODE_REPEAT);
}

