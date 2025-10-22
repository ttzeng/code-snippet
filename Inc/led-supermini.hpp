#ifndef LED_SUPER_MINI_HPP
#define LED_SUPER_MINI_HPP

#include "driver/gpio.h"
#include "led.hpp"

class Led_Esp32c3_SuperMini : public Led {
  public:
    Led_Esp32c3_SuperMini(gpio_num_t pin);
    ~Led_Esp32c3_SuperMini();
  protected:
    virtual void set_state(bool state);
    virtual bool get_state() const;
  private:
    gpio_num_t led_pin;
};

#endif // LED_SUPER_MINI_HPP
