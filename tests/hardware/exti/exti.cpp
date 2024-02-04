//make compile-hardware-test test=tests/hardware/exti/exti.cpp name=exti
/**
 * @file   exti.cpp
 * @author Mariamahmed44 (madiam.ahmed300@gmail.com)
 * @brief   Testing EXTI0 which is done by makeing D2 pin as input pullup,
 *          and when any change happens to this pin, a led connected to A0
 *          will light up for 3 seconds.
 * @version 0.1
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdint.h>
#include <util/delay.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../mcal/inc/ExternalInterrupt.h"

using namespace avr::mcal::gpio;
using namespace avr::mcal::external_interrupt;
using namespace avr::types;


void led_on()
{
Gpio::WritePin(kPortA, kPin0, Gpio::DigitalLevel::kHigh);
_delay_ms(3000);

}
int main() {
  /*set A0 as output for the led, and D2 as input pullup for EXTI0*/
  Gpio::SetPinDirection(kPortA, kPin0, Gpio::DirectionState::kOutput);
  Gpio::SetPinDirection(kPortD, kPin2, Gpio::DirectionState::kInputPullUp);
  /*enable EXTI0 & apply any changes to trigger the interrupt*/
  SetInterrupt(kInterrupt0, kChange, led_on);

   while (1) {
  Gpio::WritePin(kPortA, kPin0, Gpio::DigitalLevel::kLow);
}
}
