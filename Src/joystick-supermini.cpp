#include <string.h>
#include "joystick-supermini.hpp"

// ADC configuration
#define ADC_ATTEN           ADC_ATTEN_DB_12
#define ADC_BIT_WIDTH       ADC_BITWIDTH_12

joystick_supermini::joystick_supermini(adc_channel_t pin_x, adc_channel_t pin_y, gpio_num_t pin_button)
    : pin_button(pin_button), pin_x(pin_x), pin_y(pin_y)
{
    // Initialize ADC1 unit
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
        .clk_src = (soc_periph_adc_digi_clk_src_t)0,
        .ulp_mode = (adc_ulp_mode_t)0,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc1_handle));

    // Configure ADC channels to measure analog signals
    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN,
        .bitwidth = ADC_BIT_WIDTH,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, pin_x, &config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, pin_y, &config));

    // Initialize GPIO button
    gpio_config_t io_conf;
    memset(&io_conf, 0, sizeof(io_conf));
    io_conf.intr_type = GPIO_INTR_DISABLE,
    io_conf.mode = GPIO_MODE_INPUT,
    io_conf.pin_bit_mask = (1ULL << pin_button),
    io_conf.pull_down_en = (gpio_pulldown_t)0,
    io_conf.pull_up_en = (gpio_pullup_t)1; // Enable pull-up for button
    gpio_config(&io_conf);
}

joystick_supermini::~joystick_supermini()
{
    // Recycle the ADC Unit
    ESP_ERROR_CHECK(adc_oneshot_del_unit(adc1_handle));

    ESP_ERROR_CHECK(gpio_reset_pin(pin_button));
}

void joystick_supermini::read(int& x, int& y, bool& button, int normalized)
{
    // Read button state (active low, so invert)
    button = !gpio_get_level(pin_button);

    // Read raw ADC values
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, pin_x, &x));
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, pin_y, &y));

    if (normalized > 0) {
        x = x * normalized / (1 << ADC_BIT_WIDTH);
        y = y * normalized / (1 << ADC_BIT_WIDTH);
    }
}
