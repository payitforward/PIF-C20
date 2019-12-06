/*  
Author  : Pay It Forward 
website : http://www.payitforward.edu.vn/wordpress/
*/

#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "stm32f1xx.h"

extern void forward(int speed);
extern void backward(int speed);
extern void stop(int speed);
extern void left(int speed);
extern void right(int speed);

#endif