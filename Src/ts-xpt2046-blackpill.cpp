#include "ts-xpt2046-blackpill.hpp"

touch_screen_xpt2046_blackpill::touch_screen_xpt2046_blackpill(uint16_t width, uint16_t height, SPI_HandleTypeDef *hspi)
    : touch_screen_xpt2046(width, height), ts_spi(hspi)
{
    STM32_GPIO_Init();
}

void touch_screen_xpt2046_blackpill::STM32_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

bool touch_screen_xpt2046_blackpill::is_touched()
{
    return (read_channel(XPT2046_Z1_POSITION) > XPT2046_TOUCH_THRESHOLD);
}

/**
 * @brief  Read a single channel from XPT2046
 * @param  command: Command byte (channel selection)
 * @retval 12-bit ADC value
 */
uint16_t touch_screen_xpt2046_blackpill::read_channel(uint8_t command)
{
    uint8_t tx_data[3] = {0};
    uint8_t rx_data[3] = {0};
    uint16_t result = 0;

    /* Construct command byte */
    tx_data[0] = XPT2046_START_BIT | command;
    tx_data[1] =
    tx_data[2] = 0x00;

    /* Activate chip select */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);

    /* Small delay for CS setup time */
    for (volatile int i = 0; i < 10; i++);

    /* Transmit command and receive data */
    if (HAL_SPI_TransmitReceive(ts_spi, tx_data, rx_data, 3, 100) == HAL_OK) {
        /* XPT2046 returns 12-bit data in bits [14:3] of the response */
        result = (((rx_data[1] << 8) | rx_data[2]) >> 3) & 0x0FFF;
    }

    /* Deactivate chip select */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);

    return result;
}


void touch_screen_xpt2046_blackpill::mdelay(uint32_t msec)
{
    HAL_Delay(msec);
}
