//
// Created by Tristan Morisot on 16/06/2021.
//

#include <hardware/gpio.h>
#include <pico/binary_info/code.h>
#include <hardware/i2c.h>
#include <cstdio>
#include <exception>
#include "I2C.h"

I2C::I2C(int scl, int sda) {
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_set_function(sda, GPIO_FUNC_I2C);

    gpio_pull_up(sda);
    gpio_pull_up(scl);

    bi_decl(bi_2pins_with_func((unsigned long) sda, (unsigned long) scl, GPIO_FUNC_I2C));

    this->sclPin = scl;
    this->sdaPin = sda;
}

void I2C::reset(uint8_t addresse) {
    int res = i2c_write_timeout_us(i2c0, addresse, 0x00, 1, true, 50000);

    if (res == PICO_ERROR_TIMEOUT) {
        printf("PICO_ERROR_TIMEOUT\n");
    } else if (res == PICO_ERROR_GENERIC) {
        printf("PICO_ERROR_GENERIC\n");
    } else {
        printf("%i\n", res);
    }
}
