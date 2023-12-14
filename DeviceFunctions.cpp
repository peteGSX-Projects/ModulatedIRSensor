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
SensorConfig sensorConfigs[SENSOR_COUNT]={
  {PC13,PC14,false},
  {PC15,PA0,false},
  // {PA1,PA2,false},
  // {PA3,PA4,false},
  // {PA5,PA6,false},
  // {PA7,PB0,false},
  // {PB1,PB10,false},
  // {PB11,PB9,false},
  // {PB8,PB5,false},
  // {PB4,PB3,false},
  // {PA15,PA10,false},
  // {PA9,PA8,false},
  // {PB15,PB14,false},
  // {PB13,PB12,false},
};

void disableJTAG() {
  // Disable JTAG and enable SWD by clearing the SWJ_CFG bits
  // Assuming the register is named AFIO_MAPR or AFIO_MAPR2
  AFIO->MAPR &= ~(AFIO_MAPR_SWJ_CFG);
  // or
  // AFIO->MAPR2 &= ~(AFIO_MAPR2_SWJ_CFG);
}

IRSensor* sensors[SENSOR_COUNT];

void setupSensors() {
  for (int i=0; i<SENSOR_COUNT; i++) {
    sensors[i]=new IRSensor(i, sensorConfigs[i].transmitPin, sensorConfigs[i].receivePin, sensorConfigs[i].beamBreak);
    sensors[i]->setActivateCallback(onActivate);
    sensors[i]->setDeactivateCallback(onDeactivate);
    sensors[i]->begin();
  }
}

void onActivate(int id) {
  Serial.print(F("Sensor "));
  Serial.print(id);
  Serial.println(F(" activated"));
}

void onDeactivate(int id) {
  Serial.print(F("Sensor "));
  Serial.print(id);
  Serial.println(F(" deactivated"));
}
