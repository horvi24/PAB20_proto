/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "include.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
WS28XX_HandleTypeDef ws;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_TIM1_Init();
  MX_ADC1_Init();
  MX_USART4_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */


  //setup: https://www.youtube.com/watch?v=TBYatUxH6Ek
#define LED_NUMBER 6
#define LED_SIGNAL_POWER 64
  WS28XX_Init(&ws, &htim1, 48, TIM_CHANNEL_2, LED_NUMBER);


  int i = 0;
  int j = 0;
  int c = 0;

  TIM3->CCR4 = 1000;
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

  printf("\r\r  PAB2.0 - Demo 0.1.2 (31.03.26)\r\r  \n");
  LED_WW_ON();
  LED_RS_OFF();
  PWR_HOLD_ON();
  while (PWR_KEY());
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if (PWR_KEY()) {
		  LED_RS_OFF();
		  LED_WW_OFF();

		  for( i = 0; i < 7; i++){
			  WS28XX_SetPixel_RGBW_565(&ws, i, COLOR_RGB565_BLACK, 0);
		  }
		  WS28XX_Update(&ws);
		  printf("\r\r  OFF\n");
		  PWR_HOLD_OFF();
		  while(1);
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  switch(j){
	  	  case 0:
	  		c = COLOR_RGB565_RED;
	  		break;
	  	  case 1:
	  		c = COLOR_RGB565_GREEN;
	  		break;
	  	  case 2:
	  		c = COLOR_RGB565_BLUE;
	  		break;
	  	  case 3:
	  		c = COLOR_RGB565_WHITE;
	  		break;
	  	  case 4:
	  		c = COLOR_RGB565_PURPLE;
	  		break;
	  	  case 5:
	  		c = COLOR_RGB565_CORAL;
	  		break;
	  	  case 6:
	  		c = COLOR_RGB565_GOLD;
	  		break;
	  	  default:
	  		break;
	  }
	  printf("%1d\n", j);
	  if(j == 6) printf("\r  \n");
	  if (j++ > 5) j = 0;

	  WS28XX_SetPixel_RGBW_565(&ws, 0, c, LED_SIGNAL_POWER);

	  for( i = 1; i < 7; i++){
		  HAL_Delay(100);
		  WS28XX_SetPixel_RGBW_565(&ws, i, c, 255);
		  WS28XX_Update(&ws);
	  }
	  for( i = 1; i < 7; i++){
		  HAL_Delay(100);
		  WS28XX_SetPixel_RGBW_565(&ws, i, c, 0);
		  WS28XX_Update(&ws);
	  }
	  LED_RS_TOGGLE();
	  LED_WW_TOGGLE();

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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 12;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
