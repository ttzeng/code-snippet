#ifndef TFT_ST7735_SUPER_MINI_HPP
#define TFT_ST7735_SUPER_MINI_HPP

#include "driver/spi_master.h"
#include "tft-st7735.hpp"

class tft_st7735_supermini : public tft_st7735 {
  public:
    explicit tft_st7735_supermini(spi_host_device_t spi_host, int pin_cs, int pin_sck, int pin_mosi, int pin_dc, int pin_rst,
                                  uint8_t rotation = ST7735_ROTATION_0);
    ~tft_st7735_supermini();
    virtual tft& fill(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
  protected:
    virtual void ST7735_WriteCommand(uint8_t cmd);
    virtual void ST7735_WriteData(uint8_t data);
    virtual void ST7735_WriteData(uint8_t *data, uint16_t len);
    virtual void _RST(bool state);
    virtual void _DC(bool state);
    virtual void _CS(bool state);
    virtual void mdelay(uint32_t msec);
    spi_host_device_t spi_host;
    spi_device_handle_t spi;
    int pin_dc;
    int pin_reset;
};

#endif  // TFT_ST7735_SUPER_MINI_HPP
