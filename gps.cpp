#include <stdio.h>
#include <pico/binary_info/code.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "Adafruit/Screen/Screen.h"

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

int main() {
    stdio_init_all();
    setupLed();

    printf("Starting\n");

    debugWithLight();

    Screen screen (SPI(spi0, 1, 2, 3 ,4), 5, 6);

    screen.setBacklight(0.5);

    printf("Starting loop\n");
    while (true) {
        debugWithLight();

        sleep_ms(1000);
    }
}

#pragma clang diagnostic pop