/*
 * mq2.h
 *
 *  Created on: Dec 31, 2025
 *      Author: HP
 */

#ifndef INC_MQ2_H_
#define INC_MQ2_H_

#include "stm32f4xx_hal.h"

// Thresholds (ADC based)
#define AIR_GOOD_MAX       1200
#define AIR_MODERATE_MAX   2500

uint32_t MQ2_ReadADC(void);
const char* MQ2_GetAirStatus(uint32_t adc_value);


#endif /* INC_MQ2_H_ */
