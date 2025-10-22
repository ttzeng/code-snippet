#ifndef LED_BLACK_PILL_HPP
#define LED_BLACK_PILL_HPP

#include "led.hpp"

class Led_Stm32_BlackPill : public Led {
  public:
    explicit Led_Stm32_BlackPill();
    ~Led_Stm32_BlackPill();
  protected:
    virtual void set_state(bool state);
    virtual bool get_state() const;
};

#endif // LED_BLACK_PILL_HPP
