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

#include <Arduino.h>
#include "DeviceFunctions.h"

/// @brief Configuration of the IR sensors in this format:
///        {transmitPin, receivePin, beamBreak}
///        Set beamBreak to true if the transmitter and receiver are facing each other in a beam break configuration
#if defined(ARDUINO_BLUEPILL_F103C8) && !__has_include("MySensors.h")
IRSensor* sensors[SENSOR_COUNT]={
  new IRSensor(0,PC13,PC14,false,true),
  new IRSensor(1,PC15,PA0,false,false),
  new IRSensor(2,PA1,PA2,false,true),
  new IRSensor(3,PA3,PA4,false,false),
  new IRSensor(4,PA5,PA6,false,true),
  new IRSensor(5,PA7,PB0,false,false),
  new IRSensor(6,PB1,PB10,false,true),
  new IRSensor(7,PB11,PB9,false,false),
  new IRSensor(8,PB8,PB5,false,true),
  new IRSensor(9,PB4,PB3,false,false),
  new IRSensor(10,PA15,PA10,false,true),
  new IRSensor(11,PA9,PA8,false,false),
  new IRSensor(12,PB15,PB14,false,true),
  new IRSensor(13,PB13,PB12,false,false),
};
#endif
