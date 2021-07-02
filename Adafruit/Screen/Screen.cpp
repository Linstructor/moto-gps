//
// Created by Tristan Morisot on 26/06/2021.
//

#include <cstdint>
#include <cmath>
#include <hardware/gpio.h>
#include "Screen.h"
#include "hardware/pwm.h"

void Screen::setBacklight(uint8_t brightness) {
    // gamma correct the provided 0-255 brightness value onto a
    // 0-65535 range for the pwm counter
    float gamma = 2.8;
    uint16_t value = (uint16_t)(pow((float)(brightness) / 255.0f, gamma) * 65535.0f + 0.5f);
    pwm_set_gpio_level(this->blPin, value);
}

Screen::Screen(SPI spi, int bl, int dc) {
    this->spi = &spi;
    this->dcPin = dc;
    this->blPin = bl;

    gpio_set_function(dc, GPIO_FUNC_SPI);
    gpio_set_dir(dc, GPIO_OUT);

    pwm_config cfg = pwm_get_default_config();
    pwm_set_wrap(pwm_gpio_to_slice_num(bl), 65535);
    pwm_init(pwm_gpio_to_slice_num(bl), &cfg, true);
    gpio_set_function(bl, GPIO_FUNC_PWM);

    execute(reg::COLMOD,1, "\x05");  // 16 bits per pixel

    execute(reg::FRMCTR2, 5, "\x0c\x0c\x00\x33\x33");
    execute(reg::GCTRL, 1, "\x14");
    execute(reg::VCOMS, 1, "\x37");
    execute(reg::LCMCTRL, 1, "\x2c");
    execute(reg::VDVVRHEN, 1, "\x01");
    execute(reg::VRHS, 1, "\x12");
    execute(reg::VDVS, 1, "\x20");
    execute(0xd0, 2, "\xa4\xa1");
    execute(reg::FRMCTR2, 1, "\x0f");
    execute(reg::GMCTRP1, 14, "\xD0\x04\x0D\x11\x13\x2B\x3F\x54\x4C\x18\x0D\x0B\x1F\x23");
    execute(reg::GMCTRN1, 14, "\xD0\x04\x0C\x11\x13\x2C\x3F\x44\x51\x2F\x1F\x1F\x20\x23");

    execute(reg::INVON);   // set inversion mode
    execute(reg::SLPOUT);  // leave sleep mode
    execute(reg::DISPON);  // turn display on
}

void Screen::execute(uint8_t command, size_t len, const char *data) {
    this->spi->selectCs();

    gpio_put(dcPin, 0); // command mode
    spi_write_blocking(this->spi->getInstance(), &command, 1);

    if(data) {
        gpio_put(dcPin, 1); // data mode
        spi_write_blocking(this->spi->getInstance(), (const uint8_t*)data, len);
    }

    this->spi->deselectCs();
}

void Screen::execute(uint8_t command) {
    this->spi->selectCs();

    gpio_put(dcPin, 0); // command mode
    spi_write_blocking(this->spi->getInstance(), &command, 1);

    this->spi->deselectCs();
}
