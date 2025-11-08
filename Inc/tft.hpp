#ifndef TFT_HPP
#define TFT_HPP

#include "stdint.h"

#define RGB565(r,g,b) ((((r) & 0xf8) << 8) | (((g) & 0xfc) << 3) | ((b) >> 3))

#define RGB565_BLACK        0x0000
#define RGB565_BLUE         0x001F
#define RGB565_RED          0xF800
#define RGB565_GREEN        0x07E0
#define RGB565_CYAN         0x07FF
#define RGB565_MAGENTA      0xF81F
#define RGB565_YELLOW       0xFFE0
#define RGB565_WHITE        0xFFFF
#define RGB565_ORANGE       0xFD20
#define RGB565_PURPLE       0x8010
#define RGB565_PINK         0xFE19
#define RGB565_BROWN        0xA145

typedef struct {
    const uint8_t width;
    const uint8_t height;
    const uint16_t data[];
} FontDef;

extern FontDef Font8x8, Font7x10, Font11x18;

typedef void (*mdelay_func) (uint32_t msec);

class tft {
  public:
    explicit tft(uint16_t width, uint16_t height);
    uint16_t width() { return display_width; }
    uint16_t height() { return display_height; }
    virtual tft& pixel(int16_t x, int16_t y, uint16_t color) = 0;
    virtual tft& line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    virtual tft& rect(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
    virtual tft& fill(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color);
    virtual tft& clear(uint16_t color);
    virtual tft& circle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    virtual tft& fill(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    virtual tft& draw_char(int16_t x, int16_t y, char ch, uint16_t color, uint16_t bgcolor, FontDef* font = 0);
    virtual tft& draw_string(int16_t x, int16_t y, char* str, uint16_t color, uint16_t bgcolor, FontDef* font = 0);
  protected:
    uint16_t display_width;
    uint16_t display_height;
    FontDef* default_font;
};

#endif // TFT_HPP
