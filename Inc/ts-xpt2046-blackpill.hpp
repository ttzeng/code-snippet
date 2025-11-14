#ifndef TOUCH_SCREEN_XPT2046_BLACK_PILL_HPP
#define TOUCH_SCREEN_XPT2046_BLACK_PILL_HPP

#include "ts-xpt2046.hpp"
#include "stm32f1xx_hal.h"

class touch_screen_xpt2046_blackpill : public touch_screen_xpt2046 {
  public:
    explicit touch_screen_xpt2046_blackpill(uint16_t width, uint16_t height, SPI_HandleTypeDef *hspi);
  protected:
    void STM32_GPIO_Init();
    virtual bool is_touched();
    virtual uint16_t read_channel(uint8_t command);
    virtual void mdelay(uint32_t msec);
    SPI_HandleTypeDef *ts_spi;
};

#endif  // TOUCH_SCREEN_XPT2046_BLACK_PILL_HPP
