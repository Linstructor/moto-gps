//
// Created by Tristan Morisot on 16/06/2021.
//

#ifndef GPS_SPI_H
#define GPS_SPI_H

#include <cstdint>
#include <string>
#include <hardware/spi.h>


class SPI {
private :
    int sckPin;
    int misoPin;
    int mosiPin;
    int csPin;
    spi_inst_t *instance;

public :
    SPI(spi_inst_t *instance, int sck, int miso, int mosi, int cs);

    void read(uint8_t add, uint8_t *buffer, uint16_t length);
    void write(uint8_t add, uint8_t data, uint8_t length);

    int getSCK() const { return sckPin; };
    int getMISO() const { return misoPin; };
    int getMOSI() const { return mosiPin; };
    int getCS() const { return csPin; };
    spi_inst_t *getInstance() const { return instance; };

    void selectCs();
    void deselectCs();
};


#endif //GPS_SPI_H
