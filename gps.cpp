#include <stdio.h>
#include <pico/binary_info/code.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "Adafruit/LSM6DSOX/LSM6DSOX.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void debugWithLight() {
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    sleep_ms(500);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
    sleep_ms(500);
}


int main() {
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    sleep_ms(2000);
    debugWithLight();
    sleep_ms(2000);
    printf("Starting\n");

    i2c_init(i2c0, 100 * 1000);
    I2C gpsI2C (22, 21);
    LSM6DSOX sensor (gpsI2C);

    bi_decl(bi_1pin_with_name(25, "On-board LED"));

    printf("Reseting sensor\n");
    //sensor.reset();

    debugWithLight();

    printf("Starting loop\n");
    bool running = true;
    while (running) {
        debugWithLight();
        printf("%i, %i\n", i2c_get_read_available(i2c0), i2c_get_write_available(i2c0));
        /*printf("Test\n");
        uint8_t accel[3], gyro[3];
        sensor.getAccelerometerAndGyroscopeData(accel, gyro);
        printf(reinterpret_cast<const char *>(accel[1]));
        printf(reinterpret_cast<const char *>(gyro[1]))*/

        sensor.reset();

        /*printf("\nI2C Bus Scan\n");
        printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

        for (int addr = 0; addr < (1 << 7); ++addr) {
            if (addr % 16 == 0) {
                printf("%02x ", addr);
            }

            // Perform a 1-byte dummy read from the probe address. If a slave
            // acknowledges this address, the function returns the number of bytes
            // transferred. If the address byte is ignored, the function returns
            // -1.

            // Skip over any reserved addresses.
            int ret;
            uint8_t rxdata;
            if (reserved_addr(addr))
                ret = PICO_ERROR_GENERIC;
            else
                ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);

            printf(ret < 0 ? "." : "@");
            printf(addr % 16 == 15 ? "\n" : "  ");
        }
        printf("Done.\n");*/

        sleep_ms(1000);
    }
}

#pragma clang diagnostic pop