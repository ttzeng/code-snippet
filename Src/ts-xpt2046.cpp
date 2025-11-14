#include "ts-xpt2046.hpp"

touch_screen_xpt2046::touch_screen_xpt2046(uint16_t width, uint16_t height)
    : touch_screen(width, height)
{
    // Set default calibration values (raw ADC range)
    calibrate(250, 3900, 250, 3900);
}

bool touch_screen_xpt2046::read(int& x, int& y)
{
    bool touched = is_touched();

    if (touched) {
        // Read multiple samples and average for better accuracy
        const int samples = 8;
        uint32_t x_raw, x_sum = 0, y_raw, y_sum = 0, valid_samples = 0;

        for (int i = 0; i < samples; i++) {
            // Small delay to stabilize
            mdelay(1);

            x = read_channel(XPT2046_DIFF_X);
            y = read_channel(XPT2046_DIFF_Y);
            // Filter out invalid readings
            if (x > 100 && x < 4000 && y > 100 && y < 4000) {
                x_sum += x, y_sum += y;
                valid_samples++;
            }
        }

        if (valid_samples > 0) {
            // Calculate averages
            x_raw = x_sum / valid_samples;
            y_raw = y_sum / valid_samples;

            // Apply calibration
            if (x_raw < x_min) x_raw = x_min;
            if (x_raw > x_max) x_raw = x_max;
            if (y_raw < y_min) y_raw = y_min;
            if (y_raw > y_max) y_raw = y_max;

            // Map to screen coordinates
            x = ((x_raw - x_min) * screen_width) / (x_max - x_min);
            y = ((y_raw - y_min) * screen_height) / (y_max - y_min);
        } else {
            touched = 0;
        }
    }
    return touched;
}

void touch_screen_xpt2046::calibrate(uint16_t Xmin, uint16_t Xmax, uint16_t Ymin, uint16_t Ymax)
{
    x_min = Xmin, x_max = Xmax;
    y_min = Ymin, y_max = Ymax;
}
