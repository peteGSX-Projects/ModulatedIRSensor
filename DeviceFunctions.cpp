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
#include "Version.h"
#include "DeviceFunctions.h"
#include "IRSensor.h"

#if defined(ARDUINO_BLUEPILL_F103C8)
#if __has_include ("MyBluepill.h")
  #include "MyBluepill.h"
#else
  #warning MyBluepill.h not found. Using defaults from DefaultBluepill.h
  #include "DefaultBluepill.h"
#endif
#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)
#if __has_include ("MyMega.h")
  #include "MyMega.h"
#else
  #warning MyMega.h not found. Using defaults from DefaultMega.h
  #include "DefaultMega.h"
#endif
#endif

#if defined(ARDUINO_BLUEPILL_F103C8)
PinNameMap pinNames[TOTAL_PINS] = {
  {PC13,"PC13"},{PC14,"PC14"},{PC15,"PC15"},{PA0,"PA0"},{PA1,"PA1"},{PA2,"PA2"},{PA3,"PA3"},{PA4,"PA4"},
  {PA5,"PA5"},{PA6,"PA6"},{PA7,"PA7"},{PB0,"PB0"},{PB1,"PB1"},{PB10,"PB10"},{PB11,"PB11"},
  {PB9,"PB9"},{PB8,"PB8"},{PB5,"PB5"},{PB4,"PB4"},{PB3,"PB3"},{PA15,"PA15"},
  {PA10,"PA10"},{PA9,"PA9"},{PA8,"PA8"},{PB15,"PB15"},{PB14,"PB14"},{PB13,"PB13"},{PB12,"PB12"},
};
#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)
#include <avr/wdt.h>
PinNameMap pinNames[TOTAL_PINS] = {
  {2,"D2"},{3,"D3"},{4,"D4"},{5,"D5"},{6,"D6"},{7,"D7"},{8,"D8"},{9,"D9"},{10,"D10"},{11,"D11"},
  {12,"D12"},{13,"D13"},{14,"D14"},{15,"D15"},{16,"D16"},{17,"D17"},{18,"D18"},{19,"D19"},{22,"D22"},{23,"D23"},
  {24,"D24"},{25,"D25"},{26,"D26"},{27,"D27"},{28,"D28"},{29,"D29"},{30,"D30"},{31,"D31"},{32,"D32"},{33,"D33"},
  {34,"D34"},{35,"D35"},{36,"D36"},{37,"D37"},{38,"D38"},{39,"D39"},{40,"D40"},{41,"D41"},{42,"D42"},{43,"D43"},
  {44,"D44"},{45,"D45"},{46,"D46"},{47,"D47"},{48,"D48"},{49,"D49"},{A0,"A0"},{A1,"A1"},{A2,"A2"},{A3,"A3"},
  {A4,"A4"},{A5,"A5"},{A6,"A6"},{A7,"A7"},{A8,"A8"},{A9,"A9"},{A10,"A10"},{A11,"A11"},
  {A12,"A12"},{A13,"A13"},{A14,"A14"},{A15,"A15"},
};
#endif

IRSensor* sensors[SENSOR_COUNT];
byte sensorStates[(SENSOR_COUNT/8)+1];
char* version;
uint8_t versionBuffer[3];
bool diag=false;

#if defined(ARDUINO_BLUEPILL_F103C8)
void disableJTAG() {
  // Disable JTAG and enable SWD by clearing the SWJ_CFG bits
  // Assuming the register is named AFIO_MAPR or AFIO_MAPR2
  AFIO->MAPR &= ~(AFIO_MAPR_SWJ_CFG);
  // or
  // AFIO->MAPR2 &= ~(AFIO_MAPR2_SWJ_CFG);
}
#endif

void setupSensors() {
  for (int i=0; i<SENSOR_COUNT; i++) {
    sensors[i]=new IRSensor(i, sensorConfigs[i].transmitPin, sensorConfigs[i].receivePin, sensorConfigs[i].beamBreak, sensorConfigs[i].startState);
    sensors[i]->setActivateCallback(sensorActivated);
    sensors[i]->setDeactivateCallback(sensorDeactivated);
    sensors[i]->begin();
  }
}

void sensorActivated(int id) {
  uint8_t sensorByte=id/8;
  uint8_t sensorBit=id-(sensorByte*8);
  bitSet(sensorStates[sensorByte], sensorBit);
  Serial.print(F("Sensor "));
  Serial.print(id);
  Serial.println(F(" activated"));
}

void sensorDeactivated(int id) {
  uint8_t sensorByte=id/8;
  uint8_t sensorBit=id-(sensorByte*8);
  bitClear(sensorStates[sensorByte], sensorBit);
  Serial.print(F("Sensor "));
  Serial.print(id);
  Serial.println(F(" deactivated"));
}

void setVersion() {
  const String versionString = VERSION;
  char versionArray[versionString.length() + 1];
  versionString.toCharArray(versionArray, versionString.length() + 1);
  version = strtok(versionArray, "."); // Split version on .
  versionBuffer[0] = atoi(version);  // Major first
  version = strtok(NULL, ".");
  versionBuffer[1] = atoi(version);  // Minor next
  version = strtok(NULL, ".");
  versionBuffer[2] = atoi(version);  // Patch last
}

void reset() {
#if defined(ARDUINO_BLUEPILL_F103C8)
  __disable_irq();
  NVIC_SystemReset();
  while(true) {};
#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)
  wdt_enable(WDTO_15MS);
  delay(50);
#endif
}
