#include "led-blackpill.hpp"
#include "stm32f1xx_hal.h"

#define LED_PORT    GPIOB
#define LED_PIN     GPIO_PIN_12

Led_Stm32_BlackPill::Led_Stm32_BlackPill()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

Led_Stm32_BlackPill::~Led_Stm32_BlackPill()
{
}

void Led_Stm32_BlackPill::set_state(bool state)
{
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, (GPIO_PinState)state);
}

bool Led_Stm32_BlackPill::get_state() const
{
    return HAL_GPIO_ReadPin(LED_PORT, LED_PIN);
}
