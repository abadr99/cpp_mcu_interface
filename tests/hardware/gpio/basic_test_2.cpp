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
     
    
    // 2] Set pin A1 as output
    gpioA.SetDirection<Pin::kPin1, DirectionState::kInputPullUp>();
    gpioA.SetDirection<Pin::kPin0, DirectionState::kOutput>();
    DigitalLevel val=kHigh;
    while (1) {
       
    val= gpioA.Read<Pin::kPin1>();
        _delay_ms(50);
        if ( val == kLow)
        {
        gpioA.Write<Pin::kPin0, DigitalLevel::kHigh>();
        }
        else{
gpioA.Write<Pin::kPin0, DigitalLevel::kLow>();
        }
        
    }
    
}
