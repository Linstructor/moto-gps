//
// Created by Tristan Morisot on 16/06/2021.
//

#ifndef GPS_I2C_H
#define GPS_I2C_H

class I2C {
public:
    I2C(int scl, int sda, uint8_t addresse);
    void write(uint8_t data, int length);
    void read(int16_t accel[3], int16_t gyro[3]);
    //void reset();

private:
    int sclPin;
    int sdaPin;
    uint8_t addresse;
};

#endif //GPS_I2C_H
