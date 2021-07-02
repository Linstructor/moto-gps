//
// Created by Tristan Morisot on 16/06/2021.
//

#include <hardware/i2c.h>
#include "LSM6DSOX.h"

LSM6DSOX::LSM6DSOX(I2C bus): bus(bus){
    this->bus = bus;
}

void LSM6DSOX::getAccelerometerAndGyroscopeData(uint8_t *acc, uint8_t *gyro) {
    this->bus.read(LSM6DS_OUTX_ACCEL, acc, 6);
    this->bus.read(LSM6DS_OUTX_GYRO, gyro, 6);
}

void LSM6DSOX::testRead(uint8_t *acc1, uint8_t *acc2, uint8_t *acc3, uint8_t *acc4, uint8_t *acc5, uint8_t *acc6) {
    this->bus.read(22, acc1, 1);
    this->bus.read(23, acc2, 1);
    this->bus.read(24, acc3, 1);
    this->bus.read(25, acc4, 1);
    this->bus.read(26, acc5, 1);
    this->bus.read(27, acc6, 1);
}
