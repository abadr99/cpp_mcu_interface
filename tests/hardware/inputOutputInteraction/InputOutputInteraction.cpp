 /**
 * @file InputOutputInteraction.cpp
 * @brief  - This Program reads the value of pin A1 (button)
 *          - If it is low,(i.e. button is pressed) it turns on led on A0
 *          - If it is high,(i.e. button is not pressed),it turns off led on A0
 *         - This is done by connecting positive pin of led with A0 and negative
 *            pin with 220OHM resistor connected to ground.
 *         -And by connecting the first pin of the push button with A1, 
 *            and the other pin with the ground
 * @version 0.1
 * @date 2023-12-21
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
#define DEBOUNCE_TIME   (50)

int main() {
    //set a0 as input pullup
    Gpio::SetPinDirection(kPortA, kPin0, DR::kInputPullUp);
    //set a1 as output
    Gpio::SetPinDirection(kPortA, kPin1, DR::kOutput);
    DL val = DL::kHigh;
    while (1) {
        val = Gpio::ReadPin(kPortA, kPin0);
        _delay_ms(DEBOUNCE_TIME);
        if (val == Gpio::DigitalLevel::kLow) {
            Gpio::WritePin(kPortA, kPin1, DL::kHigh);
        }
        else {
            Gpio::WritePin(kPortA, kPin1, DL::kLow);
        } 
    }
    
}
