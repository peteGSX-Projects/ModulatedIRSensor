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

#ifndef MYMEGA_H
#define MYMEGA_H

#include <Arduino.h>
#include "DeviceFunctions.h"

/// @brief Configuration of the IR sensors in this format:
///        {transmitPin, receivePin, beamBreak}
///        Set beamBreak to true if the transmitter and receiver are facing each other in a beam break configuration
SensorConfig sensorConfigs[SENSOR_COUNT]={
  {2,3,false,true},
  {4,5,false,false},
  {6,7,false,true},
  {8,9,false,false},
  {10,11,false,true},
  {12,13,false,false},
  {14,15,false,true},
  {16,17,false,false},
  {18,19,false,true},
  {22,23,false,false},
  {24,25,false,true},
  {26,27,false,false},
  {28,29,false,true},
  {30,31,false,false},
  {32,33,false,true},
  {34,35,false,false},
  {36,37,false,true},
  {38,39,false,false},
  {40,41,false,true},
  {42,43,false,false},
  {44,45,false,true},
  {46,47,false,false},
  {48,49,false,true},
  {A0,A1,false,false},
  {A2,A3,false,true},
  {A4,A5,false,false},
  {A6,A7,false,true},
  {A8,A9,false,false},
  {A10,A11,false,true},
  {A12,A13,false,false},
  {A14,A15,false,true},
};

#endif
