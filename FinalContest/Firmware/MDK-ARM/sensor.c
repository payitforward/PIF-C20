#include "sensor.h"

void read_sensor()
{
		sensor[0] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
}
