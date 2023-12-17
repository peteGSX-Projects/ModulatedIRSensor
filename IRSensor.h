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

/*
*   Using cheap AliExpress IR sensors
*   These sensors set an input pin low when activated in reflection mode
*   In beam break mode, therefore, they will set an input pin high when activated
*   Experimentation shows the receiver takes several microseconds to respond to
*   a change in state, therefore a delay of 20 microseconds is added to compensate
*/

#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <Arduino.h>
#include "defines.h"

class IRSensor {
public:
  /// @brief Constructor for a sensor object
  /// @param transmitPin Pin for the IR transmitter
  /// @param receivePin Pin for the IR phototransistor
  /// @param beamBreak Set to true when transmitter/phototransistor face each other (defaul false)
  IRSensor(int id, int txPin, int rxPin, bool beamBreak=false, bool startState=true, unsigned long transmitDelay=10000, unsigned long responseDelay=20);

  /// @brief Initiate sensor monitoring, sets pin modes and attaches to the interrupt handler
  void begin();

  /// @brief Routinely check each sensor pair to see if they have been activated
  void check();

  /// @brief Get current state of the transmit pin
  /// @return true/false
  bool getTxState();

  /// @brief Get current state of the receive pin
  /// @return true/false
  bool getRxState();

  /// @brief Get whether it's configured for beam break mode or not
  /// @return true/false
  bool getBeamBreak();

  /// @brief Check if currently activated
  /// @return true/false
  bool getActivated();

private:
  int _id;
  int _txPin;
  int _rxPin;
  bool _beamBreak;
  bool _txState;
  unsigned long _txDelay;
  unsigned long _rxDelay;
  bool _activated;
  unsigned long _lastTxTime;
  unsigned long _lastRxTime;
  static const int _windowSize=10;
  bool _window[_windowSize];
  int _windowIndex;
  bool _rxState;

};

#endif
