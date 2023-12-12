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

IRSensor::IRSensor(int id, int transmitPin, int receivePin, int message, bool beamBreak)
: _id(id), _transmitPin(transmitPin), _receivePin(receivePin), _message(message),
  _beamBreak(beamBreak), _activated(false),
  _activationCallback(nullptr), _deactivationCallback(nullptr) {}

void IRSensor::setActivateCallback(void (*callback)(int id)) {
  _activationCallback=callback;
}

void IRSensor::setDeactivateCallback(void (*callback)(int id)) {
  _deactivationCallback=callback;
}

void IRSensor::begin() {
  pinMode(_transmitPin, OUTPUT);
  pinMode(_receivePin, INPUT);
  digitalWrite(_transmitPin, HIGH);
}

void IRSensor::check() {
  // Active: Reflection=LOW, Beam break=HIGH
  bool active=false;
  bool currentState=digitalRead(_receivePin);
  if (_beamBreak && currentState) {
    active=true;
  } else if (!_beamBreak && !currentState) {
    active=true;
  }
  if (_activated!=active) {
    _activated=active;
    if (_activated && _activationCallback) {
      _activationCallback(_id);
    } else if (!_activated && _deactivationCallback) {
      _deactivationCallback(_id);
    }
  }
}

// IRSensor class private methods
