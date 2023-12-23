/*
 *  © 2023 Peter Cole
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DEFINES_H
#define DEFINES_H

#include "IRSensor.h"

#if __has_include ("MyConfig.h")
  #include "MyConfig.h"
#else
  #warning MyConfig.h not found. Using defaults from DefaultConfig.h
  #include "DefaultConfig.h"
#endif

#ifndef SENSOR_COUNT
#if defined(ARDUINO_BLUEPILL_F103C8)
#define SENSOR_COUNT 14
#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)
#define SENSOR_COUNT 62
#endif
#endif

#ifndef I2C_ADDRESS
#define I2C_ADDRESS 0x65
#endif

#ifndef DIAG_CONFIG_DELAY
#define DIAG_CONFIG_DELAY 5
#endif

#if defined(ARDUINO_BLUEPILL_F103C8)
#define TOTAL_PINS 28
#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)
#define TOTAL_PINS 62
#endif

#define EXIOINIT 0xE0     // Flag to start setup procedure
#define EXIORDY 0xE1      // Flag setup procedure done, return to CS to ACK
#define EXIODPUP 0xE2     // Flag we're receiving digital pin pullup configuration
#define EXIOVER 0xE3      // Flag to send version
#define EXIORDAN 0xE4     // Flag an analogue input is being read
#define EXIOWRD 0xE5      // Flag for digital write
#define EXIORDD 0xE6      // Flag a digital input is being read
#define EXIOENAN 0xE7     // Flag to enable an analogue input pin
#define EXIOINITA 0xE8    // Flag to send analogue pin info
#define EXIOPINS 0xE9     // Flag we need to send pin counts
#define EXIOWRAN 0xEA     // Flag we're receiving an analogue write (PWM)
#define EXIOERR 0xEF      // Flag something has errored to send to device driver

struct PinNameMap {
  int pin;
  const char* pinName;
};

#endif
