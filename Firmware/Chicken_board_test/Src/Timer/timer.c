/*
 * timer.c
 *
 *  Created on: Sep 6, 2019
 *      Author: 16138
 */
#include "tim.h"
#include "timer.h"

#define MAX_CALLBACK_FUNC	15

static callback_t callbacks[MAX_CALLBACK_FUNC];
static uint64_t ms = 0;
timer_ID_t timer_register_callback(timer_callback_func_t timer_callback_func, uint16_t period_ms, uint8_t* context, timer_mode_t mode){
	for(uint8_t i = 0; i < MAX_CALLBACK_FUNC; i++){
		if(callbacks[i].timer_callback_func == 0){
			callbacks[i].timer_callback_func = timer_callback_func;
			callbacks[i].period_ms = period_ms;
			callbacks[i].context = context;
			callbacks[i].cnt = 0;
			callbacks[i].id = i;
			callbacks[i].mode = mode;
			return i;
		}
	}
	return -1;
}

void timer_unregister_callback(uint8_t id){
	callbacks[id].timer_callback_func = 0;
}

uint64_t milis(){
	return ms;
}

static void timer_callback(){
	ms++;
	for(uint8_t i = 0; i < MAX_CALLBACK_FUNC; i++){
		if(callbacks[i].timer_callback_func != 0){
			callbacks[i].cnt++;
			if(callbacks[i].cnt == callbacks[i].period_ms){
				callbacks[i].timer_callback_func(callbacks[i].context);
				callbacks[i].cnt = 0;
				if(callbacks[i].mode == TIMER_MODE_ONE_SHOT) callbacks[i].timer_callback_func = 0;
			}
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim1.Instance)
    {
    	timer_callback();
    }
}
