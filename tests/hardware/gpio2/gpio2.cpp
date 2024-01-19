 /**
 * @file basic_test_2.cpp
 * @author @Mariamahmed44 (madiam.ahmed300@gmail.com)
 * @brief  - Very simple gpio test that reads the value of pin A1 (button)
 *         - If it is low, or if the button is pressed, it turns on led on A0
 *         - If it is high, or if the button is not pressed,
 *            it turns off  led on A0
 *         - This is done by connecting positive pin of led with A0 and negative
 *            pin with 220ohm resistor connected to ground.
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

int main() {
    // 1] Create a GPIO object with PortA
    Gpio<Port::kPortA> gpioA
     
    
    // 2] Set pin A1 as input pullup
    gpioA.SetDirection<Pin::kPin1, DirectionState::kInputPullUp>();
    // 3] Set pin A0 as output
    gpioA.SetDirection<Pin::kPin0, DirectionState::kOutput>();
    // 4]create a value & initialize it to khigh
    // 5] It will be assigned to the return value of read method
    DigitalLevel val=kHigh;
    while (1) {
    // 6]read value of A1
        val= gpioA.Read<Pin::kPin1>();
    // 7]for debouncing 
        _delay_ms(50);
    // 8]if the value is low , turn on the led , else turn it off, for A0
        if ( val == kLow){
        gpioA.Write<Pin::kPin0, DigitalLevel::kHigh>();
        }
        else{
        gpioA.Write<Pin::kPin0, DigitalLevel::kLow>();
        }
        
    }
    
}
