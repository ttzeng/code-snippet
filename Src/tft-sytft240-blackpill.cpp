#include "stm32f1xx_hal.h"
#include "tft-sytft240-blackpill.hpp"

// Pin definitions for parallel interface
#define LCD_CS_PORT     GPIOB
#define LCD_CS_PIN      GPIO_PIN_0

#define LCD_RS_PORT     GPIOB
#define LCD_RS_PIN      GPIO_PIN_1

#define LCD_WR_PORT     GPIOB
#define LCD_WR_PIN      GPIO_PIN_10

#define LCD_RD_PORT     GPIOB
#define LCD_RD_PIN      GPIO_PIN_11

#define LCD_RST_PORT    GPIOA
#define LCD_RST_PIN     GPIO_PIN_8

// Data bus pins (PA0-PA7 for 8-bit data)
#define LCD_DATA_PORT   GPIOA
#define LCD_DATA_PINS   (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7)

tft_sytft240_blackpill::tft_sytft240_blackpill()
    : tft_ili9325c(SY_TFT240_WIDTH, SY_TFT240_HEIGHT)
{
    STM32_GPIO_Init();
    ILI9325C_Init();
}

void tft_sytft240_blackpill::STM32_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure data pins (PA0-PA7) as outputs
    GPIO_InitStruct.Pin = LCD_DATA_PINS;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_DATA_PORT, &GPIO_InitStruct);

    // Configure control pins as outputs
    GPIO_InitStruct.Pin = LCD_CS_PIN;
    HAL_GPIO_Init(LCD_CS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_RS_PIN;
    HAL_GPIO_Init(LCD_RS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_WR_PIN;
    HAL_GPIO_Init(LCD_WR_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_RD_PIN;
    HAL_GPIO_Init(LCD_RD_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_RST_PIN;
    HAL_GPIO_Init(LCD_RST_PORT, &GPIO_InitStruct);

    // Set initial states
    _CS(1);
    _RS(1);
    _WR(1);
    _RD(1);
    _RST(1);
}

void tft_sytft240_blackpill::_CS(bool on)
{
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, on? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void tft_sytft240_blackpill::_RS(bool on)
{
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, on? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void tft_sytft240_blackpill::_WR(bool on)
{
    HAL_GPIO_WritePin(LCD_WR_PORT, LCD_WR_PIN, on? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void tft_sytft240_blackpill::_RD(bool on)
{
    HAL_GPIO_WritePin(LCD_RD_PORT, LCD_RD_PIN, on? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void tft_sytft240_blackpill::_RST(bool on)
{
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, on? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void tft_sytft240_blackpill::_OUT(uint16_t v)
{
    // Write high byte
    GPIOA->ODR = (GPIOA->ODR & 0xFF00) | ((v >> 8) & 0xFF);
    HAL_GPIO_WritePin(LCD_WR_PORT, LCD_WR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_WR_PORT, LCD_WR_PIN, GPIO_PIN_SET);

    // Write low byte
    GPIOA->ODR = (GPIOA->ODR & 0xFF00) | (v & 0xFF);
    HAL_GPIO_WritePin(LCD_WR_PORT, LCD_WR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_WR_PORT, LCD_WR_PIN, GPIO_PIN_SET);
}

void tft_sytft240_blackpill::mdelay(uint32_t msec)
{
    HAL_Delay(msec);
}
