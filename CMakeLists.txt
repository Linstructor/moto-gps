# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/Users/tristan/Documents/pico-sdk/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(gps C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(gps gps.cpp Adafruit/BusDevice/SPI.cpp Adafruit/BusDevice/SPI.h Adafruit/BusDevice/I2C.cpp Adafruit/BusDevice/I2C.h Adafruit/LSM6DSOX/LSM6DSOX.cpp Adafruit/LSM6DSOX/LSM6DSOX.h Adafruit/Bluetooth/BlueFruit.cpp Adafruit/Bluetooth/BlueFruit.h Adafruit/Screen/Screen.cpp Adafruit/Screen/Screen.h Adafruit/bluefruit/Adafruit_BluefruitLE_SPI.h Adafruit/bluefruit/Adafruit_BluefruitLE_SPI.cpp Adafruit/bluefruit/utility/Adafruit_FIFO.h Adafruit/bluefruit/utility/Adafruit_FIFO.cpp Adafruit/bluefruit/utility/TimeoutTimer.h)

pico_set_program_name(gps "gps")
pico_set_program_version(gps "0.1")

pico_enable_stdio_uart(gps 1)
pico_enable_stdio_usb(gps 1)

# Add the standard library to the build
target_link_libraries(gps pico_stdlib)

# Add any user requested libraries
target_link_libraries(gps
        hardware_spi
        hardware_i2c
        hardware_pio
        hardware_pwm
        )

pico_add_extra_outputs(gps)

