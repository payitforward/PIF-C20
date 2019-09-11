#ifndef _MPU6050_H_
#define _MPU6050_H_

#include "stdint.h"

void MPU6050_initialize();
bool MPU6050_test_connection();
void mpu6050_get_motion(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);

#endif /* _MPU6050_H_ */
