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

#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <Arduino.h>

class IRSensor {
public:
  /// @brief Constructor for a sensor object
  /// @param transmitPin Pin for the IR transmitter
  /// @param receivePin Pin for the IR phototransistor
  /// @param activationCallback Function to call when sensor pair is activated
  /// @param deactivationCallback Function to call when sensor pair is deactivated
  /// @param beamBreak Set to true when transmitter/phototransistor face each other (defaul false)
  IRSensor(int transmitPin, int receivePin, void (*activationCallback)()=nullptr, void (*deactivationCallback)()=nullptr, bool beamBreak=false);

  /// @brief Initiate sensor monitoring, sets pin modes and attaches to the interrupt handler
  void begin();


private:
  int _transmitPin;
  int _receivePin;
  void (*_activationCallback)();
  void (*_deactivationCallback)();
  bool _beamBreak;

  static void _sensorInterruptHandler();

  static IRSensor* _instance;

};

/*
class IRSensor {
public:
  /// @brief Constructor for a sensor object
  /// @param transmitPin Pin to use for transmitting the encoded message
  /// @param receivePin Pin to use for receiving the encoded message
  /// @param message Integer to use as the encoded message to send
  /// @param beamBreak (Optional) Set to true if the transmit/receive pair are in a beam break configuration rather than reflection
  IRSensor(int transmitPin, int receivePin, int message, bool beamBreak=false, int threshold=1000);

  /// @brief Transmit the encoded message
  void transmitMessage();

private:
  int _transmitPin;
  int _receivePin;
  int _message;
  bool _beamBreak;
  unsigned long _threshold;
  volatile int _receivedMessage;

  /// @brief Interrupt handler for sensors
  /// @param context The sensor instance that needs handling
  static void _sensorInterruptHandler(void* context);

  /// @brief Process the received data
  /// @param duration Length of received pulse
  void _processReceivedData(uint32_t duration);

  /// @brief Decode the actual received message based on pulse duration
  /// @param duration Duration of the pulse received
  /// @return Message to return
  int _decodeData(uint32_t duration);

};
*/

#endif
