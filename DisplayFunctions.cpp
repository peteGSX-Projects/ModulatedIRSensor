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
#include "defines.h"
#include "version.h"
#include "DisplayFunctions.h"
#include "DeviceFunctions.h"
#include "I2CFunctions.h"

char* version;
uint8_t versionBuffer[3];
unsigned long lastSensorDisplay=0;
unsigned long displayDelay=DIAG_CONFIG_DELAY*1000;
int firstVpin=0;

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

void startupDisplay() {
  Serial.println(F("Modulated IR Sensor"));
  Serial.print(F("Version: "));
  Serial.println(VERSION);
  Serial.print(F("Available at I2C address 0x"));
  Serial.println(i2cAddress);
}

void displaySensors() {
  if (millis()-lastSensorDisplay>displayDelay) {
    lastSensorDisplay=millis();
    Serial.println(F("Current sensor states:"));
    for (int i=0; i<SENSOR_COUNT; i++) {
      char pinName[5];
      int nameLength=strlen(pinNames[i].pinName);
      int spaces=4-nameLength;

      if (spaces>0) {
        for (int j=0; j<spaces; j++) {
          pinName[j]=' ';
        }
        strncpy(pinName, pinNames[i].pinName, nameLength);
      }
      Serial.print(F("Pin|Tx State|Rx State|Beam Break|Active: "));
      Serial.print(pinName);
      Serial.print(F("|"));
      Serial.print(sensors[i]->getTxState());
      Serial.print(F("|"));
      Serial.print(sensors[i]->getRxState());
      Serial.print(F("|"));
      Serial.print(sensors[i]->getBeamBreak());
      Serial.print(F("|"));
      Serial.println(sensors[i]->getActivated());
    }
  }
}

void displayVpinMap() {
  int vpin=firstVpin;
  
}
