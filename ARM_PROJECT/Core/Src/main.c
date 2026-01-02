/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "dht11.h"	`
#include "mq2.h"
#include "lcd.h"
#include "buzzer.h"
#include <stdio.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc2;
I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
volatile uint8_t timer_flag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_ADC2_Init(void);
static void MX_TIM2_Init(void);
void Timer_Delay(uint32_t seconds);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        timer_flag = 1;
    }
}

/* HARDWARE TIMER DELAY */
void Timer_Delay(uint32_t seconds)
{
    while (seconds--)
    {
        timer_flag = 0;
        while (!timer_flag);
    }
}

/* -------------------------------------------------------------------------- */
int main(void)
{
    uint8_t temp, hum;
    uint32_t adc_value;
    char buf[16];
    char lcd_buf[16];

    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_ADC2_Init();
    MX_TIM2_Init();
    lcd16x2_i2c_init(&hi2c1);
    DHT11_Init();
    HAL_Delay(1000);


    /* START TIMER INTERRUPT */
    HAL_TIM_Base_Start_IT(&htim2);

    while (1)
    {

        lcd16x2_i2c_clear();
        lcd16x2_i2c_setCursor(0, 0);
        lcd16x2_i2c_printf("DHT11 Ready");
        Timer_Delay(1);


        if (DHT11_Read(&temp, &hum) == 0)
        {
            lcd16x2_i2c_clear();
            lcd16x2_i2c_setCursor(0, 0);
            sprintf(buf, "Temp:%d C", temp);
            lcd16x2_i2c_printf(buf);

            lcd16x2_i2c_setCursor(1, 0);
            sprintf(buf, "Hum :%d %%", hum);
            lcd16x2_i2c_printf(buf);
        }
        else
        {
            lcd16x2_i2c_clear();
            lcd16x2_i2c_setCursor(0, 0);
            lcd16x2_i2c_printf("DHT11 Error");
        }

        Timer_Delay(2);


        lcd16x2_i2c_clear();
        lcd16x2_i2c_setCursor(0, 0);
        lcd16x2_i2c_printf("MQ2 Ready");
        Timer_Delay(1);


        adc_value = MQ2_ReadADC();

        lcd16x2_i2c_clear();
        lcd16x2_i2c_setCursor(0, 0);
        sprintf(lcd_buf, "Gas ADC:%lu", adc_value);
        lcd16x2_i2c_printf(lcd_buf);

        lcd16x2_i2c_setCursor(1, 0);
        lcd16x2_i2c_printf(MQ2_GetAirStatus(adc_value));

        buzzer_Handle(adc_value);

        Timer_Delay(2);
    }
}



static void MX_ADC2_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    hadc2.Instance = ADC2;
    hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc2.Init.Resolution = ADC_RESOLUTION_12B;
    hadc2.Init.ScanConvMode = DISABLE;
    hadc2.Init.ContinuousConvMode = DISABLE;
    hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc2.Init.NbrOfConversion = 1;
    HAL_ADC_Init(&hadc2);

    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(&hadc2, &sConfig);
}

static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    HAL_I2C_Init(&hi2c1);
}

static void MX_TIM2_Init(void)
{
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 49999;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 999;
    HAL_TIM_Base_Init(&htim2);
}

static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;

  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 |
                                RCC_CLOCKTYPE_PCLK2;

  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
}
