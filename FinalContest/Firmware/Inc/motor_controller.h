/*  
Author  : Pay It Forward 
website : http://www.payitforward.edu.vn/wordpress/
*/

#ifndef _MOTOR_CONTROLLER_H_
#define _MOTOR_CONTROLLER_H_

#include "stm32f1xx.h"
#include <stdint.h>

typedef enum{
	MOTOR_0,
	MOTOR_1
}motor_t;

/**
 * @brief Enable motor
 * 
 */
void motor_init(void);

/**
 * @brief Set speed for specific motor
 * 
 * @param motor 
 * @param speed range from -255 to 255
 */
void motor_set_speed(motor_t motor, int16_t speed);

#endif
