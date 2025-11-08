#include "tft-st7735.hpp"

tft& tft_st7735::pixel(int16_t x, int16_t y, uint16_t color)
{
    if (x >= 0 && x < display_width && y >= 0 && y < display_height) {
        ST7735_SetAddressWindow(x, y, x, y);
        uint8_t c[] = { uint8_t(color >> 8), uint8_t(color & 0xff) };
        ST7735_WriteData(c, sizeof(c));
    }
    return *this;
}

void tft_st7735::ST7735_Init(mdelay_func mdelay)
{
    // Hardware reset
    _RST(1);
    mdelay(5);
    _RST(0);
    mdelay(20);
    _RST(1);
    mdelay(150);

    // Software reset
    ST7735_WriteCommand(ST7735_SWRESET);
    mdelay(150);

    // Out of sleep mode
    ST7735_WriteCommand(ST7735_SLPOUT);
    mdelay(500);

    // Frame rate control - normal mode
    ST7735_WriteCommand(ST7735_FRMCTR1);
    ST7735_WriteData(0x01);
    ST7735_WriteData(0x2c);
    ST7735_WriteData(0x2d);

    // Frame rate control - idle mode
    ST7735_WriteCommand(ST7735_FRMCTR2);
    ST7735_WriteData(0x01);
    ST7735_WriteData(0x2c);
    ST7735_WriteData(0x2d);

    // Frame rate control - partial mode
    ST7735_WriteCommand(ST7735_FRMCTR3);
    ST7735_WriteData(0x01);
    ST7735_WriteData(0x2c);
    ST7735_WriteData(0x2d);
    ST7735_WriteData(0x01);
    ST7735_WriteData(0x2c);
    ST7735_WriteData(0x2d);

    // Display inversion control
    ST7735_WriteCommand(ST7735_INVCTR);
    ST7735_WriteData(0x07);

    // Power control
    ST7735_WriteCommand(ST7735_PWCTR1);
    ST7735_WriteData(0xa2);
    ST7735_WriteData(0x02);
    ST7735_WriteData(0x84);

    ST7735_WriteCommand(ST7735_PWCTR2);
    ST7735_WriteData(0xc5);

    ST7735_WriteCommand(ST7735_PWCTR3);
    ST7735_WriteData(0x0a);
    ST7735_WriteData(0x00);

    ST7735_WriteCommand(ST7735_PWCTR4);
    ST7735_WriteData(0x8a);
    ST7735_WriteData(0x2a);

    ST7735_WriteCommand(ST7735_PWCTR5);
    ST7735_WriteData(0x8a);
    ST7735_WriteData(0xee);

    // VCOM control
    ST7735_WriteCommand(ST7735_VMCTR1);
    ST7735_WriteData(0x0e);

    // Inversion off
    ST7735_WriteCommand(ST7735_INVOFF);

    // Memory access control
    ST7735_WriteCommand(ST7735_MADCTL);
    ST7735_WriteData(0xc0);

    // Color mode: 16-bit
    ST7735_WriteCommand(ST7735_COLMOD);
    ST7735_WriteData(0x05);

    // Gamma correction positive polarity
    uint8_t gmctrp1[] = {0x02, 0x1c, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2d,
                         0x29, 0x25, 0x2b, 0x39, 0x00, 0x01, 0x03, 0x10};
    ST7735_WriteCommand(ST7735_GMCTRP1);
    ST7735_WriteData(gmctrp1, sizeof(gmctrp1));

    // Gamma correction negative polarity
    uint8_t gmctrn1[] = {0x03, 0x1d, 0x07, 0x06, 0x2e, 0x2c, 0x29, 0x2d,
                         0x2e, 0x2e, 0x37, 0x3f, 0x00, 0x00, 0x02, 0x10};
    ST7735_WriteCommand(ST7735_GMCTRN1);
    ST7735_WriteData(gmctrp1, sizeof(gmctrn1));

    // Normal display on
    ST7735_WriteCommand(ST7735_NORON);
    mdelay(10);

    // Display on
    ST7735_WriteCommand(ST7735_DISPON);
    mdelay(100);
}

void tft_st7735::ST7735_SetAddressWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    // Column address set
    ST7735_WriteCommand(ST7735_CASET);
    uint8_t x[] = { uint8_t(x0 >> 8), uint8_t(x0 & 0xff), uint8_t(x1 >> 8), uint8_t(x1 & 0xff) };
    ST7735_WriteData(x, sizeof(x));

    // Row address set
    ST7735_WriteCommand(ST7735_RASET);
    uint8_t y[] = { uint8_t(y0 >> 8), uint8_t(y0 & 0xff), uint8_t(y1 >> 8), uint8_t(y1 & 0xff) };
    ST7735_WriteData(y, sizeof(y));

    // Write to RAM
    ST7735_WriteCommand(ST7735_RAMWR);
}

void tft_st7735::ST7735_SetRotation(uint8_t rotation)
{
    uint16_t temp;
    ST7735_WriteCommand(ST7735_MADCTL);
    switch(rotation) {
        case ST7735_ROTATION_90:  // Landscape
            ST7735_WriteData(0xa0);
            temp = display_width, display_width = display_height, display_height = temp;
            break;
        case ST7735_ROTATION_180: // Portrait inverted
            ST7735_WriteData(0x00);
            break;
        case ST7735_ROTATION_270: // Landscape inverted
            ST7735_WriteData(0x60);
            temp = display_width, display_width = display_height, display_height = temp;
            break;
        case ST7735_ROTATION_0:   // Portrait
        default:
            ST7735_WriteData(0xc0);
            break;
    }
}
