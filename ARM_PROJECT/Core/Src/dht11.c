/*
 * dht11.c
 *
 *  Created on: Dec 22, 2025
 *      Author: Administrator
 */
/*
 * dht11.c
 *
 *  Created on: Dec 22, 2025
 *      Author: Administrator
 */
#include "dht11.h"

/* ---------------- DWT delay ---------------- */

static void DWT_Delay_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
}

static void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = (SystemCoreClock / 1000000) * us;
    while ((DWT->CYCCNT - start) < ticks);
}

/* ---------------- GPIO control ---------------- */

static void DHT11_Pin_Output(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;   // ✅ REQUIRED
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

static void DHT11_Pin_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;   // ✅ REQUIRED
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

/* ---------------- Init ---------------- */

void DHT11_Init(void)
{
    DWT_Delay_Init();
}

/* ---------------- Safe wait function ---------------- */

static uint8_t DHT11_WaitForPin(GPIO_PinState state, uint32_t timeout_us)
{
    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) != state)
    {
        if (timeout_us-- == 0)
            return 1;   // timeout
        delay_us(1);
    }
    return 0;
}

/* ---------------- Read byte ---------------- */

static uint8_t DHT11_ReadByte(uint8_t *byte)
{
    uint8_t i;
    *byte = 0;

    for (i = 0; i < 8; i++)
    {
        if (DHT11_WaitForPin(GPIO_PIN_SET, 100)) return 1;
        delay_us(40);

        if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
            *byte |= (1 << (7 - i));

        if (DHT11_WaitForPin(GPIO_PIN_RESET, 100)) return 1;
    }
    return 0;
}

/* ---------------- Main read ---------------- */

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity)
{
    uint8_t data[5] = {0};

    /* Start signal */
    DHT11_Pin_Output();
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
    HAL_Delay(18);

    DHT11_Pin_Input();
    delay_us(30);

    /* Sensor response */
    if (DHT11_WaitForPin(GPIO_PIN_RESET, 100)) return 1;
    if (DHT11_WaitForPin(GPIO_PIN_SET, 100))   return 2;
    if (DHT11_WaitForPin(GPIO_PIN_RESET, 100)) return 3;

    /* Read data */
    for (uint8_t i = 0; i < 5; i++)
        if (DHT11_ReadByte(&data[i])) return 4;

    /* Checksum */
    if ((data[0] + data[1] + data[2] + data[3]) != data[4])
        return 5;

    *humidity = data[0];
    *temperature = data[2];

    return 0;   // ✅ SUCCESS
}
