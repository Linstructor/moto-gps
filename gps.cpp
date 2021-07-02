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

    //Screen screen = createScreen();

    //LSM6DSOX sensor = createLSM6DSOX();

    I2C i2c (15, 14, LSM6DS_DEFAULT_ADDRESS, i2c1);
    LSM6DSOX sensor (i2c);

    uint8_t acc[6];
    uint8_t gyro[6];

    //printf("Starting loop\n");
    while (true) {
        debugWithLight();

        sensor.getAccelerometerAndGyroscopeData(acc, gyro);
        printf("Acc: %i, %i, %i, %i, %i, %i \n", acc[0], acc[1], acc[2], acc[3], acc[4], acc[5]);
        sensor.testRead(&acc[0], &gyro[1], &gyro[2], &gyro[3], &gyro[4], &gyro[5]);
        printf("Acc: %i, %i, %i, %i, %i, %i \n", gyro[0], gyro[1], gyro[2], gyro[3], gyro[4], gyro[5]);
        //printf("Gyro: %i, %i, %i, %i, %i, %i \n", gyro[0], gyro[1], gyro[2], gyro[3], gyro[4], gyro[5]);

        sleep_ms(500);
    }
}

#pragma clang diagnostic pop