 /**
 * @file led_1.cpp
 * @brief  - Led test that turns it on for 1 second
 *         - After that it turns it off for 1 second
 *         - Then it toggles for 
 *         - After 5 seconds it toggles again
 *         - After 5 seconds it does the same tasks
 *         - This is done by connecting positive pin on led with A0 and negative
 *           pin with 220ohm resistor connected to ground.
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
#include "../../../hal/inc/GpioDeviceInterface.h"
#include "../../../hal/inc/Led.h"


using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::hal::led;
using namespace avr::types;

int main() 
{
    // 1] Create a led object with PortA
    Led<kActiveHigh>led_1({kPortA,kPin0});
    
    while (1) {
      led_1.TurnOn();
      _delay_ms(1000);
      led_1.TurnOff();
      _delay_ms(1000);
      led_1.Toggle();
      _delay_ms(5000);
      led_1.Toggle();
      _delay_ms(5000);
    }
}
