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
#include "SerialFunctions.h"
#include "DisplayFunctions.h"
#include "DeviceFunctions.h"

bool newSerialData=false;
const uint8_t maxSerialChars=10;
char serialInputChars[maxSerialChars];

void processSerialInput() {
  static bool serialInProgress=false;
  static uint8_t serialIndex=0;
  char startMarker='<';
  char endMarker='>';
  char serialChar;
  while (Serial.available()>0 && newSerialData==false) {
    serialChar=Serial.read();
    if (serialInProgress==true) {
      if (serialChar!=endMarker) {
        serialInputChars[serialIndex]=serialChar;
        serialIndex++;
        if (serialIndex>=maxSerialChars) {
          serialIndex=maxSerialChars-1;
        }
      } else {
        serialInputChars[serialIndex]='\0';
        serialInProgress=false;
        serialIndex=0;
        newSerialData=true;
      }
    } else if (serialChar==startMarker) {
      serialInProgress=true;
    }
  }
  if (newSerialData) {
    newSerialData=false;
    char* strtokIndex;
    strtokIndex=strtok(serialInputChars, " ");
    char activity=strtokIndex[0];
    strtokIndex=strtok(NULL, " ");
    uint8_t delay=strtoul(strtokIndex, NULL, 10);
    switch(activity) {
      case 'D':
        if (!delay) {
          delay=0;
        }
        processCaseD(delay);
        break;

      case 'V':
        startupDisplay();
        displayVpinMap();
        break;

      case 'Z':
        reset();
        break;

      default:
        break;
    }
  }
}

void processCaseD(int delay) {
  if (delay>0) {
    displayDelay=delay*1000;
    diag=true;
    Serial.print(F("Enabling diagnostic output every "));
    Serial.print(delay);
    Serial.println(F(" seconds"));
  } else if (diag && delay==0) {
    diag=false;
    Serial.println(F("Disabling diagnostic output"));
  } else {
    diag=true;
    Serial.println(F("Enabling diagnostic output"));
  }
  
}
