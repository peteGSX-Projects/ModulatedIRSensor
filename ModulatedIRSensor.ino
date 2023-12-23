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
#include "Version.h"
#include "I2CFunctions.h"
#include "DeviceFunctions.h"
#include "DisplayFunctions.h"
#include "SerialFunctions.h"

void setup() {
#if defined(ARDUINO_BLUEPILL_F103C8)
  disableJTAG();
#endif
  Serial.begin(115200);
  setVersion();
  startupDisplay();
  setupI2C();
  setupSensors();
}

void loop() {
  for (int i=0; i<SENSOR_COUNT; i++) {
    sensors[i]->check();
  }
  if (diag) {
    displaySensors();
  }
  processSerialInput();
}
