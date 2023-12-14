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

const int txPin=PC13;
const int rxPin=PC14;

unsigned long lastTxTime=0;
unsigned long lastRxTime=0;
unsigned long waveDelay=1000;
unsigned long responseDelay=1020;   // Allow for slow phototransistor response to trasnmitter changes
bool received=false;

const int windowSize=10;
bool window[windowSize];
int windowIndex=0;

bool txState=true;

bool activeState=false;

void setup() {
  disableJTAG();
  Serial.begin(115200);
  delay(5000);
  Serial.println(F("Encoded IR Sensor"));
  Serial.print(F("Version: "));
  Serial.println(VERSION);
  // setupSensors();

  pinMode(txPin, OUTPUT);
  pinMode(rxPin, INPUT);
  digitalWrite(txPin, txState);
}

void loop() {
  // for (int i=0; i<SENSOR_COUNT; i++) {
  //   sensors[i]->check();
  // }

  unsigned long currentMicros=micros();

  if (currentMicros-lastTxTime>waveDelay) {
    lastTxTime=currentMicros;
    txState=!txState;
    digitalWrite(txPin, txState);
  }

  if (currentMicros-lastRxTime>responseDelay) {
    lastRxTime=lastRxTime=currentMicros;
    bool rxState=digitalRead(rxPin);
    bool isActive=(activeState) ? rxState : !rxState;
    window[windowIndex]=(isActive==txState);
    windowIndex=(windowIndex+1) % windowSize;
  }

  received=true;
  for (int i=0; i< windowSize; i++) {
    if (!window[i]) {
      received=false;
      break;
    }
  }

  if (received) {
    onActivate(0);
  }
}
