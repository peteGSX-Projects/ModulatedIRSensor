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

IRSensor::IRSensor(int txPin, int rxPin, bool startState, bool beamBreak, bool activeHigh, unsigned long transmitDelay, unsigned long responseDelay)
: _txPin(txPin), _rxPin(rxPin), _txState(startState), _beamBreak(beamBreak), _activeHigh(activeHigh), _txDelay(transmitDelay), _rxDelay(transmitDelay+responseDelay) {
  _id=_nextId++;
  _activated=false;
  _lastTxTime=0;
  _lastRxTime=0;
  _windowIndex=0;
  _rxState=false;
  _activationCallback=nullptr;
  _deactivationCallback=nullptr;
}

void IRSensor::begin() {
  pinMode(_txPin, OUTPUT);
  pinMode(_rxPin, INPUT);
  digitalWrite(_txPin, _txState);
}

/// @brief Modulate the transmitter high/low and compare the receiver state
void IRSensor::check() {
  unsigned long currentMicros=micros();

  // Alternate trasmit pin at the specified rate
  if (currentMicros-_lastTxTime>_txDelay) {
    _lastTxTime=currentMicros;
    _txState=!_txState;
    digitalWrite(_txPin, _txState);
  }
  
  // Check the receive pin state after the specified delay
  if (currentMicros-_lastRxTime>_rxDelay) {
    _lastRxTime=currentMicros;
    // Get receiver state and invert if sensor is active high
    _rxState=digitalRead(_rxPin);
    bool rxState=(_activeHigh) ? _rxState : !_rxState;
    if (_beamBreak) {
      // In beam break mode, if Tx is high and Rx matches, it's receiving, therefore not activated
      // If Tx is high and Rx doesn't match, active
      _window[_windowIndex]=(_txState&&rxState!=_txState) || (!_txState);
    } else {
      // In reflection mode, true if Rx is the same as Tx
      _window[_windowIndex]=(rxState==_txState);
    }
    _windowIndex=(_windowIndex+1)%_windowSize;
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

int IRSensor::getId() {
  return _id;
}

bool IRSensor::getTxState() {
  return _txState;
}

bool IRSensor::getRxState() {
  return _rxState;
}

bool IRSensor::getActiveHigh() {
  return _activeHigh;
}

bool IRSensor::getBeamBreak() {
  return _beamBreak;
}

bool IRSensor::getActivated() {
  return _activated;
}

void IRSensor::setActivateCallback(void (*callback)(int id)) {
  _activationCallback=callback;
}

void IRSensor::setDeactivateCallback(void (*callback)(int it)) {
  _deactivationCallback=callback;
}

int IRSensor::getTxPin() {
  return _txPin;
}

int IRSensor::getRxPin() {
  return _rxPin;
}

// IRSensor class private methods

int IRSensor::_nextId=0;
