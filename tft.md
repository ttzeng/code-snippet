# TFT Display Driver

## ST7735 based

### ESP32-C3 Super Mini

#### Hardware Connections

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

### STM32F103C8 Black Pill

#### Hardware Connections

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
