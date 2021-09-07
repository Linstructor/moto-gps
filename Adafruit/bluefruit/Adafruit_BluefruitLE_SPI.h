/**************************************************************************/
/*!
    @file     Adafruit_BluefruiLE_SPI.h
    @author   hathach, ktown (Adafruit Industries)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2015, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#ifndef _ADAFRUIT_BLE_SPI_H_
#define _ADAFRUIT_BLE_SPI_H_

#include "utility/Adafruit_FIFO.h"
#include "../BusDevice/SPI.h"
#include "../Bluetooth/sdep.h"

#define SPI_IGNORED_BYTE          0xFEu /**< SPI default character. Character clocked out in case of an ignored transaction. */
#define SPI_OVERREAD_BYTE         0xFFu /**< SPI over-read character. Character clocked out after an over-read of the transmit buffer. */
#define SPI_DEFAULT_DELAY_US      50

#define BLE_BUFSIZE              4*SDEP_MAX_PACKETSIZE
#define BLUEFRUIT_MODE_COMMAND   1
#define BLUEFRUIT_MODE_DATA      0

#define memclr(buffer, size)  memset(buffer, 0, size)


class Adafruit_BluefruitLE_SPI
{
protected:
    uint8_t _mode;
    absolute_time_t _reset_started_timestamp;
    bool    _verbose;
    enum
    {
        BLUEFRUIT_TRANSPORT_INVALID,
        BLUEFRUIT_TRANSPORT_HWUART,
        BLUEFRUIT_TRANSPORT_SWUART,
        BLUEFRUIT_TRANSPORT_HWSPI,
        BLUEFRUIT_TRANSPORT_SWSPI,
        };
    uint8_t  _physical_transport;
    uint32_t _timeout = 1000;
private:
    SPI *spi;
    // Hardware Pin
    int8_t          m_irq_pin;
    int8_t          m_rst_pin;

    // TX
    uint8_t         m_tx_buffer[SDEP_MAX_PACKETSIZE];
    uint8_t         m_tx_count;

    // RX
    uint8_t         m_rx_buffer[BLE_BUFSIZE];
    Adafruit_FIFO   m_rx_fifo;

    bool            m_mode_switch_command_enabled;

    // Low level transportation I/O functions
    bool    sendInitializePattern(void);
    bool    sendPacket(uint16_t command, const uint8_t* buffer, uint8_t count, uint8_t more_data);
    bool    getPacket(sdepMsgResponse_t* p_response);

    bool    getResponse(void);
    void    simulateSwitchMode(void);
//    bool    handleSwitchCmdInDataMode(uint8_t ch);

    uint8_t spixfer(uint8_t x);
    void spixfer(uint8_t *x, size_t len);

public:
    // Constructor
    Adafruit_BluefruitLE_SPI(SPI *spi, int8_t irqPin, int8_t rstPin);

    // HW initialisation
    bool begin(bool v = false, bool blocking = true);
    void end(void);

    bool setMode(uint8_t new_mode);
    void enableModeSwitchCommand(bool enabled);

    // Class Print virtual function Interface
    virtual size_t write(uint8_t c);
    virtual size_t write(const uint8_t *buffer, size_t size);

    // pull in write(str) and write(buf, size) from Print
    //using Print::write;

    // Class Stream interface
    virtual int  available(void);
    virtual int  read(void);
    virtual void flush(void);
    virtual int  peek(void);
};

#endif
