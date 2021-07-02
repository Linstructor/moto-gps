//
// Created by Tristan Morisot on 16/06/2021.
//

#ifndef GPS_LSM6DSOX_H
#define GPS_LSM6DSOX_H


#include <cstdint>
#include "../BusDevice/I2C.h"

const uint8_t DEFAULT_ADDRESSE = 0x6A;
const uint8_t DEFAULT_CHIP_ID = 0x6C;

const uint8_t LSM6DS_WHOAMI = 0x6C;
const uint8_t LSM6DS_CTRL1_XL = 0x10;
const uint8_t LSM6DS_CTRL2_G = 0x11;
const uint8_t LSM6DS_RESET = 0x12;
const uint8_t LSM6DS_CTRL8_XL = 0x17;
const uint8_t LSM6DS_CTRL9_XL = 0x18;
const uint8_t LSM6DS_CTRL10_C = 0x19;
const uint8_t LSM6DS_OUT_TEMP_L = 0x20;
const uint8_t LSM6DS_OUTX_GYRO = 0x22;
const uint8_t LSM6DS_OUTX_ACCEL = 0x28;
const uint8_t LSM6DS_STEP_COUNTER = 0x4B;
const uint8_t LSM6DS_TAP_CFG = 0x58;

const float MILLI_G_TO_ACCEL = 0.00980665;

static int LSM6DS_DEFAULT_ADDRESS = 0x6A;

class LSM6DSOX {
public:
    explicit LSM6DSOX(I2C bus);
    void getAccelerometerAndGyroscopeData(uint8_t *acc, uint8_t *gyro);
    void testRead(uint8_t *acc1, uint8_t *acc2, uint8_t *acc3, uint8_t *acc4, uint8_t *acc5, uint8_t *acc6);


private:
    I2C bus;
};


#endif //GPS_LSM6DSOX_H
