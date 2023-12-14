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
#include "IRSensor.h"

// IRSensor class public methods

IRSensor::IRSensor(int id, int txPin, int rxPin, bool beamBreak)
: _id(id), _txPin(txPin), _rxPin(rxPin), _beamBreak(beamBreak) {
  _activated=false;
  _lastTxTime=0;
  _lastRxTime=0;
  _txDelay=1000;
  _rxDelay=1020;
  _windowIndex=0;
  _txState=true;
  _activationCallback=nullptr;
  _deactivationCallback=nullptr;
}

void IRSensor::setActivateCallback(void (*callback)(int id)) {
  _activationCallback=callback;
}

void IRSensor::setDeactivateCallback(void (*callback)(int id)) {
  _deactivationCallback=callback;
}

void IRSensor::begin() {
  pinMode(_txPin, OUTPUT);
  pinMode(_rxPin, INPUT);
  digitalWrite(_txPin, _txState);
}

void IRSensor::check() {
  unsigned long currentMicros=micros();

  if (currentMicros-_lastTxTime>_txDelay) {
    _lastTxTime=currentMicros;
    _txState=!_txState;
    digitalWrite(_txPin, _txState);
  }
  
  if (currentMicros-_lastRxTime>_rxDelay) {
    _lastRxTime=currentMicros;
    bool rxState=digitalRead(_rxPin);
    bool isActive=(_beamBreak) ? rxState : !rxState;
    _window[_windowIndex]=(isActive==_txState);
    _windowIndex=(_windowIndex)%_windowSize;
  }

  bool activated=true;
  for (int i=0; i<_windowSize; i++) {
    if (!_window[i]) {
      activated=false;
      break;
    }
  }
  
  if (_activated!=activated) {
    _activated=activated;
    if (_activated && _activationCallback) {
      _activationCallback(_id);
    } else if (!_activated && _deactivationCallback) {
      _deactivationCallback(_id);
    }
  }
}

// IRSensor class private methods
