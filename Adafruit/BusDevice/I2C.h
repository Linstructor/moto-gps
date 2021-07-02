//
// Created by Tristan Morisot on 16/06/2021.
//

#ifndef GPS_I2C_H
#define GPS_I2C_H

class I2C {
public:
    I2C(int scl, int sda, uint8_t addresse, i2c_inst_t *instance);
    void write(uint8_t data, int length);
    void read(uint8_t reg, uint8_t *val, int length);
    //void reset();

private:
    int sclPin;
    int sdaPin;
    i2c_inst_t *instance;
    uint8_t addresse;
};

#endif //GPS_I2C_H
