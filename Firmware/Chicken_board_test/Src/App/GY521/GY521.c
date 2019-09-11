/*
 * GY521.c
 *
 *  Created on: Sep 6, 2019
 *      Author: 16138
 */

#ifndef APP_GY521_GY521_C_
#define APP_GY521_GY521_C_

#include "stdio.h"
#include "string.h"
#include "GY521.h"

#include "MPU6050.h"
#include "Timer/timer.h"
#include "i2c.h"
#include "usart.h"

bool connection_OK = false;
int16_t motion_6[6];

void GY521_callback(uint8_t* context){
	connection_OK = MPU6050_test_connection();
	if(connection_OK){
		mpu6050_get_motion(&motion_6[0], &motion_6[1], &motion_6[2], &motion_6[3], &motion_6[4], &motion_6[5]);
		char string[60];
		sprintf(string, "GY521: ax:%d ay:%d az:%d gx:%d gy:%d gy:%d \r\n", motion_6[0], motion_6[1], motion_6[2], motion_6[3], motion_6[4], motion_6[5]);
		HAL_UART_Transmit(&huart1, (uint8_t*)string, (uint16_t)strlen(string), HAL_MAX_DELAY);
	}
	else{
		MPU6050_initialize();
	}
}

void GY521_app(){
	MPU6050_initialize();
	connection_OK = MPU6050_test_connection();
	timer_register_callback(GY521_callback, 1000, 0, TIMER_MODE_REPEAT);
}

bool GY521_connection_OK(){
	return connection_OK;
}

bool GY521_get_accel(float accel[3]){
	if(connection_OK){
		accel[0] = motion_6[0];
		accel[1] = motion_6[1];
		accel[2] = motion_6[2];
		return true;
	}
	else{
		return false;
	}
}

bool GY521_get_gyro(float gyro[3]){
	if(connection_OK){
		gyro[0] = motion_6[3];
		gyro[1] = motion_6[4];
		gyro[2] = motion_6[5];
		return true;
	}
	else{
		return false;
	}
}

#endif /* APP_GY521_GY521_C_ */
