#include "control.h"

void move(int motor,int dir)  
	{
	if(motor == 0)    // motor = 0 : dong co phai
    {
		if(dir == 0)   // nguoc chieu kim dong ho
		{
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET);
		}
		else if(dir == 1)  // cung chieu kim dong ho
		{
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);
		}
		}
	else if (motor == 1)  // motor = 1 : dong co trai
		{			
		if(dir == 0)	// nguoc chieu kim dong ho
		{
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
		}
		else if(dir == 1) // cung chieu kim dong ho
		{
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
		}
		}
	}