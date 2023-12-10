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

IRSensor::IRSensor(int transmitPin, int receivePin, int message, bool beamBreak, int threshold)
  : _transmitPin(transmitPin), _receivePin(receivePin), _message(message), _beamBreak(beamBreak), _threshold(threshold), _receivedMessage(0) {
    // Initialise the sensor
    pinMode(_transmitPin, OUTPUT);
    pinMode(_receivePin, INPUT);
    // attachInterrupt(_receivePin, handler, change);
  }

void IRSensor::transmitMessage() {
  // Configure PWM
  int pwmFrequency=38000;
  int pwmResolution=255;

  // PWM period calculation
  int pwmPeriod=SystemCoreClock/(pwmFrequency*pwmResolution);

  // Use Timer 2 for PWM
  TIM2->CR1|=TIM_CR1_CEN;
  TIM2->PSC=0;
  TIM2->ARR=pwmPeriod-1;
  TIM2->CCMR1|=TIM_CCMR1_OC2M_1;
  TIM2->CCR2=(pwmPeriod*_message)/255;

  digitalWrite(_transmitPin, HIGH);
  delayMicroseconds(_threshold);
  digitalWrite(_transmitPin, LOW);
  delayMicroseconds(_threshold);

  TIM2->CR1&=~TIM_CR1_CEN;
}

// IRSensor class private methods

void IRSensor::_sensorInterruptHandler(void* context) {
  // Cast the context back to the sensor object
  IRSensor* sensor=static_cast<IRSensor*>(context);
  
  // Static method to handle IR data reception for all instances
  static volatile unsigned long lastTime=0;
  static volatile unsigned long pulseDuration=0;

  unsigned long currentTime=micros();
  unsigned long duration=currentTime-lastTime;

  if (duration>sensor->_threshold) {
    // Rising or falling edge detected
    if (digitalRead(sensor->_receivePin)==HIGH) {
      // Rising edge, start measuring pulse duration
      pulseDuration = 0;
    } else {
      // Falling edge, end of pulse, process the received data
      sensor->_processReceivedData(pulseDuration);
    }
  } else {
    // Increment pulse duration during the pulse
    pulseDuration += duration;
  }

  lastTime = currentTime;
}

void IRSensor::_processReceivedData(uint32_t duration) {
  _receivedMessage=_decodeData(duration);
}

int IRSensor::_decodeData(uint32_t duration) {
  return (duration>_threshold) ? 1 : 0;
}
