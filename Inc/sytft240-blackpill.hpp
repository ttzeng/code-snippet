#ifndef SY_TFT240_BLACK_PILL_HPP
#define SY_TFT240_BLACK_PILL_HPP

#include "sytft240.hpp"

class sytft240_Stm32_BlackPill : public sytft240 {
  public:
    explicit sytft240_Stm32_BlackPill(mdelay_func mdelay);
    ~sytft240_Stm32_BlackPill();
  protected:
    void STM32_GPIO_Init(void);
    virtual void _CS(bool on);
    virtual void _RS(bool on);
    virtual void _WR(bool on);
    virtual void _RD(bool on);
    virtual void _RST(bool on);
    virtual void _OUT(uint16_t v);
};

#endif // SY_TFT240_BLACK_PILL_HPP
