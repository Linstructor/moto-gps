//
// Created by Tristan Morisot on 26/06/2021.
//

#ifndef GPS_SCREEN_H
#define GPS_SCREEN_H

#include "../BusDevice/SPI.h"

enum reg {
    SWRESET   = 0x01,
    TEOFF     = 0x34,
    TEON      = 0x35,
    MADCTL    = 0x36,
    COLMOD    = 0x3A,
    GCTRL     = 0xB7,
    VCOMS     = 0xBB,
    LCMCTRL   = 0xC0,
    VDVVRHEN  = 0xC2,
    VRHS      = 0xC3,
    VDVS      = 0xC4,
    FRCTRL2   = 0xC6,
    PWRCTRL1  = 0xD0,
    FRMCTR1   = 0xB1,
    FRMCTR2   = 0xB2,
    GMCTRP1   = 0xE0,
    GMCTRN1   = 0xE1,
    INVOFF    = 0x20,
    SLPOUT    = 0x11,
    DISPON    = 0x29,
    GAMSET    = 0x26,
    DISPOFF   = 0x28,
    RAMWR     = 0x2C,
    INVON     = 0x21,
    CASET     = 0x2A,
    RASET     = 0x2B
};


class Screen {
private:
        int blPin;
        int dcPin;
        SPI *spi;


        void execute(uint8_t command, size_t len, const char *data);
        void execute(uint8_t command);

public:
        void setBacklight(uint8_t brightness);
        void update();

        Screen(SPI spi, int bl, int dc);
};


#endif //GPS_SCREEN_H
