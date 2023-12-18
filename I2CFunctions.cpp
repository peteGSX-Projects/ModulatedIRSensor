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
#include <Wire.h>
#include "defines.h"
#include "I2CFunctions.h"
#include "DisplayFunctions.h"
#include "DeviceFunctions.h"

uint8_t i2cAddress=I2C_ADDRESS;
uint8_t numReceivedPins=0;
char commandBuffer[3];
char responseBuffer[1];
bool setupComplete=false;
uint8_t outboundFlag;

void setupI2C() {
  if (i2cAddress<0x08 || i2cAddress>0x77) {
    Serial.print(F("Invalid I2C address configured: 0x"));
    Serial.print(i2cAddress, HEX);
    Serial.println(F(", using default instead"));
    i2cAddress=0x65;
  }
  Wire.begin(i2cAddress);
}

void receiveEvent(int numBytes) {
  if (numBytes==0) return;
  byte buffer[numBytes];
  for (uint8_t i=0; i<numBytes; i++) {
    buffer[i]=Wire.read();
  }
  switch(buffer[0]) {
    case EXIOINIT:
      if (numBytes==4) {
        numReceivedPins=buffer[1];
        firstVpin=(buffer[3]<<8)+buffer[2];
        if (numReceivedPins==SENSOR_COUNT) {
          setupComplete=true;
        } else {
          setupComplete=false;
        }
        outboundFlag=EXIOINIT;
      }
      break;
    
    case EXIOINITA:
      if (numBytes==1) {
        outboundFlag=EXIOINITA;
      }
      break;
    
    case EXIOVER:
      if (numBytes==1) {
        outboundFlag=EXIOVER;
      }
      break;
    
    case EXIODPUP:
      if (numBytes==3) {
        outboundFlag=EXIODPUP;
        responseBuffer[0]=EXIORDY;
      }
      break;
    
    case EXIORDD:
      if (numBytes==1) {
        outboundFlag=EXIORDD;
      }
      break;

    case EXIORDAN:
      if (numBytes==1) {
        outboundFlag=EXIORDAN;
      }
      break;

    case EXIOWRD:
    case EXIOENAN:
    case EXIOWRAN:
      outboundFlag=EXIOWRD;
      responseBuffer[0]=EXIOERR;
      break;
    
    default:
      break;
  }
}

void requestEvent() {
  char noData[0];
  switch(outboundFlag) {
    case EXIOINIT:
      if(setupComplete) {
        commandBuffer[0]=EXIOPINS;
        commandBuffer[1]=SENSOR_COUNT;
        commandBuffer[2]=0;
      } else {
        commandBuffer[0]=0;
        commandBuffer[1] = 0;
        commandBuffer[2] = 0;
      }
      Wire.write(commandBuffer, 3);
      break;
    
    case EXIOINITA:
      Wire.write(noData, 0);
      break;

    case EXIOVER:
      Wire.write(versionBuffer, 3);
      break;
    
    case EXIODPUP:
      Wire.write(responseBuffer, 1);
      break;

    case EXIORDD:
      Wire.write(sensorStates, SENSOR_COUNT);
      break;

    case EXIORDAN:
      Wire.write(noData, 0);
      break;
    
    case EXIOWRD:
      Wire.write(responseBuffer, 1);
      break;

    default:
      break;
  }
}
