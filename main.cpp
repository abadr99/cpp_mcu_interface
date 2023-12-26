#include <stdint.h>
#include "mcal/inc/Atmega32.h"
#include "utils/inc/Register.h"
#include "mcal/inc/Gpio.h"
#include "hal/inc/GpioDeviceInterface.h"
#include "hal/inc/Led.h"

using namespace avr::types;
using namespace avr::mcal::gpio;
using namespace avr::hal;
using namespace avr::hal::led;

int main() {
gpio::OutputDeviceInterface<kPortA>(avr::types::kPin1,avr::types::kPin2);
    while (1) {
        
    }
}

