//
// Created by Tristan Morisot on 17/06/2021.
//

#ifndef GPS_BLUEFRUIT_H
#define GPS_BLUEFRUIT_H


#include "../BusDevice/SPI.h"

const uint16_t SDEP_MAX_PACKETSIZE = 16;

// Command list
const uint16_t SDEP_CMDTYPE_INITIALIZE = 0xBEEF; /**< Controls the on board LED(s) */
const uint16_t SDEP_CMDTYPE_AT_WRAPPER = 0x0A00;
const uint16_t SDEP_CMDTYPE_BLE_UARTTX = 0x0A01;
const uint16_t SDEP_CMDTYPE_BLE_UARTRX = 0x0A02;

//Message type
const uint16_t SDEP_MSGTYPE_COMMAND = 0x10;
const uint16_t SDEP_MSGTYPE_RESPONSE = 0x20;
const uint16_t SDEP_MSGTYPE_ALERT = 0x40;
const uint16_t SDEP_MSGTYPE_ERROR = 0x80;

class BlueFruit {
public:
    BlueFruit(SPI spi, int rst, int irq);

private:
    SPI spi;
    void init();
    void execute(uint16_t command, uint8_t *buffer, uint8_t length);
    void read();
};

class DataFIFO {
public:
    void flush();
};


#endif //GPS_BLUEFRUIT_H
