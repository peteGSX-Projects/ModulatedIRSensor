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
#include "Defines.h"

class IRSensor {
public:
  /// @brief Constructor for a sensor object
  /// @param transmitPin Pin for the IR transmitter
  /// @param receivePin Pin for the IR phototransistor
  /// @param beamBreak Set to true when transmitter/phototransistor face each other (default false)
  IRSensor(int txPin, int rxPin, bool startState=true, bool activeHigh=false, bool beamBreak=false, unsigned long transmitDelay=10000, unsigned long responseDelay=20);

  /// @brief Initiate sensor monitoring, sets pin modes and attaches to the interrupt handler
  void begin();

  /// @brief Routinely check each sensor pair to see if they have been activated
  void check();

  /// @brief Get this sensor's ID
  /// @return ID
  int getId();

  /// @brief Get current state of the transmit pin
  /// @return true/false
  bool getTxState();

  /// @brief Get current state of the receive pin
  /// @return true/false
  bool getRxState();

  /// @brief Get whether the sensor is active high
  /// @return true/false
  bool getActiveHigh();

  /// @brief Get whether it's configured for beam break mode or not
  /// @return true/false
  bool getBeamBreak();

  /// @brief Check if currently activated
  /// @return true/false
  bool getActivated();

  /// @brief Set function to call when sensor activated
  /// @param callback Function to call
  void setActivateCallback(void (*callback)(int id));

  /// @brief Set function to call when sensor deactivated
  /// @param callback Function to call
  void setDeactivateCallback(void (*callback)(int id));

  /// @brief Get the transmitter pin number
  /// @return Transmitter pin number
  int getTxPin();

  /// @brief Get the receiver pin number
  /// @return Receiver pin number
  int getRxPin();

private:
  int _id;
  int _txPin;
  int _rxPin;
  bool _txState;
  bool _activeHigh;
  bool _beamBreak;
  unsigned long _txDelay;
  unsigned long _rxDelay;
  bool _activated;
  unsigned long _lastTxTime;
  unsigned long _lastRxTime;
  static const int _windowSize=10;
  bool _window[_windowSize];
  int _windowIndex;
  bool _rxState;
  void (*_activationCallback)(int id);
  void (*_deactivationCallback)(int id);

  static int _nextId;

};

#endif
