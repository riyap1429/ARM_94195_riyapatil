/*
 * mq2.c
 *
 *  Created on: Dec 31, 2025
 *      Author: HP
 */
#include "mq2.h"

extern ADC_HandleTypeDef hadc2;

uint32_t MQ2_ReadADC(void)
{
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
    uint32_t value = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);
    return value;
}

const char* MQ2_GetAirStatus(uint32_t adc_value)
{
    if (adc_value < AIR_GOOD_MAX)
        return "AIR: GOOD     ";
    else if (adc_value < AIR_MODERATE_MAX)
        return "AIR: MODERATE ";
    else
        return "AIR: BAD !!!  ";
}


