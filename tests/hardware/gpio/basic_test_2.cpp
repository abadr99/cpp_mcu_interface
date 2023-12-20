#include <stdint.h>
#include <util/delay.h>
#include "../../../mcal/inc/atmega32.h"
#include "../../../utils/inc/register.h"
#include "../../../mcal/inc/gpio.h"

using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;

int main() {
    // 1] Create a GPIO object with PortA
    Gpio<Port::kPortA> gpioA;
     
    
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
        if ( val == kLow)
        {
        gpioA.Write<Pin::kPin0, DigitalLevel::kHigh>();
        }
        else{
gpioA.Write<Pin::kPin0, DigitalLevel::kLow>();
        }
        
    }
    
}
