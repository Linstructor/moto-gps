//
// Created by Tristan Morisot on 17/06/2021.
//

#include "BlueFruit.h"

void BlueFruit::init() {
    // setup spi

    this->spi.deselectCs();

    //Send init command
    execute(SDEP_CMDTYPE_INITIALIZE, NULL, 0);

    // reset chip

    sleep_ms(1000);
}

void BlueFruit::execute(uint16_t command, uint8_t *buffer, uint8_t length) {
    // Check if data is being transferred from the chip
    // or if in data mode

    /* Create header packet
     * message type = command
     * message id high = (input>>8) & 0xff
     * message id low = input & 0xff
     * length = length
     * more data ?
     */

    if (buffer != NULL && length > 0) {
        /* Copy buffer into message
         * memcpy(msgCmd.payload, buf, count);
         */
    }

    // Begin transaction

    // Enable CS

    //Wait device ack

    // Create timeout

    // While timeout is not reached or if the message has been confirmed ?
    while ( ( spixfer(msgCmd.header.msg_type) == SPI_IGNORED_BYTE ) && !tt.expired() )
    {
        // Disable & Re-enable CS with a bit of delay for Bluefruit to ready itself
        this->spi.deselectCs();
        sleep_ms(10);
        this->spi.selectCs();
    }

    // If not timeout, send the rest of the data
    // spixfer((void*) (((uint8_t*)&msgCmd) +1), sizeof(sdepMsgHeader_t)+count-1);

    this->spi.deselectCs();

}

void DataFIFO::flush() {
    // Clear fifo
}
