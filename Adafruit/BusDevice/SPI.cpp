//
// Created by Tristan Morisot on 16/06/2021.
//

#include "SPI.h"
#include <hardware/gpio.h>

SPI::SPI(spi_inst_t *instance, int sck, int miso, int mosi, int cs) {
    this->csPin = cs;
    this->sckPin = sck;
    this->misoPin = miso;
    this->mosiPin = mosi;
    this->instance = instance;

    spi_init(instance, 400 * 1000);

    gpio_set_function(mosi, GPIO_FUNC_SPI);
    gpio_set_function(sck, GPIO_FUNC_SPI);
    gpio_set_function(miso, GPIO_FUNC_SPI);

    gpio_init(cs);
    gpio_set_dir(cs, GPIO_OUT);
    gpio_put(cs, 1);
}

void SPI::selectCs() {
    asm volatile("nop \n nop \n nop");
    gpio_put(this->csPin, 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

void SPI::deselectCs() {
    asm volatile("nop \n nop \n nop");
    gpio_put(this->csPin, 1);
    asm volatile("nop \n nop \n nop");
}

void SPI::read(uint8_t add, uint8_t *buffer, uint16_t length) {
    selectCs();
    spi_write_blocking(instance, &add, 1);
    spi_read_blocking(instance, 0, buffer, length);
    sleep_ms(10);
    deselectCs();
}

void SPI::write(uint8_t add, uint8_t data, uint8_t length) {
    uint8_t buf[2];
    buf[0] = add & 0x7f;  // remove read bit as this is a write
    buf[1] = data;
    selectCs();
    spi_write_blocking(instance, buf, 2);
    deselectCs();
    sleep_ms(10);
}
