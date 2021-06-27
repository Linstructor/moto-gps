//
// Created by Tristan Morisot on 16/06/2021.
//

#include <hardware/i2c.h>
#include "LSM6DSOX.h"

void LSM6DSOX::reset() {
    this->bus.reset(LSM6DS_DEFAULT_ADDRESS);
}

LSM6DSOX::LSM6DSOX(I2C bus): bus(bus){
    this->bus = bus;
}

void LSM6DSOX::getAccelerometerAndGyroscopeData(uint8_t *acc, uint8_t *gyro) {
    i2c_read_blocking(i2c_default, LSM6DS_OUTX_ACCEL, acc, 6, false);
    i2c_read_blocking(i2c_default, LSM6DS_OUTX_GYRO, gyro, 6, false);
}
