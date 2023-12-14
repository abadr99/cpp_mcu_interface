#include <stdint.h>
#include "mcal/inc/atmega32.h"
#include "utils/inc/register.h"
#include "mcal/inc/gpio.h"

using namespace utils;
using namespace avr::mcu::gpio;
using namespace avr::types;

int main() {
    Gpio<Port::kPortA> gpioA;
    
    while (1) {
    }
}
