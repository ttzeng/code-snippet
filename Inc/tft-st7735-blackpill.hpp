#ifndef TFT_ST7735_BLACK_PILL_HPP
#define TFT_ST7735_BLACK_PILL_HPP

#include "tft-st7735.hpp"
#include "stm32f1xx_hal.h"

class tft_st7735_blackpill : public tft_st7735 {
  public:
    explicit tft_st7735_blackpill(SPI_HandleTypeDef *hspi, mdelay_func mdelay, uint8_t rotation = ST7735_ROTATION_0);
    virtual tft& fill(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
  protected:
    virtual void STM32_GPIO_Init();
    virtual void ST7735_WriteCommand(uint8_t cmd);
    virtual void ST7735_WriteData(uint8_t data);
    virtual void ST7735_WriteData(uint8_t *data, uint16_t len);
    virtual void _RST(bool state);
    virtual void _DC(bool state);
    virtual void _CS(bool state);
    SPI_HandleTypeDef *st7735_spi;
};

#endif  // TFT_ST7735_BLACK_PILL_HPP
