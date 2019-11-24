#include "PID.h"


void PID_SET_PARAMs(PID_parameter* pid_parameters,float Kp,float Ki,float Kd)
{
	pid_parameters->Kp = Kp;
	pid_parameters->Ki = Ki;
	pid_parameters->Kd = Kd;
}
float PID_PROCESS(PID_parameter* pid_parameter, float vitri,float setpoint)   //setpoint = 0;
{
		pid_parameter->error =  vitri - setpoint;
    pid_parameter->pre2_error = pid_parameter->pre_error;
    pid_parameter->pre_error = pid_parameter->error;
    
    pid_parameter->pre_Out = pid_parameter->Out;

    pid_parameter->KP_part = pid_parameter->Kp * (pid_parameter->error - pid_parameter->pre_error);
    pid_parameter->KI_part = 0.5* pid_parameter->Ki * pid_parameter->Ts * (pid_parameter->error + pid_parameter->pre_error);
    pid_parameter->KD_part =(pid_parameter->Kd / pid_parameter->Ts) * (pid_parameter->error - 2*pid_parameter->pre_error +pid_parameter->pre2_error);

    pid_parameter->Out = pid_parameter->pre_Out+ pid_parameter->KP_part + pid_parameter->KI_part +pid_parameter->KD_part;
    
    if (pid_parameter->Out > pid_parameter->PID_Saturation)
	  {
			pid_parameter->Out = pid_parameter->PID_Saturation;
	   }
	  else if (pid_parameter->Out < (-pid_parameter->PID_Saturation))
	  {
			pid_parameter->Out = -pid_parameter->PID_Saturation;
	  }
		
    return pid_parameter->Out; 
}