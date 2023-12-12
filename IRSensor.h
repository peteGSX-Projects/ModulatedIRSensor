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
  /// @param message Numeric message to transmit and validate has been received in order to activate
  /// @param beamBreak Set to true when transmitter/phototransistor face each other (defaul false)
  IRSensor(int id, int transmitPin, int receivePin, int message, bool beamBreak=false);

  /// @brief Set function to call when sensor activated
  /// @param callback Function to call
  void setActivateCallback(void (*callback)(int id));

  /// @brief Set function to call when sensor deactivated
  /// @param callback Function to call
  void setDeactivateCallback(void (*callback)(int id));
  
  /// @brief Initiate sensor monitoring, sets pin modes and attaches to the interrupt handler
  void begin();

  /// @brief Routinely check each sensor pair to see if they have been activated
  void check();

private:
  int _id;
  int _transmitPin;
  int _receivePin;
  int _message;
  bool _beamBreak;
  bool _activated;
  void (*_activationCallback)(int id);
  void (*_deactivationCallback)(int id);

};

#endif
