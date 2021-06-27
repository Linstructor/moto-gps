//
// Created by Tristan Morisot on 16/06/2021.
//

#ifndef GPS_I2C_H
#define GPS_I2C_H

class I2C {
public:
    I2C(int scl, int sda);
    void reset(uint8_t addresse);

private:
    int sclPin;
    int sdaPin;
};

#endif //GPS_I2C_H
