#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "tft-st7735-supermini.hpp"

tft_st7735_supermini::tft_st7735_supermini(spi_host_device_t spi_host, int pin_cs, int pin_sck, int pin_mosi, int pin_dc, int pin_rst, uint8_t rotation)
    : spi_host(spi_host), spi(0), pin_dc(pin_dc), pin_reset(pin_rst)
{
    // Initialize GPIO pins
    gpio_config_t io_conf;
    memset(&io_conf, 0, sizeof(io_conf));
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << pin_dc) | (1ULL << pin_reset);
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    // Configure SPI bus
    spi_bus_config_t buscfg;
    memset(&buscfg, 0, sizeof(buscfg));
    buscfg.max_transfer_sz = ST7735_WIDTH * ST7735_HEIGHT * 2;
    buscfg.mosi_io_num = pin_mosi;
    buscfg.sclk_io_num = pin_sck;
    buscfg.miso_io_num =
    buscfg.quadwp_io_num = 
    buscfg.quadhd_io_num = -1;
    ESP_ERROR_CHECK(spi_bus_initialize(spi_host, &buscfg, SPI_DMA_CH_AUTO));

    // Configure SPI device
    spi_device_interface_config_t devcfg;
    memset(&devcfg, 0, sizeof(devcfg));
    devcfg.clock_speed_hz = 26 * 1000 * 1000; // 26 MHz
    devcfg.mode = 0;
    devcfg.spics_io_num = pin_cs;
    devcfg.queue_size = 7;
    devcfg.flags = SPI_DEVICE_NO_DUMMY;
    ESP_ERROR_CHECK(spi_bus_add_device(spi_host, &devcfg, &spi));

    ST7735_Init();
    ST7735_SetRotation(rotation);
}

tft_st7735_supermini::~tft_st7735_supermini()
{
    if (spi) {
        spi_bus_remove_device(spi);
        spi_bus_free(spi_host);
    }
}

tft& tft_st7735_supermini::fill(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    if (x >= 0 && x < ST7735_WIDTH && y >= 0 && y < ST7735_HEIGHT) {
        ST7735_SetAddressWindow(x, y, x + width - 1, y + height - 1);
        uint32_t pixels = width * height;
        uint8_t colorBytes[2] = { uint8_t(color >> 8), uint8_t(color & 0xff) };
        for (uint32_t i = 0; i < pixels; i++) {
            ST7735_WriteData(colorBytes, 2);
        }
    }
    return *this;
}

void tft_st7735_supermini::ST7735_WriteCommand(uint8_t cmd)
{
    spi_transaction_t t;

    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &cmd;

    gpio_set_level((gpio_num_t)pin_dc, 0); // Command mode
    spi_device_polling_transmit(spi, &t);
}

void tft_st7735_supermini::ST7735_WriteData(uint8_t data)
{
    ST7735_WriteData(&data, 1);
}

void tft_st7735_supermini::ST7735_WriteData(uint8_t *data, uint16_t len)
{
    spi_transaction_t t;

    if (len > 0) {
        memset(&t, 0, sizeof(t));
        t.length = len * 8;
        t.tx_buffer = data;

        gpio_set_level((gpio_num_t)pin_dc, 1); // Data mode
        spi_device_polling_transmit(spi, &t);
    }
}

void tft_st7735_supermini::_RST(bool state)
{
    gpio_set_level((gpio_num_t)pin_reset, state? 1 : 0);
}

void tft_st7735_supermini::_DC(bool state)
{
    gpio_set_level((gpio_num_t)pin_dc, state? 1 : 0);
}

void tft_st7735_supermini::_CS(bool unused)
{
    // CS is auto driven in the SPI transaction
}

void tft_st7735_supermini::mdelay(uint32_t msec)
{
    vTaskDelay(msec / portTICK_PERIOD_MS);
}
