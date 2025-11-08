#ifndef TFT_ST7735_HPP
#define TFT_ST7735_HPP

#include "tft.hpp"

// Screen dimensions
#define ST7735_WIDTH        160
#define ST7735_HEIGHT       128

// ST7735 Commands
#define ST7735_NOP          0x00
#define ST7735_SWRESET      0x01
#define ST7735_RDDID        0x04
#define ST7735_RDDST        0x09
#define ST7735_SLPIN        0x10
#define ST7735_SLPOUT       0x11
#define ST7735_PTLON        0x12
#define ST7735_NORON        0x13
#define ST7735_INVOFF       0x20
#define ST7735_INVON        0x21
#define ST7735_DISPOFF      0x28
#define ST7735_DISPON       0x29
#define ST7735_CASET        0x2A
#define ST7735_RASET        0x2B
#define ST7735_RAMWR        0x2C
#define ST7735_RAMRD        0x2E
#define ST7735_PTLAR        0x30
#define ST7735_COLMOD       0x3A
#define ST7735_MADCTL       0x36
#define ST7735_FRMCTR1      0xB1
#define ST7735_FRMCTR2      0xB2
#define ST7735_FRMCTR3      0xB3
#define ST7735_INVCTR       0xB4
#define ST7735_DISSET5      0xB6
#define ST7735_PWCTR1       0xC0
#define ST7735_PWCTR2       0xC1
#define ST7735_PWCTR3       0xC2
#define ST7735_PWCTR4       0xC3
#define ST7735_PWCTR5       0xC4
#define ST7735_VMCTR1       0xC5
#define ST7735_RDID1        0xDA
#define ST7735_RDID2        0xDB
#define ST7735_RDID3        0xDC
#define ST7735_RDID4        0xDD
#define ST7735_PWCTR6       0xFC
#define ST7735_GMCTRP1      0xE0
#define ST7735_GMCTRN1      0xE1

// Rotation definitions
#define ST7735_ROTATION_0   0
#define ST7735_ROTATION_90  1
#define ST7735_ROTATION_180 2
#define ST7735_ROTATION_270 3

class tft_st7735 : public tft {
  public:
    explicit tft_st7735() : tft(ST7735_HEIGHT, ST7735_WIDTH) {};
    virtual tft& pixel(int16_t x, int16_t y, uint16_t color);
  protected:
    void ST7735_Init(mdelay_func mdelay);
    void ST7735_SetAddressWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void ST7735_SetRotation(uint8_t rotation);
    virtual void ST7735_WriteCommand(uint8_t cmd) = 0;
    virtual void ST7735_WriteData(uint8_t data) = 0;
    virtual void ST7735_WriteData(uint8_t *data, uint16_t len) = 0;
    virtual void _RST(bool state) = 0;
    virtual void _DC(bool state) = 0;
    virtual void _CS(bool state) = 0;
};

#endif // TFT_ST7735_HPP
