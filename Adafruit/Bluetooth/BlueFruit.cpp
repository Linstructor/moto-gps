//
// Created by Tristan Morisot on 17/06/2021.
//

#include <hardware/gpio.h>
#include "BlueFruit.h"
#include "sdep.h"

#define SPI_IGNORED_BYTE          0xFEu /**< SPI default character. Character clocked out in case of an ignored transaction. */
#define SPI_OVERREAD_BYTE         0xFFu /**< SPI over-read character. Character clocked out after an over-read of the transmit buffer. */
#define SPI_DEFAULT_DELAY_US      50

void BlueFruit::init() {
    // setup spi

    this->spi.deselectCs();

    //Send init command
    execute(SDEP_CMDTYPE_INITIALIZE, NULL, 0);

    // reset chip
    reset();
    sleep_ms(1000);
}

bool BlueFruit::execute(uint16_t command, uint8_t *buffer, uint8_t length) {
    // Check if data is being transferred from the chip
    // or if in data mode

    /* Create header packet
     * message type = command
     * message id high = (input>>8) & 0xff
     * message id low = input & 0xff
     * length = length
     * more data ?
     */

    sdepMsgCommand_t msgCmd;

    /*msgCmd.header.msg_type    = SDEP_MSGTYPE_COMMAND;
    msgCmd.header.cmd_id_high = highByte(command);
    msgCmd.header.cmd_id_low  = lowByte(command);
    msgCmd.header.length      = length;
    msgCmd.header.more_data   = (length == SDEP_MAX_PACKETSIZE) ? more_data : 0;*/

    if (buffer != NULL && length > 0) {
        /* Copy buffer into message
         * memcpy(msgCmd.payload, buf, count);
         */
    }

    // Enable CS
    this->spi.selectCs();

    // While timeout is not reached or if the message has been confirmed ?
    while ( ( sendPacket(msgCmd.header.msg_type) == SPI_IGNORED_BYTE ) /*&& !tt.expired()*/ )
    {
        // Disable & Re-enable CS with a bit of delay for Bluefruit to ready itself
        this->spi.deselectCs();
        sleep_ms(SPI_DEFAULT_DELAY_US);
        this->spi.selectCs();
    }

    // If not timeout, send the rest of the data
    sendPacket((void*) (((uint8_t*)&msgCmd) +1), sizeof(sdepMsgHeader_t)+length-1);

    this->spi.deselectCs();

    /*
     * Should return false if action timeout, but I removed this feature
     * Now the request can stay in an infinite while loop right above
     */
    return true;
}

void BlueFruit::sendPacket(void *buff, size_t len) {
    uint8_t *p = (uint8_t *)buff;

    while (len--) {
        p[0] = sendPacket(p[0]);
        p++;
    }
}

void BlueFruit::selectSCK() {
    asm volatile("nop \n nop \n nop");
    gpio_put(this->spi.getSCK(), 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

void BlueFruit::deselectSCK() {
    asm volatile("nop \n nop \n nop");
    gpio_put(this->spi.getSCK(), 1);
    asm volatile("nop \n nop \n nop");
}

uint8_t BlueFruit::sendPacket(uint8_t x) {
    // software spi
    uint8_t reply = 0;
    for (int i=7; i>=0; i--) {
        reply <<= 1;
        //            digitalWrite(m_sck_pin, LOW);
        this->selectSCK();
        //            digitalWrite(m_mosi_pin, p[0] & (1<<i));
//        gpio_put(this->spi.getMOSI(), p[0] & (1<<i));
        //            digitalWrite(m_sck_pin, HIGH);
        this->deselectSCK();
        /*if (digitalRead(m_miso_pin))
            reply |= 1;*/
    }
    //digitalWrite(m_sck_pin, LOW);
    this->selectSCK();
    //SerialDebug.println(reply, HEX);
    return reply;
}

bool BlueFruit::reset() {
//    pinMode(m_rst_pin, OUTPUT);
    gpio_put(rstPin, 0);
    gpio_put(rstPin, 1);
    sleep_ms(10);
    gpio_put(rstPin, 0);
    return true;
}

bool BlueFruit::sendInitPattern() {
    return execute(SDEP_CMDTYPE_INITIALIZE, NULL, 0);
}

void DataFIFO::flush() {
    // Clear fifo
}
