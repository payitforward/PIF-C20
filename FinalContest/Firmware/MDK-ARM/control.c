#include "control.h"
#include "stdint.h"
/**
  * @brief function control
  * @param None
  */
void forward(int speed)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);  // dong co trai
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET); // dong co phai
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);

	}
void backward(int speed)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET);
	
	}
void stop(int speed)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);
		
	}
void left(int speed)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);  // dong co trai
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET); // dong co phai
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);

	}
void right(int speed)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);  // dong co trai
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET); // dong co phai
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);
		
	}
