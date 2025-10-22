#include "led-supermini.hpp"
#include "esp_log.h"

static const char* TAG = "Led-Esp32c3-SuperMini";

Led_Esp32c3_SuperMini::Led_Esp32c3_SuperMini(gpio_num_t pin) : led_pin(pin)
{
    // Configure GPIO pin
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << led_pin);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;

    esp_err_t ret;
    if ((ret = gpio_config(&io_conf)) == ESP_OK) {
        // Initialize LED to OFF state
        gpio_set_level(led_pin, 0);
        ESP_LOGI(TAG, "LED created for GPIO%d and initialized successfully", led_pin);
    } else {
        ESP_LOGE(TAG, "Failed to initialize LED GPIO%d", led_pin);
    }
}

Led_Esp32c3_SuperMini::~Led_Esp32c3_SuperMini()
{
    // Reset GPIO to default state
    esp_err_t ret;
    if ((ret = gpio_reset_pin(led_pin)) == ESP_OK) {
        ESP_LOGI(TAG, "LED GPIO%d deinitialized and destroyed", led_pin);
    } else {
        ESP_LOGE(TAG, "Failed to deinitialize LED GPIO%d", led_pin);
    }
}

void Led_Esp32c3_SuperMini::set_state(bool state)
{
    esp_err_t ret;
    if ((ret = gpio_set_level(led_pin, state? 1 : 0)) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set LED state to %s", state ? "ON" : "OFF");
    } else {
        ESP_LOGI(TAG, "LED state set to %s via assignment operator", state ? "ON" : "OFF");
    }
}

bool Led_Esp32c3_SuperMini::get_state() const
{
    return gpio_get_level((gpio_num_t)led_pin);
}
