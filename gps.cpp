#include <stdio.h>
#include <pico/binary_info/code.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "Adafruit/Screen/Screen.h"
#include "Adafruit/LSM6DSOX/LSM6DSOX.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

void debugWithLight() {
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    sleep_ms(500);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
    sleep_ms(500);
}


void setupLed() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    sleep_ms(2000);
    debugWithLight();
    sleep_ms(2000);
}

Screen createScreen() {
    SPI spi (spi1, 14, 0, 15 ,13);
    Screen screen (spi, 14, 15);
    return screen;
}

LSM6DSOX createLSM6DSOX() {
    I2C i2c (15, 14, LSM6DS_DEFAULT_ADDRESS, i2c1);
    LSM6DSOX sensor (i2c);
    return sensor;
}

int main() {
    stdio_init_all();
    setupLed();

    printf("Starting\n");

    debugWithLight();

    //printf("Starting loop\n");
    while (true) {
        debugWithLight();

        sleep_ms(500);
    }
}

#pragma clang diagnostic pop