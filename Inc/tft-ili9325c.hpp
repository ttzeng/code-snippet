#ifndef TFT_ILI9325C_HPP
#define TFT_ILI9325C_HPP

#include "tft.hpp"

// ILI9325C register definitions
#define ILI9325_START_OSC           0x00
#define ILI9325_DRIV_OUT_CTRL       0x01
#define ILI9325_DRIV_WAV_CTRL       0x02
#define ILI9325_ENTRY_MOD           0x03
#define ILI9325_RESIZE_CTRL         0x04
#define ILI9325_DISP_CTRL1          0x07
#define ILI9325_DISP_CTRL2          0x08
#define ILI9325_DISP_CTRL3          0x09
#define ILI9325_DISP_CTRL4          0x0A
#define ILI9325_RGB_DISP_IF_CTRL1   0x0C
#define ILI9325_FRM_MARKER_POS      0x0D
#define ILI9325_RGB_DISP_IF_CTRL2   0x0F
#define ILI9325_POW_CTRL1           0x10
#define ILI9325_POW_CTRL2           0x11
#define ILI9325_POW_CTRL3           0x12
#define ILI9325_POW_CTRL4           0x13
#define ILI9325_GRAM_HOR_AD         0x20
#define ILI9325_GRAM_VER_AD         0x21
#define ILI9325_RW_GRAM             0x22
#define ILI9325_POW_CTRL7           0x29
#define ILI9325_FRM_RATE_COL_CTRL   0x2B
#define ILI9325_GAMMA_CTRL1         0x30
#define ILI9325_GAMMA_CTRL2         0x31
#define ILI9325_GAMMA_CTRL3         0x32
#define ILI9325_GAMMA_CTRL4         0x35
#define ILI9325_GAMMA_CTRL5         0x36
#define ILI9325_GAMMA_CTRL6         0x37
#define ILI9325_GAMMA_CTRL7         0x38
#define ILI9325_GAMMA_CTRL8         0x39
#define ILI9325_GAMMA_CTRL9         0x3C
#define ILI9325_GAMMA_CTRL10        0x3D
#define ILI9325_HOR_START_AD        0x50
#define ILI9325_HOR_END_AD          0x51
#define ILI9325_VER_START_AD        0x52
#define ILI9325_VER_END_AD          0x53
#define ILI9325_GATE_SCAN_CTRL1     0x60
#define ILI9325_GATE_SCAN_CTRL2     0x61
#define ILI9325_GATE_SCAN_CTRL3     0x6A
#define ILI9325_PART_IMG1_DISP_POS  0x80
#define ILI9325_PART_IMG1_START_AD  0x81
#define ILI9325_PART_IMG1_END_AD    0x82
#define ILI9325_PART_IMG2_DISP_POS  0x83
#define ILI9325_PART_IMG2_START_AD  0x84
#define ILI9325_PART_IMG2_END_AD    0x85
#define ILI9325_PANEL_IF_CTRL1      0x90
#define ILI9325_PANEL_IF_CTRL2      0x92
#define ILI9325_PANEL_IF_CTRL3      0x93
#define ILI9325_PANEL_IF_CTRL4      0x95
#define ILI9325_PANEL_IF_CTRL5      0x97
#define ILI9325_PANEL_IF_CTRL6      0x98

class tft_ili9325c : public tft {
  public:
    explicit tft_ili9325c(uint16_t width, uint16_t height) : tft(width, height) {};
    virtual tft& pixel(int16_t x, int16_t y, uint16_t color);
    virtual tft& clear(uint16_t color);
  protected:
    void ILI9325C_Init(mdelay_func mdelay);
    void ILI9325C_WriteReg(uint16_t reg, uint16_t data);
    virtual void _CS(bool on) = 0;
    virtual void _RS(bool on) = 0;
    virtual void _WR(bool on) = 0;
    virtual void _RD(bool on) = 0;
    virtual void _RST(bool on) = 0;
    virtual void _OUT(uint16_t v) = 0;
};

#endif  // TFT_ILI9325C_HPP
