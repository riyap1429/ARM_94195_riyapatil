/*
 * buzzer.c
 *
 *  Created on: Dec 31, 2025
 *      Author: HP
 */

#include "mq2.h"

// PD12 → Green LED
// PD13 → Orange LED
// PD14 → Red LED
// PD15 → Buzzer

void buzzer_Handle(uint32_t adc_value)
{
    // Turn OFF all
    HAL_GPIO_WritePin(GPIOD,
        GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15,
        GPIO_PIN_RESET);

    if (adc_value < AIR_GOOD_MAX)
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); // Green
    }
    else if (adc_value < AIR_MODERATE_MAX)
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET); // Orange
    }
    else
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET); // Red
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); // Buzzer
    }
}


