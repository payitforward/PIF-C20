/*  
Author  : Pay It Forward 
website : http://www.payitforward.edu.vn/wordpress/
*/

#ifndef _PID_H_
#define _PID_H_

#include "stm32f1xx.h"
typedef struct
{
			float Kp;
			float Ki;
			float Kd;
			float error ;
			float pre_error;
			float pre2_error;
			float Ts;
			float KP_part;
		  float KI_part;
			float KD_part;
			float Out;
			float pre_Out;
			float PID_Saturation;
}PID_parameter;

void PID_SET_PARAMs(PID_parameter* pid_parameters,float Kp,float Ki,float Kd);
float PID_PROCESS(PID_parameter* pid_parameter, float vitri,float setpoint);
#endif  



