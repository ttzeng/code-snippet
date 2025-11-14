#ifndef TFT_SY_TFT240_BLACK_PILL_HPP
#define TFT_SY_TFT240_BLACK_PILL_HPP

#include "tft-ili9325c.hpp"

// Display dimensions
#define SY_TFT240_WIDTH             240
#define SY_TFT240_HEIGHT            320

class tft_sytft240_blackpill : public tft_ili9325c {
  public:
    explicit tft_sytft240_blackpill();
  protected:
    void STM32_GPIO_Init(void);
    virtual void _CS(bool on);
    virtual void _RS(bool on);
    virtual void _WR(bool on);
    virtual void _RD(bool on);
    virtual void _RST(bool on);
    virtual void _OUT(uint16_t v);
    virtual void mdelay(uint32_t msec);
};

#endif  // TFT_SY_TFT240_BLACK_PILL_HPP
