//
// Created by Tristan Morisot on 26/06/2021.
//

#include <cstdint>
#include <cmath>
#include <hardware/gpio.h>
#include "Screen.h"
#include "hardware/pwm.h"

void Screen::setBacklight(float brightness) {
    // gamma correct the provided 0-255 brightness value onto a
    // 0-65535 range for the pwm counter
    brightness *= 255.0f;
    float gamma = 2.8;
    uint16_t value = (uint16_t)(pow((float)(brightness) / 255.0f, gamma) * 65535.0f + 0.5f);
    pwm_set_gpio_level(this->blPin, value);
}

Screen::Screen(SPI spi, int bl, int dc) {
    this->spi = spi;
    this->dcPin = dc;
    this->blPin = bl;

    gpio_set_function(dc, GPIO_FUNC_SPI);
    gpio_set_dir(dc, GPIO_OUT);

    pwm_config cfg = pwm_get_default_config();
    pwm_set_wrap(pwm_gpio_to_slice_num(this), 65535);
    pwm_init(pwm_gpio_to_slice_num(bl), &cfg, true);
    gpio_set_function(bl, GPIO_FUNC_PWM);
    setBacklight(255); // Turn backlight on by default to avoid nasty surprises
}
