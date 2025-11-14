#ifndef TOUCH_SCREEN_HPP
#define TOUCH_SCREEN_HPP

#include "stdbool.h"
#include "stdint.h"

class touch_screen {
  public:
    explicit touch_screen(uint16_t width, uint16_t height)
        { screen_width = width, screen_height = height; };
    virtual bool read(int& x, int& y) = 0;
  protected:
    uint16_t screen_width;
    uint16_t screen_height;
};

#endif  // TOUCH_SCREEN_HPP
