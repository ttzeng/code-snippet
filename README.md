# TFT Display Driver

## API Reference

```
tft& tft::pixel(int16_t x, int16_t y, uint16_t color)
tft& tft::line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
tft& tft::rect(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color)
tft& tft::fill(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color)
tft& tft::clear(uint16_t color)
tft& tft::circle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
tft& tft::fill(int16_t x0, int16_t y0, int16_t r, uint16_t color)
tft& tft::draw_char(int16_t x, int16_t y, char ch, uint16_t color, uint16_t bgcolor, FontDef* font)
tft& tft::draw_string(int16_t x, int16_t y, char* str, uint16_t color, uint16_t bgcolor, FontDef* font)
uint16_t tft::width()
uint16_t tft::height()
```

## Hardware Connections

### ST7735 based

#### ESP32-C3 Super Mini

| ST7735 Pin | ESP32-C3 Pin | Function |
|------------|--------------|----------|
| VCC        | 3.3V         | Power    |
| GND        | GND          | Ground   |
| SCL        | GPIO4        | SPI Clock |
| SDA        | GPIO6        | SPI MOSI  |
| RES        | GPIO0        | Reset     |
| DC         | GPIO1        | Data/Command |
| CS         | GPIO7        | Chip Select |
| BLK        | 3.3V         | Backlight |

#### STM32F103C8 Black Pill

| ST7735 Pin | Black Pill Pin | Function |
|------------|----------------|----------|
| VCC        | 3.3V           | Power    |
| GND        | GND            | Ground   |
| CS         | PA4            | Chip Select |
| RESET      | PA3            | Hardware Reset |
| A0/DC      | PA2            | Data/Command |
| SDA/MOSI   | PA7            | SPI1 MOSI |
| SCK        | PA5            | SPI1 Clock |
| LED        | 3.3V           | Backlight |

```
ST7735 Display          STM32F103C8 Black Pill
┌─────────────┐        ┌────────────────┐
│             │        │                │
│   VCC   ────┼────────┼─ 3.3V          │
│   GND   ────┼────────┼─ GND           │
│   CS    ────┼────────┼─ PA4           │
│   RESET ────┼────────┼─ PA3           │
│   A0/DC ────┼────────┼─ PA2           │
│   SDA   ────┼────────┼─ PA7 (MOSI)    │
│   SCK   ────┼────────┼─ PA5 (SCK)     │
│   LED   ────┼────────┼─ 3.3V          │
│             │        │                │
└─────────────┘        └────────────────┘
```

### ILI9325C based

#### STM32F103C8 Black Pill

| Function | STM32 Pin | LCD Pin | Description |
|----------|-----------|---------|-------------|
| **Control Pins** |
| CS | PB0 | CS | Chip Select |
| RS/DC | PB1 | RS/DC | Register Select/Data Command |
| WR | PB10 | WR | Write Enable |
| RD | PB11 | RD | Read Enable (*optional*) |
| RST | PA8 | RST | Reset |
| **Data Bus (8-bit)** |
| D0-D7 | PA0-PA7 | DB0-DB7 | Parallel Data Bus |
| **Power** |
| VCC | 3.3V | VCC | Power Supply |
| GND | GND | GND | Ground |

```
STM32F103C8 Black Pill          ILI9325C TFT LCD
┌─────────────────────────┐    ┌─────────────────────────┐
│                         │    │                         │
│ PB0  ───────────────────┼────┤ CS                      │
│ PB1  ───────────────────┼────┤ RS/DC                   │
│ PB10 ───────────────────┼────┤ WR                      │
│ PB11 ───────────────────┼────┤ RD                      │
│ PA8  ───────────────────┼────┤ RST                     │
│                         │    │                         │
│ PA0  ───────────────────┼────┤ DB0                     │
│ PA1  ───────────────────┼────┤ DB1                     │
│ PA2  ───────────────────┼────┤ DB2                     │
│ PA3  ───────────────────┼────┤ DB3                     │
│ PA4  ───────────────────┼────┤ DB4                     │
│ PA5  ───────────────────┼────┤ DB5                     │
│ PA6  ───────────────────┼────┤ DB6                     │
│ PA7  ───────────────────┼────┤ DB7                     │
│                         │    │                         │
│ 3.3V ───────────────────┼────┤ VCC                     │
│ GND  ───────────────────┼────┤ GND                     │
└─────────────────────────┘    └─────────────────────────┘
```

# Touch Screen Driver

## API Reference

```
bool touch_screen::read(int& x, int& y)
```

## Hardware Connections

### XPT2046 based

#### STM32F103C8 Black Pill

| XPT2046 Pin | STM32 Pin | Function | Description |
|-------------|-----------|----------|-------------|
| T_CLK       | PB13      | SPI2_SCK | SPI Clock |
| T_DO        | PB14      | SPI2_MISO| SPI Data Out |
| T_DIN       | PB15      | SPI2_MOSI| SPI Data In |
| T_CS        | PA11      | GPIO_OUT | Chip Select |

```
XPT2046 Touch Screen          STM32F103C8 Black Pill
┌─────────────────┐          ┌─────────────────────┐
│                 │          │                     │
│  T_CLK     ●────┼──────────┤ PB13 (SPI2_SCK)     │
│  T_DO      ●────┼──────────┤ PB14 (SPI2_MISO)    │
│  T_DIN     ●────┼──────────┤ PB15 (SPI2_MOSI)    │
│  T_CS      ●────┼──────────┤ PA11 (GPIO)         │
│  GND       ●────┼──────────┤ GND                 │
│                 │          │                     │
└─────────────────┘          └─────────────────────┘
```
