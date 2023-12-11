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
#include "DeviceFunctions.h"

void setup() {
  disableJTAG();
  Serial.begin(115200);
  Serial.println(F("Encoded IR Sensor"));
  // pinMode(irReceiverPin, INPUT);
}

void loop() {
  // bool newState = digitalRead(irReceiverPin);
  // if (newState != receivedState) {
  //   Serial.println(newState);
  //   receivedState = newState;
  // }
}

/* ORIGINAL CODE HERE

#include <Arduino.h>

// Transmitter Setup:

// Connect the anode (longer leg) of the IR LED to a digital output pin on the Arduino (e.g., Pin 3).
// Connect the cathode (shorter leg) of the IR LED to a current-limiting resistor (e.g., 220 ohms).
// Connect the other end of the current-limiting resistor to the GND pin on the Arduino.

// Receiver Setup:

// Connect the collector of the IR phototransistor to the 5V pin on the Arduino through a pull-up resistor (e.g., 10k ohms).
// Connect the emitter of the IR phototransistor to a digital input pin on the Arduino (e.g., Pin 2).
// Connect a capacitor (e.g., 1uF) between the digital input pin and GND to filter out noise.
//

// // Encoder
//
// To encode a signal with a simple number without using a library, you can use a basic encoding scheme like Pulse Width Modulation (PWM). In this method, you can represent the data by varying the width of the pulses of the IR signal. For example, you can use a longer pulse for a binary "1" and a shorter pulse for a binary "0."

// Here's a basic example of how to encode a simple number (e.g., 5) and transmit it using an IR LED connected to an Arduino.

// This example will transmit the number 5 using PWM encoding. Adjust the pulseWidthHigh and pulseWidthLow variables to control the width of the pulses and, consequently, the encoding. You'll need to use a corresponding decoding algorithm on the receiving side to interpret the pulses and extract the encoded number.

// Keep in mind that this example is a simple illustration, and in real-world applications, you may need to consider error checking, synchronization, and other factors to ensure reliable data transmission and reception. Using more advanced encoding schemes and error-checking methods would be necessary for robust and error-resistant communication.
//

// // Decoder (phototransistor)
//
// To decode the transmitted signal using the Pulse Width Modulation (PWM) encoding example provided earlier, you would need a receiving algorithm that measures the time durations of the incoming pulses and then interprets these durations to reconstruct the original encoded number. Here's a basic decoding algorithm for the given PWM encoding scheme.

// In this decoding algorithm, the Arduino waits for the start signal from the transmitter using waitForStartSignal(). Once the start signal is received, it proceeds to receive and decode the number using receiveNumber(). The function receiveNumber() measures the time durations of the incoming pulses and interprets them to reconstruct the original encoded number.

// Please note that this is a basic example for educational purposes, and in real-world applications, you may need to add error checking, synchronization, and other measures to ensure reliable data transmission and reception. More advanced encoding and decoding methods are necessary for robust and error-resistant communication.
//

#if defined(ARDUINO_AVR_NANO)
const int irTransmitterPin = 3; // The pin connected to the anode (longer leg) of the IR LED
const int irReceiverPin = 2; // The pin connected to the emitter of the IR phototransistor
#elif defined(ARDUINO_BLUEPILL_F103C8)
const int irTransmitterPin = PB13; // The pin connected to the anode (longer leg) of the IR LED
const int irReceiverPin = PB14; // The pin connected to the emitter of the IR phototransistor
#endif
int numberToSend = 5; // The number you want to encode and transmit
unsigned long lastTransmit = 0;
const unsigned long transmitDelay = 5000;
bool receivedState = LOW;

// Basic IR setup here that works in reflection mode

// void setup() {
//   Serial.begin(115200);
//   Serial.println(F("Basic IR sensor test"));
//   pinMode(irReceiverPin, INPUT);
// }

// void loop() {
//   bool newState = digitalRead(irReceiverPin);
//   if (newState != receivedState) {
//     Serial.println(newState);
//     receivedState = newState;
//   }
// }

void setup() {
  Serial.begin(115200);
  pinMode(irTransmitterPin, OUTPUT);
  pinMode(irReceiverPin, INPUT);    // No pullup required, board has a pullup resistor already
}

void loop() {
  if (millis() - lastTransmit > transmitDelay) {
    transmitNumber(numberToSend);
  }
  if (waitForStartSignal()) {
    int decodedNumber = receiveNumber();
    Serial.print("Received number: ");
    Serial.println(decodedNumber);
  }
}

void transmitNumber(int number) {
  // Encode and transmit the number using PWM

  // Define the pulse width for binary "1" and binary "0" (in microseconds)
  const int pulseWidthHigh = 1000; // For example, use 1000 microseconds for "1"
  const int pulseWidthLow = 500;   // For example, use 500 microseconds for "0"

  // Start transmission with a known signal (e.g., a sequence of pulses to indicate the beginning of the data)
  digitalWrite(irTransmitterPin, HIGH);
  delay(200); // A short delay for synchronization
  digitalWrite(irTransmitterPin, LOW);
  delayMicroseconds(100);

  // Send each bit of the number
  for (int i = 0; i < 8; i++) {
    int bitValue = (number >> i) & 1; // Extract the i-th bit of the number

    // Transmit the bit as a pulse
    if (bitValue) {
      digitalWrite(irTransmitterPin, HIGH);
      delayMicroseconds(pulseWidthHigh);
    } else {
      digitalWrite(irTransmitterPin, HIGH);
      delayMicroseconds(pulseWidthLow);
    }

    // Leave a gap between pulses
    digitalWrite(irTransmitterPin, LOW);
    delayMicroseconds(100);
  }

  // End transmission with a known signal (e.g., a sequence of pulses to indicate the end of the data)
  digitalWrite(irTransmitterPin, HIGH);
  delay(200); // A short delay for synchronization
  digitalWrite(irTransmitterPin, LOW);
}

bool waitForStartSignal() {
  // This function waits for the start signal from the transmitter.
  // It will block until the start signal is received or a timeout occurs.

  const int startSignalTimeout = 2000; // Timeout duration in milliseconds
  unsigned long startTime = millis();

  while (digitalRead(irReceiverPin) == HIGH) {
    if (millis() - startTime >= startSignalTimeout) {
      return false; // Start signal not received within timeout, abort
    }
  }

  return true; // Start signal received
}

int receiveNumber() {
  // This function receives and decodes the number sent by the transmitter.

  // Define the pulse width for binary "1" and binary "0" (in microseconds)
  const int pulseWidthHigh = 1000; // For example, use 1000 microseconds for "1"
  const int pulseWidthLow = 500;   // For example, use 500 microseconds for "0"

  int receivedNumber = 0;

  for (int i = 0; i < 8; i++) {
    // Measure the duration of the pulse (HIGH level)
    unsigned long pulseStartTime = micros();
    while (digitalRead(irReceiverPin) == HIGH) {
      // Wait for the pulse to end
    }
    unsigned long pulseDuration = micros() - pulseStartTime;

    // Determine the bit value based on the pulse duration
    int bitValue;
    if (pulseDuration > (pulseWidthHigh + pulseWidthLow) / 2) {
      bitValue = 1;
    } else {
      bitValue = 0;
    }

    // Update the received number
    receivedNumber |= (bitValue << i);

    // Skip the gap between pulses
    while (digitalRead(irReceiverPin) == LOW) {
      // Wait for the next pulse to start
    }
  }

  return receivedNumber;
}

*/
