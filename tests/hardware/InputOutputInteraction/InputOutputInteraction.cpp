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

#define DEBOUNCE_TIME   (50)
int main() {
    //Create a GPIO object of portA
    Gpio GPIO(kPortA);
    //set a0 as input pullup
    GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kInputPullUp);
    //set a1 as output
    GPIO.SetPinDirection(kPin1, Gpio::DirectionState::kOutput);
   Gpio::DigitalLevel val =Gpio::DigitalLevel::kHigh;
    while (1) {
        val = GPIO.ReadPin(kPin0);
        _delay_ms(DEBOUNCE_TIME);
        if (val == Gpio::DigitalLevel::kLow) {
            GPIO.WritePin(kPin1, Gpio::DigitalLevel::kHigh);
        }
        else {
            GPIO.WritePin(kPin1, Gpio::DigitalLevel::kLow);
        } 
    }
    
}
