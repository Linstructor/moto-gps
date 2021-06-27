//
// Created by Tristan Morisot on 16/06/2021.
//

#include <hardware/gpio.h>
#include <pico/binary_info/code.h>
#include <hardware/i2c.h>
#include <cstdio>
#include <exception>
#include "I2C.h"

I2C::I2C(int scl, int sda, uint8_t addresse) {
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_set_function(sda, GPIO_FUNC_I2C);

    gpio_pull_up(sda);
    gpio_pull_up(scl);

    bi_decl(bi_2pins_with_func((unsigned long) sda, (unsigned long) scl, GPIO_FUNC_I2C));

    this->sclPin = scl;
    this->sdaPin = sda;
    this->addresse = addresse;
}

void I2C::write(uint8_t data, int length) {
    i2c_write_blocking(i2c_default, this->addresse, &data, length, true);
}

void I2C::read(int16_t *accel, int16_t *gyro) {
    uint8_t buffer[6];

    // Start reading acceleration registers from register 0x3B for 6 bytes
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c_default, this->addresse, &val, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c_default, this->addresse, buffer, 6, false);

    // Now gyro data from reg 0x43 for 6 bytes
    // The register is auto incrementing on each read
    val = 0x43;
    i2c_write_blocking(i2c_default, this->addresse, &val, 1, true);
    i2c_read_blocking(i2c_default, this->addresse, buffer, 6, false);  // False - finished with bus

}
