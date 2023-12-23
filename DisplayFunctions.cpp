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
#include "Defines.h"
#include "DisplayFunctions.h"
#include "DeviceFunctions.h"
#include "I2CFunctions.h"

unsigned long lastSensorDisplay=0;
unsigned long displayDelay=DIAG_CONFIG_DELAY*1000;
int firstVpin=0;

void startupDisplay() {
  Serial.println(F("Modulated IR Sensor"));
  Serial.print(F("Version: "));
  Serial.print(versionBuffer[0]);
  Serial.print(F("."));
  Serial.print(versionBuffer[1]);
  Serial.print(F("."));
  Serial.println(versionBuffer[2]);
  Serial.print(F("Available at I2C address 0x"));
  Serial.println(i2cAddress, HEX);
}

void displaySensors() {
  if (millis()-lastSensorDisplay>displayDelay) {
    lastSensorDisplay=millis();
    Serial.println(F("Current sensor states:"));
    int vpin=firstVpin;
    for (int i=0; i<SENSOR_COUNT; i++) {
      Serial.print(F("Vpin|Tx State|Rx State|Beam Break|Active: "));
      Serial.print(vpin);
      Serial.print(F("|"));
      Serial.print(sensors[i]->getTxState());
      Serial.print(F("|"));
      Serial.print(sensors[i]->getRxState());
      Serial.print(F("|"));
      Serial.print(sensors[i]->getBeamBreak());
      Serial.print(F("|"));
      Serial.println(sensors[i]->getActivated());
      vpin++;
    }
  }
}

void displayVpinMap() {
  int vpin=firstVpin;
  Serial.println(F("Vpin to sensor pin mappings (Vpin => Tx pin|Rx pin):"));
  for (uint8_t i=0; i<SENSOR_COUNT; i++) {
    char txName[5];
    char rxName[5];
    int txPin=sensors[i]->getTxPin();
    int rxPin=sensors[i]->getRxPin();
    for (uint8_t i=0; i<28; i++) {
      if (pinNames[i].pin==txPin) {
        strncpy(txName, pinNames[i].pinName, sizeof(txName)-1);
        txName[sizeof(txName)-1]='\0';
      }
      if (pinNames[i].pin==rxPin) {
        strncpy(rxName, pinNames[i].pinName, sizeof(rxName)-1);
        rxName[sizeof(rxName)-1]='\0';
      }
    }
    Serial.print(vpin);
    Serial.print(F(" => "));
    Serial.print(txName);
    Serial.print(F("|"));
    Serial.println(rxName);
    vpin++;
  }
}
