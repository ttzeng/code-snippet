#include "tft-ili9325c.hpp"

tft& tft_ili9325c::pixel(int16_t x, int16_t y, uint16_t color)
{
    if (x >= 0 && x < display_width && y >= 0 && y && display_height) {
        ILI9325C_WriteReg(ILI9325_GRAM_HOR_AD, x);
        ILI9325C_WriteReg(ILI9325_GRAM_VER_AD, y);
        ILI9325C_WriteReg(ILI9325_RW_GRAM, color);
    }
    return *this;
}

tft& tft_ili9325c::clear(uint16_t color)
{
    ILI9325C_WriteReg(ILI9325_GRAM_HOR_AD, 0);
    ILI9325C_WriteReg(ILI9325_GRAM_VER_AD, 0);

    // Select chip and set to command mode for register address
    _CS(0);
    _RS(0);
    _OUT(ILI9325_RW_GRAM);

    _RS(1);     // Switch to data mode for continuous data writes
    for (uint32_t i = 0; i < display_width * display_height; i++) {
        _OUT(color);
    }
    _CS(1);
    return *this;
}

void tft_ili9325c::ILI9325C_Init(mdelay_func mdelay)
{
    // Reset display
    _RST(0);
    mdelay(50);
    _RST(1);
    mdelay(120);

    // Initial register setup
    ILI9325C_WriteReg(0x00E3, 0x3008);
    ILI9325C_WriteReg(0x00E7, 0x0012);
    ILI9325C_WriteReg(0x00EF, 0x1231);
    ILI9325C_WriteReg(0x00E7, 0x0010);

    // Power control
    ILI9325C_WriteReg(ILI9325_POW_CTRL1, 0x0000);
    ILI9325C_WriteReg(ILI9325_POW_CTRL2, 0x0007);
    ILI9325C_WriteReg(ILI9325_POW_CTRL3, 0x0000);
    ILI9325C_WriteReg(ILI9325_POW_CTRL4, 0x0000);
    mdelay(200);

    ILI9325C_WriteReg(ILI9325_POW_CTRL1, 0x1690);
    ILI9325C_WriteReg(ILI9325_POW_CTRL2, 0x0227);
    mdelay(50);

    ILI9325C_WriteReg(ILI9325_POW_CTRL3, 0x001A);
    mdelay(50);

    ILI9325C_WriteReg(ILI9325_POW_CTRL4, 0x1800);
    ILI9325C_WriteReg(ILI9325_POW_CTRL7, 0x002A);
    mdelay(50);

    // Gamma correction
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL1, 0x0000);
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL2, 0x0000);
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL3, 0x0000);
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL4, 0x0206);
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL5, 0x0808);
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL6, 0x0007);
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL7, 0x0201);
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL8, 0x0000);
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL9, 0x0000);
    ILI9325C_WriteReg(ILI9325_GAMMA_CTRL10, 0x0000);

    // Display settings
    ILI9325C_WriteReg(ILI9325_DRIV_OUT_CTRL, 0x0100);
    ILI9325C_WriteReg(ILI9325_DRIV_WAV_CTRL, 0x0700);
    ILI9325C_WriteReg(ILI9325_ENTRY_MOD, 0x1030);
    ILI9325C_WriteReg(ILI9325_RESIZE_CTRL, 0x0000);
    ILI9325C_WriteReg(ILI9325_DISP_CTRL2, 0x0202);
    ILI9325C_WriteReg(ILI9325_DISP_CTRL3, 0x0000);
    ILI9325C_WriteReg(ILI9325_DISP_CTRL4, 0x0000);
    ILI9325C_WriteReg(ILI9325_RGB_DISP_IF_CTRL1, 0x0000);
    ILI9325C_WriteReg(ILI9325_FRM_MARKER_POS, 0x0000);
    ILI9325C_WriteReg(ILI9325_RGB_DISP_IF_CTRL2, 0x0000);

    // Panel control
    ILI9325C_WriteReg(ILI9325_PANEL_IF_CTRL1, 0x0010);
    ILI9325C_WriteReg(ILI9325_PANEL_IF_CTRL2, 0x0000);
    ILI9325C_WriteReg(ILI9325_PANEL_IF_CTRL3, 0x0003);
    ILI9325C_WriteReg(ILI9325_PANEL_IF_CTRL4, 0x1100);
    ILI9325C_WriteReg(ILI9325_PANEL_IF_CTRL5, 0x0000);
    ILI9325C_WriteReg(ILI9325_PANEL_IF_CTRL6, 0x0000);

    // Display on
    ILI9325C_WriteReg(ILI9325_DISP_CTRL1, 0x0133);

    // Set display area
    ILI9325C_WriteReg(ILI9325_HOR_START_AD, 0x0000);
    ILI9325C_WriteReg(ILI9325_HOR_END_AD, 0x00EF);
    ILI9325C_WriteReg(ILI9325_VER_START_AD, 0x0000);
    ILI9325C_WriteReg(ILI9325_VER_END_AD, 0x013F);

    ILI9325C_WriteReg(ILI9325_GATE_SCAN_CTRL1, 0xA700);
    ILI9325C_WriteReg(ILI9325_GATE_SCAN_CTRL2, 0x0003);
    ILI9325C_WriteReg(ILI9325_GATE_SCAN_CTRL3, 0x0000);

    ILI9325C_WriteReg(ILI9325_PART_IMG1_DISP_POS, 0x0000);
    ILI9325C_WriteReg(ILI9325_PART_IMG1_START_AD, 0x0000);
    ILI9325C_WriteReg(ILI9325_PART_IMG1_END_AD, 0x0000);
    ILI9325C_WriteReg(ILI9325_PART_IMG2_DISP_POS, 0x0000);
    ILI9325C_WriteReg(ILI9325_PART_IMG2_START_AD, 0x0000);
    ILI9325C_WriteReg(ILI9325_PART_IMG2_END_AD, 0x0000);
}

void tft_ili9325c::ILI9325C_WriteReg(uint16_t reg, uint16_t data)
{
    _CS(0);     // Select LCD
    _RS(0);     // Command mode
    _OUT(reg);

    _RS(1);     // Data mode
    _OUT(data);
    _CS(1);     // Deselect LCD
}
