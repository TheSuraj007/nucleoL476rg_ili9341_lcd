/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9341_stm32_driver.h"
#include "ili9341_gfx.h"
#include "snow_tiger.h"
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

//SPI_HandleTypeDef hspi1;
//DMA_HandleTypeDef hdma_spi1_tx;
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
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		/* IMAGE EXAMPLE */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		fillRoundRect(10,10,100,100,20,BLUE);
		drawRoundRect(13,13,94,94,20,WHITE);

		while(1);


		ILI9341_DrawText("RGB Picture", FONT3, 10, 10, RED, YELLOW);
		ILI9341_DrawText("TIGER", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_DrawImage(gui_menu, SCREEN_VERTICAL_2);
		ILI9341_SetRotation(SCREEN_VERTICAL_1);
		HAL_Delay(5000);



	  		static uint16_t x = 0;
	  		static uint16_t y = 0;
	  		static char BufferText[40];

	  		ILI9341_FillScreen(WHITE);
	  		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
	  		ILI9341_DrawText("Counting multiple segments at once", FONT2, 10, 10, BLACK, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_FillScreen(WHITE);

	  		for(uint16_t i = 0; i <= 10; i++)
	  		{
	  			sprintf(BufferText, "Counting: %d", i);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 10, BLACK, WHITE);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 30, BLUE, WHITE);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 50, RED, WHITE);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 70, GREEN, WHITE);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 90, BLACK, WHITE);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 110, BLUE, WHITE);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 130, RED, WHITE);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 150, GREEN, WHITE);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 170, WHITE, BLACK);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 190, BLUE, BLACK);
	  			ILI9341_DrawText(BufferText, FONT3, 10, 210, RED, BLACK);
	  		}
	  		HAL_Delay(1000);

	  		/* COUNTING SINGLE SEGMENT */
	  		ILI9341_FillScreen(WHITE);
	  		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
	  		ILI9341_DrawText("Counting single segment", FONT3, 10, 10, BLACK, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_FillScreen(WHITE);

	  		for(uint16_t i = 0; i <= 100; i++)
	  		{
	  			sprintf(BufferText, "Counting: %d", i);
	  			ILI9341_DrawText(BufferText, FONT4, 10, 10, BLACK, WHITE);
	  			HAL_Delay(10);
	  		}
	  		HAL_Delay(1000);

	  		/* ALIGNMENT TEST */
	  		ILI9341_FillScreen(WHITE);
	  		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
	  		ILI9341_DrawText("Rectangle alignment check", FONT3, 10, 10, BLACK, WHITE);
	  		HAL_Delay(2000);

	  		ILI9341_FillScreen(WHITE);
	  		ILI9341_DrawHollowRectangleCoord(50, 50, 100, 100, BLACK);
	  		ILI9341_DrawFilledRectangleCoord(20, 20, 50, 50, BLACK);
	  		ILI9341_DrawHollowRectangleCoord(10, 10, 19, 19, BLACK);
	  		HAL_Delay(1000);

	  		/* INDIVIDUAL PIXEL EXAMPLE */
	  		ILI9341_FillScreen(WHITE);
	  		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
	  		ILI9341_DrawText("Slow draw by selecting", FONT3, 10, 10, BLACK, WHITE);
	  		ILI9341_DrawText("and adressing pixels", FONT3, 10, 30, BLACK, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_FillScreen(WHITE);

	  		x = 0;
	  		y = 0;

	  		while (y < ILI9341_SCREEN_HEIGHT)
	  		{
	  			while ((x < ILI9341_SCREEN_WIDTH) && (y < ILI9341_SCREEN_HEIGHT))
	  			{
	  				if(x % 2)
	  				{
	  					ILI9341_DrawPixel(x, y, BLACK);
	  				}
	  				x++;
	  			}
	  			y++;
	  			x = 0;
	  		}

	  		x = 0;
	  		y = 0;

	  		while (y < ILI9341_SCREEN_HEIGHT)
	  		{
	  			while ((x < ILI9341_SCREEN_WIDTH) && (y < ILI9341_SCREEN_HEIGHT))
	  			{
	  				if(y % 2)
	  				{
	  					ILI9341_DrawPixel(x, y, BLACK);
	  				}
	  				x++;
	  			}
	  			y++;
	  			x = 0;
	  		}

	  		HAL_Delay(2000);

	  		/* 565 GRAYSCALE EXAMPLE */
	  		ILI9341_FillScreen(WHITE);
	  		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
	  		ILI9341_DrawText("Color gradient", FONT3, 10, 10, BLACK, WHITE);
	  		ILI9341_DrawText("Grayscale", FONT3, 10, 30, BLACK, WHITE);
	  		HAL_Delay(2000);

	  		for(uint16_t i = 0; i <= ILI9341_SCREEN_WIDTH; i++)
	  		{
	  			uint16_t Red = 0;
	  			uint16_t Green = 0;
	  			uint16_t Blue = 0;

	  			Red = i/(10);
	  			Red <<= 11;
	  			Green = i/(5);
	  			Green <<= 5;
	  			Blue = i/(10);

	  			uint16_t RGB = Red + Green + Blue;
	  			ILI9341_DrawRectangle(i, x, 1, 240, RGB);

	  		}
	  		HAL_Delay(2000);



	  		// Horizontal Line (X, Y, Length, Color)
	  		  ILI9341_FillScreen(WHITE);
	  		  ILI9341_DrawHLine(50, 120, 200, NAVY);
	  		  HAL_Delay(1000);

	  		  // Vertical Line (X, Y, Length, Color)
	  		  ILI9341_FillScreen(WHITE);
	  		  ILI9341_DrawVLine(160, 40, 150, DARKGREEN);
	  		  HAL_Delay(1000);

	  		  // Hollow Circle (Centre X, Centre Y, Radius, Color)
	  		  ILI9341_FillScreen(WHITE);
	  		  ILI9341_DrawHollowCircle(160, 120, 80, PINK);
	  		  HAL_Delay(1000);

	  		  // Filled Circle (Centre X, Centre Y, Radius, Color)
	  		  ILI9341_FillScreen(WHITE);
	  		  ILI9341_DrawFilledCircle(160, 120, 50, CYAN);
	  		  HAL_Delay(1000);

	  		  // Filled Rectangle (Start X, Start Y, Length X, Length Y)
	  		  ILI9341_FillScreen(WHITE);
	  		  ILI9341_DrawRectangle(50, 50, 220, 140, GREENYELLOW);
	  		  HAL_Delay(1000);

	  		  // Hollow Rectangle (Start X, Start Y, End X, End Y)
	  		  ILI9341_FillScreen(WHITE);
	  		  ILI9341_DrawHollowRectangleCoord(50, 50, 270, 190, DARKCYAN);
	  		  HAL_Delay(1000);

	  		  // Simple Pixel Only (X, Y, Color)
	  		  ILI9341_FillScreen(WHITE);
	  		  ILI9341_DrawPixel(100, 100, BLACK);
	  		  HAL_Delay(1000);

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
