/*
 *  © 2023 Peter Cole
 *  © 2024 Peter Cole
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
#if (defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)) && !__has_include("MySensors.h")
IRSensor* sensors[SENSOR_COUNT]={
  new IRSensor(2,3,true,false,false,20000,100),
  new IRSensor(4,5,false,false,false,20000,100),
  new IRSensor(6,7,true,false,false,20000,100),
  new IRSensor(8,9,false,false,false,20000,100),
  new IRSensor(10,11,true,false,false,20000,100),
  new IRSensor(12,13,false,false,false,20000,100),
  new IRSensor(14,15,true,false,false,20000,100),
  new IRSensor(16,17,false,false,false,20000,100),
  new IRSensor(18,19,true,false,false,20000,100),
  new IRSensor(22,23,false,false,false,20000,100),
  new IRSensor(24,25,true,false,false,20000,100),
  new IRSensor(26,27,false,false,false,20000,100),
  new IRSensor(28,29,true,false,false,20000,100),
  new IRSensor(30,31,false,false,false,20000,100),
  new IRSensor(32,33,true,false,false,20000,100),
  new IRSensor(34,35,false,false,false,20000,100),
  new IRSensor(36,37,true,false,false,20000,100),
  new IRSensor(38,39,false,false,false,20000,100),
  new IRSensor(40,41,true,false,false,20000,100),
  new IRSensor(42,43,false,false,false,20000,100),
  new IRSensor(44,45,true,false,false,20000,100),
  new IRSensor(46,47,false,false,false,20000,100),
  new IRSensor(48,49,true,false,false,20000,100),
  new IRSensor(A0,A1,false,false,false,20000,100),
  new IRSensor(A2,A3,true,false,false,20000,100),
  new IRSensor(A4,A5,false,false,false,20000,100),
  new IRSensor(A6,A7,true,false,false,20000,100),
  new IRSensor(A8,A9,false,false,false,20000,100),
  new IRSensor(A10,A11,true,false,false,20000,100),
  new IRSensor(A12,A13,false,false,false,20000,100),
  new IRSensor(A14,A15,true,false,false,20000,100),
};
#endif
