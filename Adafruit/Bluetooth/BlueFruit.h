//
// Created by Tristan Morisot on 17/06/2021.
//

#ifndef GPS_BLUEFRUIT_H
#define GPS_BLUEFRUIT_H


#include "../BusDevice/SPI.h"

class BlueFruit {
public:
    BlueFruit(SPI spi);
    void reset();

private:
    SPI spi;
};


#endif //GPS_BLUEFRUIT_H
