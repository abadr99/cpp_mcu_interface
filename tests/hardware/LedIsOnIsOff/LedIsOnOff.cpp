 /**
 * @file ledIsOnOff.cpp
 * @brief  - Led test that firstly checks if the led is on
 *         - if its true it turns it off and waits for 1 second
 *         - After that it checks if the  led is turned off
 *         - if its true it turns it on and waits for 1 second
 *         - This is done by connecting positive pin on led with A0 and negative
 *           pin with 220ohm resistor connected to ground.
 * @version 0.1
 * @date 2024-1-26
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
    bool val=0;
    while (1) {
      led_1.TurnOn();
      _delay_ms(1000);
      val=led_1.IsOn();
      if(val==1)
      {
      led_1.TurnOff();
      _delay_ms(1000);
      }
      val=led_1.IsOff();
      if(val==1)
      {
      led_1.TurnOn();
      _delay_ms(1000);
      }
    }


}
