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
   avr::hal::gpio::OutputDeviceInterface<kPortA> obj1(Pin::kPin1);
   avr::hal::gpio::OutputDeviceInterface<kPortA> obj2(Pin::kPin1, Pin::kPin2);
   avr::hal::gpio::OutputDeviceInterface<kPortA> obj3(Pin::kPin1, 
                                                      Pin::kPin2,
                                                      Pin::kPin3);


   while (1) {
       
   }
}

