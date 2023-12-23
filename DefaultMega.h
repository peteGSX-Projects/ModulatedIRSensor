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
IRSensor* sensors[SENSOR_COUNT]={
  new IRSensor(0,2,3,false,true),
  new IRSensor(1,4,5,false,false),
  new IRSensor(2,6,7,false,true),
  new IRSensor(3,8,9,false,false),
  new IRSensor(4,10,11,false,true),
  new IRSensor(5,12,13,false,false),
  new IRSensor(6,14,15,false,true),
  new IRSensor(7,16,17,false,false),
  new IRSensor(8,18,19,false,true),
  new IRSensor(9,22,23,false,false),
  new IRSensor(10,24,25,false,true),
  new IRSensor(11,26,27,false,false),
  new IRSensor(12,28,29,false,true),
  new IRSensor(13,30,31,false,false),
  new IRSensor(14,32,33,false,true),
  new IRSensor(15,34,35,false,false),
  new IRSensor(16,36,37,false,true),
  new IRSensor(17,38,39,false,false),
  new IRSensor(18,40,41,false,true),
  new IRSensor(19,42,43,false,false),
  new IRSensor(20,44,45,false,true),
  new IRSensor(21,46,47,false,false),
  new IRSensor(22,48,49,false,true),
  new IRSensor(23,A0,A1,false,false),
  new IRSensor(24,A2,A3,false,true),
  new IRSensor(25,A4,A5,false,false),
  new IRSensor(26,A6,A7,false,true),
  new IRSensor(27,A8,A9,false,false),
  new IRSensor(28,A10,A11,false,true),
  new IRSensor(29,A12,A13,false,false),
  new IRSensor(30,A14,A15,false,true),
};

#endif
