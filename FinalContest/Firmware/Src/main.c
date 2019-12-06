/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <motor_controller.h>
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <PID.h>
#include "string.h"
#include "stdio.h"

#include <motor_controller.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int kt=0;
float vitri;
int presumindex=0;
int i_SumIndexArry=0;
static int demtimeout=1;
static int demoutline=0;
static float previtri=0;
static int demprevitri=0;

typedef enum
{
	LINE_OFF=0,
	LINE_START,
}LINE_parameter;

typedef enum 
{
	LINE_external=0,
	LINE_internal,
}LINE_Control;

LINE_parameter Line_status=LINE_START;

void Control_Value_Line(int value);
void Control_vitri_Line(float vitri);
void CONTROL();	

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef enum
	{
			UART_START =0,
			UART_APP ,
	}Uart_statemachine;
Uart_statemachine my_state = UART_START;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t pwm1 = 160;
uint8_t pwm2 = 160;
uint8_t offset = 10;
uint8_t mode = 0;    // 2 : control   , 1: line follow
int i =0;
int k =0;
int kq = 0;
uint8_t S[4];
float result_PWM;
uint8_t Rx_buff[10];
PID_parameter PID_set_parameters = {.Kp =40,.Ki=0.0001,.Kd=25,.Ts = 0.005,.PID_Saturation = 180
																			,.error =0,.pre_error =0,.pre2_error=0,.pre_Out =0,.Out = 0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
																
/*
PB0  ---> IN4 
PB1  ---> IN3 
PB10 ---> IN2 
PB11 ---> IN1 
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)   // ngat 5ms
	{
//	if (htim->Instance == htim3.Instance)
//	{
//		if (mode ==1)
//		{
//			S[3] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5); // dat gia tri = 7
//			S[2] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4); // dat gia tri = 5
//			S[1] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3); // dat gia tri = 3
//			S[0] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);// dat gia tri = 1
//			for(int i=0;i<=3;i++)
//			{
//				if(S[i]==0)
//				{
//					i_SumIndexArry+=(2*i+1);
//				}
//			}
//
//			if(i_SumIndexArry==0)
//			{
//				Line_status = LINE_OFF; // khong bat line
//			}
//			else
//			{
//				Line_status = LINE_START; // bat duoc line
//			}
//
//			switch(Line_status)
//			{
//				case LINE_OFF:
//				{
//					demoutline+=1;
//					if(demoutline==20)    // out time line -> nhan lai tri tri truoc khi out
//					{
//							demtimeout+=1;
//							vitri=previtri;
//							Control_vitri_Line(vitri);
//							Line_status = LINE_START;
//							demoutline=0;
//					}
//
//					break;
//				}
//				case LINE_START:
//				{
//					Control_Value_Line(i_SumIndexArry);
//					break;
//				}
//			}
//			presumindex=i_SumIndexArry;
//			i_SumIndexArry=0;
//
//		}
//		else if(mode ==2)
//		{
//			CONTROL();
//		}
//		else if(mode == 3 || mode == 0)
//		{
//			__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);
//			__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);
//		}
//	}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	
//	if(huart->Instance == huart1.Instance)
//	{
//	switch(my_state)
//	{
//		case UART_START:
//			{
//			if (Rx_buff[0] == 's' )  // khi nhan nut start de bat dau
//				{
//					i++;
//					my_state = UART_APP;
//					HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
//					break;
//				}
//			else if (Rx_buff[0] == '1' )  // khi nhan nut stop
//				{
//					my_state = UART_START;
//					HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
//					break;
//				}
//			}
//		case UART_APP:
//			{
//			HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx_buff,1);
//			if (Rx_buff[0] == 'f' || Rx_buff[0] == 'b' || Rx_buff[0] == 'r'||Rx_buff[0] == 'l')  // khi o che do dieu khien tay
//				{
//				mode = 2;  // control
//				my_state = UART_APP;
//				HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
//				}
//				else if (Rx_buff[0] =='i')
//				{
//					mode = 3;
//				}
//				else if (Rx_buff[0] == 'd' ) // bat che do do line
//				{
//					mode = 1;  // che do do line
//					HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
//					my_state = UART_APP;
//				}
//			else if(Rx_buff[0] == 'k'  ) // tat che do do line
//				{
//					mode =0;
//					HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
//					my_state = UART_APP;
//				}
//			break;
//				}
//			}
//		}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_DMA_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim3);
  HAL_UART_Receive_DMA(&huart1,Rx_buff,1);


  motor_init();
  motor_set_speed(MOTOR_0, 100);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		/*	
						}*/
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
