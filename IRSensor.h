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

#endif
