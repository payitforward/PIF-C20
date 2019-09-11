/*
 * GY521.h
 *
 *  Created on: Sep 6, 2019
 *      Author: 16138
 */

#ifndef APP_GY521_GY521_H_
#define APP_GY521_GY521_H_

#include "stdbool.h"

void GY521_app();
bool GY521_connection_OK();
bool GY521_get_accel(float accel[3]);
bool GY521_get_gyro(float gyro[3]);

#endif /* APP_GY521_GY521_H_ */
