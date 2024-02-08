 /**
 * @file main.cpp
 * @brief  - Very simple gpio program that flash a a led for 1s 
 *         - This is done by connecting positive pin on led with A1 and negative
 *           pin with 220ohm resistor connected to ground.
 * @version 0.1
 * @date 2023-12-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdint.h>
#include <util/delay.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"

using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;
using DR = Gpio::DirectionState;
using DL = Gpio::DigitalLevel;

int main() {

    // Set pin A1 as output
    Gpio::SetPinDirection(kPortA, kPin1, DR::kOutput);
    
    while (1) {
        // Toggle output voltage every 1 second
        Gpio::WritePin(kPortA, kPin1, DL::kHigh);
        _delay_ms(1000);
        Gpio::WritePin(kPortA, kPin1, DL::kLow);
        _delay_ms(1000);
    }
}
