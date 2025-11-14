#ifndef TOUCH_SCREEN_XPT2046_HPP
#define TOUCH_SCREEN_XPT2046_HPP

#include "ts.hpp"

// XPT2046 Control byte commands
#define XPT2046_START_BIT   0x80

// Channel selection
#define XPT2046_X_POSITION  0x50  // Single-ended, measure X
#define XPT2046_Y_POSITION  0x10  // Single-ended, measure Y
#define XPT2046_Z1_POSITION 0x30  // Single-ended, measure Z1
#define XPT2046_Z2_POSITION 0x40  // Single-ended, measure Z2

// Differential mode
#define XPT2046_DIFF_X      0xD0  // Differential mode X
#define XPT2046_DIFF_Y      0x90  // Differential mode Y

// Power down modes
#define XPT2046_PD_IRQ_ON   0x00  // Power down, IRQ enabled
#define XPT2046_PD_IRQ_OFF  0x01  // Power down, IRQ disabled

// Touch threshold (adjust based on your screen)
#define XPT2046_TOUCH_THRESHOLD 250

class touch_screen_xpt2046 : public touch_screen {
  public:
    explicit touch_screen_xpt2046(uint16_t width, uint16_t height);
    virtual bool read(int& x, int& y);
    void calibrate(uint16_t Xmin, uint16_t Xmax, uint16_t Ymin, uint16_t Ymax);
  protected:
    virtual bool is_touched() = 0;
    virtual uint16_t read_channel(uint8_t command) = 0;
    virtual void mdelay(uint32_t msec) = 0;
    uint16_t x_min;
    uint16_t x_max;
    uint16_t y_min;
    uint16_t y_max;
};

#endif  // TOUCH_SCREEN_XPT2046_HPP
