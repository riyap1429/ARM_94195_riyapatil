/*
 * ext_intr.c
 *
 *  Created on: Dec 18, 2025
 *      Author: kiran_z6dopa8
 */
#include "stm32f4xx.h"
#include "ext_intr.h"

volatile int ext_flag = 0;     // Interrupt event flag
volatile int led_state = 0;    // ⭐ NEW: LED state (0=OFF, 1=ON)

void extint_init(void)
{
    RCC->AHB1ENR |= (1 << 0);     // GPIOA clock
    RCC->APB2ENR |= (1 << 14);    // SYSCFG clock

    GPIOA->MODER &= ~(3 << 0);    // PA0 input

    SYSCFG->EXTICR[0] &= ~(0xF << 0);  // PA0 -> EXTI0

    EXTI->FTSR |= (1 << 0);       // Falling edge trigger
    EXTI->IMR  |= (1 << 0);       // Unmask EXTI0

    NVIC_EnableIRQ(EXTI0_IRQn);   // Enable interrupt
}

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1 << 0))
    {
        EXTI->PR |= (1 << 0);     // Clear pending bit
        ext_flag = 1;             // Signal main()
    }
}
