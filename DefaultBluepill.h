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

#ifndef MYBLUEPILL_H
#define MYBLUEPILL_H

#include "DeviceFunctions.h"

/// @brief Configuration of the IR sensors in this format:
///        {transmitPin, receivePin, beamBreak}
///        Set beamBreak to true if the transmitter and receiver are facing each other in a beam break configuration
SensorConfig sensorConfigs[SENSOR_COUNT]={
  {PC13,PC14,false,true},
  {PC15,PA0,false,false},
  {PA1,PA2,false,true},
  {PA3,PA4,false,false},
  {PA5,PA6,false,true},
  {PA7,PB0,false,false},
  {PB1,PB10,false,true},
  {PB11,PB9,false,false},
  {PB8,PB5,false,true},
  {PB4,PB3,false,false},
  {PA15,PA10,false,true},
  {PA9,PA8,false,false},
  {PB15,PB14,false,true},
  {PB13,PB12,false,false},
};

#endif
