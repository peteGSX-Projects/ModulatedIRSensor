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
  new IRSensor(PC13,PC14,true),
  new IRSensor(PC15,PA0,false),
  new IRSensor(PA1,PA2,true),
  new IRSensor(PA3,PA4,false),
  new IRSensor(PA5,PA6,true),
  new IRSensor(PA7,PB0,false),
  new IRSensor(PB1,PB10,true),
  new IRSensor(PB11,PB9,false),
  new IRSensor(PB8,PB5,true),
  new IRSensor(PB4,PB3,false),
  new IRSensor(PA15,PA10,true),
  new IRSensor(PA9,PA8,false),
  new IRSensor(PB15,PB14,true),
  new IRSensor(PB13,PB12,false),
};
#endif
