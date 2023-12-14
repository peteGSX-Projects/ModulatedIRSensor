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

#ifndef DEVICEFUNCTIONS_H
#define DEVICEFUNCTIONS_H

#include <Arduino.h>
#include "defines.h"
#include "IRSensor.h"

struct SensorConfig {
  int transmitPin;
  int receivePin;
  bool beamBreak;
};

extern SensorConfig sensorConfigs[SENSOR_COUNT];
extern IRSensor* sensors[SENSOR_COUNT];

void disableJTAG();
void setupSensors();
void onActivate(int id);
void onDeactivate(int id);

#endif
