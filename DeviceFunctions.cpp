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
#include "version.h"
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

PinNameMap pinNames[28] = {
  {PC13,"PC13"},{PC14,"PC14"},{PC15,"PC15"},{PA0,"PA0"},{PA1,"PA1"},{PA2,"PA2"},{PA3,"PA3"},{PA4,"PA4"},
  {PA5,"PA5"},{PA6,"PA6"},{PA7,"PA7"},{PB0,"PB0"},{PB1,"PB1"},{PB10,"PB10"},{PB11,"PB11"},
  {PB9,"PB9"},{PB8,"PB8"},{PB5,"PB5"},{PB4,"PB4"},{PB3,"PB3"},{PA15,"PA15"},
  {PA10,"PA10"},{PA9,"PA9"},{PA8,"PA8"},{PB15,"PB15"},{PB14,"PB14"},{PB13,"PB13"},{PB12,"PB12"},
};

void disableJTAG() {
  // Disable JTAG and enable SWD by clearing the SWJ_CFG bits
  // Assuming the register is named AFIO_MAPR or AFIO_MAPR2
  AFIO->MAPR &= ~(AFIO_MAPR_SWJ_CFG);
  // or
  // AFIO->MAPR2 &= ~(AFIO_MAPR2_SWJ_CFG);
}

IRSensor* sensors[SENSOR_COUNT];
byte sensorStates[(SENSOR_COUNT/8)+1];
char* version;
uint8_t versionBuffer[3];
bool diag=false;

void setupSensors() {
  for (int i=0; i<SENSOR_COUNT; i++) {
    sensors[i]=new IRSensor(i, sensorConfigs[i].transmitPin, sensorConfigs[i].receivePin, sensorConfigs[i].beamBreak, sensorConfigs[i].startState);
    sensors[i]->setActivateCallback(sensorActivated);
    sensors[i]->setDeactivateCallback(sensorDeactivated);
    sensors[i]->begin();
  }
}

void sensorActivated(int id) {
  uint8_t sensorByte=id/8;
  uint8_t sensorBit=id-(sensorByte*8);
  bitSet(sensorStates[sensorByte], sensorBit);
  Serial.print(F("Sensor "));
  Serial.print(id);
  Serial.println(F(" activated"));
}

void sensorDeactivated(int id) {
  uint8_t sensorByte=id/8;
  uint8_t sensorBit=id-(sensorByte*8);
  bitClear(sensorStates[sensorByte], sensorBit);
  Serial.print(F("Sensor "));
  Serial.print(id);
  Serial.println(F(" deactivated"));
}

void setVersion() {
  const String versionString = VERSION;
  char versionArray[versionString.length() + 1];
  versionString.toCharArray(versionArray, versionString.length() + 1);
  version = strtok(versionArray, "."); // Split version on .
  versionBuffer[0] = atoi(version);  // Major first
  version = strtok(NULL, ".");
  versionBuffer[1] = atoi(version);  // Minor next
  version = strtok(NULL, ".");
  versionBuffer[2] = atoi(version);  // Patch last
}

void reset() {
  __disable_irq();
  NVIC_SystemReset();
  while(true) {};
}
