#include "tft-st7735-blackpill.hpp"

tft_st7735_blackpill::tft_st7735_blackpill(SPI_HandleTypeDef *hspi, uint8_t rotation)
{
    st7735_spi = hspi;
    STM32_GPIO_Init();
    ST7735_Init();
    ST7735_SetRotation(rotation);
}

tft& tft_st7735_blackpill::fill(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    if (x >= 0 && x < ST7735_WIDTH && y >= 0 && y < ST7735_HEIGHT) {
        ST7735_SetAddressWindow(x, y, x + width - 1, y + height - 1);
        uint32_t pixels = width * height;
        uint8_t colorBytes[2] = {color >> 8, color & 0xff};
        _DC(1);
        _CS(0);
        for (uint32_t i = 0; i < pixels; i++) {
            HAL_SPI_Transmit(st7735_spi, colorBytes, 2, HAL_MAX_DELAY);
        }
        _CS(1);
    }
    return *this;
}

void tft_st7735_blackpill::STM32_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*Configure GPIO pins : PA2(DC) PA3(RST) PA4(CS) */
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void tft_st7735_blackpill::ST7735_WriteCommand(uint8_t cmd)
{
    _DC(0);
    _CS(0);
    HAL_SPI_Transmit(st7735_spi, &cmd, 1, HAL_MAX_DELAY);
    _CS(1);
}

void tft_st7735_blackpill::ST7735_WriteData(uint8_t *data, uint16_t len)
{
    _DC(1);
    _CS(0);
    HAL_SPI_Transmit(st7735_spi, data, len, HAL_MAX_DELAY);
    _CS(1);
}

void tft_st7735_blackpill::ST7735_WriteData(uint8_t data)
{
    ST7735_WriteData(&data, 1);
}

void tft_st7735_blackpill::_RST(bool state)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, state? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void tft_st7735_blackpill::_DC(bool state)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, state? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void tft_st7735_blackpill::_CS(bool state)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, state? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void tft_st7735_blackpill::mdelay(uint32_t msec)
{
    HAL_Delay(msec);
}
