#ifndef JOYSTICK_SUPER_MINI_HPP
#define JOYSTICK_SUPER_MINI_HPP

#include "joystick.hpp"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"

class joystick_supermini : public joystick {
  public:
    explicit joystick_supermini(adc_channel_t pin_x, adc_channel_t pin_y, gpio_num_t pin_button);
    ~joystick_supermini();
    virtual void read(int& x, int& y, bool& button, int normalized);
  protected:
    gpio_num_t pin_button;
    adc_channel_t pin_x;
    adc_channel_t pin_y;
    adc_oneshot_unit_handle_t adc1_handle;
};

#endif  // JOYSTICK_SUPER_MINI_HPP
