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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "PID.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t Idle;
float vitri;
int i_SumIndexArry=0;
int i_SumValuteIndexArry=0;
float f_thamchieu=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef enum
	{
			UART_START =0,
			UART_APP = 1,
	}Uart_statemachine;

Uart_statemachine my_state = UART_START;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */
char Rx_buff[25];
char transmit[20];
uint8_t pwm1 = 160;
uint8_t pwm2 = 160;
uint8_t offset = 10;
uint8_t mode = 0;    // 0 : control   , 1: line follow

uint8_t S[4];
float result_PWM;
PID_parameter PID_set_parameters = {.Kp = 25,.Ki=0.06,.Kd=3,.Ts = 0.02,.PID_Saturation = 255
																			,.error =0,.pre_error =0,.pre2_error=0,.pre_Out =0,.Out = 0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void control();
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
/*
PB0  ---> IN4
PB1  ---> IN3
PB10 ---> IN2
PB11 ---> IN1
*/
void move(float motor,float dir)  
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
					else if(dir == 1) 				// cung chieu kim dong ho
						{
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
						}
			 }
			else if (motor == 2)
				{
							__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);
							__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);
				}
	}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)   // ngat 20ms 
	{
			if (htim->Instance == TIM3)
				{
					if (mode ==1)
						{
					S[3] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
					S[2] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
					S[1] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
					S[0] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);
					for(int i=0;i<=3;i++)
						{
							if(S[i]==0)
								{
										i_SumValuteIndexArry+=1;
										i_SumIndexArry+=(i+1);
								}
						}
					f_thamchieu=(float)i_SumIndexArry/i_SumValuteIndexArry;
					i_SumIndexArry=0;
					i_SumValuteIndexArry=0;
					if(f_thamchieu==2){
						vitri=-1.2;
					}else if(f_thamchieu==3){
						vitri=1.2;
					}else if(f_thamchieu==1){
						vitri=-2;
					}else if(f_thamchieu==4){
						vitri=2;
					}else if(f_thamchieu==1.5){
						vitri=-1.5;
					}else if(f_thamchieu ==2.5){
						vitri=0;
					}else if(f_thamchieu==3.5)
					{
						vitri=1.5;
					}	 
					
					result_PWM = PID_PROCESS(&PID_set_parameters,vitri,0);
								
							if (vitri== 0)
										{			
												move(0,1);
												move(1,0);
												__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,200);
												__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,200);
										}
							if (vitri > 0)
										{
												move(0,1);
												move(1,0);
												__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,result_PWM);  //kenh 3 dong co trai
												__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);	
										}
							if (vitri < 0)
										{
												move(0,1);
												move(1,0);
												__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);
												__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,(result_PWM*-1));	
										}
								//if (sensor[0] == 1 && sensor[1] == 0 && sensor[2] == 0 && sensor[3] ==1)
									//	vitri = 0;
			//				}
					}		 
				}
	}
	
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
			if (huart->Instance == USART1)   //state machine
				{		
						switch(my_state)
							{
							case UART_START:    // nhan chuoi voi 3 byte : bat dau,che do ,huong
								{
									if (Rx_buff[0] == 1)  // 1: khi nhan nut start 
										{
												my_state = UART_APP;  //chuyen qua trang thai 2
												HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx_buff,1);
										}
//									if (Rx_buff[0] == 1 )  // 'L':line follow
//											{
//												mode = 1;
//												my_state = UART_APP;
//												HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx_buff,3);
//											}
									else 
										{
												HAL_UART_Transmit(&huart1,(uint8_t*)"Invalid",7,100);
												HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx_buff,1);
										}
									break;
								}
							case UART_APP:
								{
									if (Rx_buff[0] == 'A') // 'A':line follow
										{
											mode = 1;  // thuc hien  do line
										}
									else if (Rx_buff[0] != 'A')
										{
									control();
										}	
									HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx_buff,1);
									//memset(Rx_buff,0,3);   // xoa Rx_buff
									my_state = UART_APP;
									break;
								}	
							}
					HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx_buff,1);

				}
	}
void control()
	{
						switch(Rx_buff[0])
										{
										case 'L':
											{		
													move(0,0);
													move(1,1);
													__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);   //speed of left motor
													__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,180);	// speed of right motor
													break;
											}
										case 'R':
											{
													move(0,0);
													move(1,1);
													__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,180);   //speed of left motor
													__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);	// speed of right motor
														break;
											}
										case 'F':
											{	
													move(0,0);
													move(1,1);
													__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,180);   //speed of left motor
													__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,180);	// speed of right motor
														break;
											}
										case 'B':
											{
													move(0,1);
													move(1,0);
													__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,180);   //speed of left motor
													__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,180);	// speed of right motor
														break;
											}
									}
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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx_buff,3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
	HAL_TIM_Base_Start_IT(&htim3);

	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,160);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,160);
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

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7199;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 200;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 9;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 254;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
