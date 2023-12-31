#include <stdint.h>
#include "mcal/inc/Atmega32.h"
#include "utils/inc/Register.h"
#include "mcal/inc/Gpio.h"
#include "hal/inc/GpioDeviceInterface.h"
#include "hal/inc/Led.h"

using namespace avr::types;
using namespace avr::mcal::gpio;
using namespace avr::hal::gpio;

int main() {
   
   OutputDeviceInterface<kPortB> obj1(Pin::kPin1);
   OutputDeviceInterface<kPortC> obj2(Pin::kPin1, Pin::kPin2);
   InputDeviceInterface<kPortA>  inp1(Pin::kPin0);
   InputDeviceInterface<kPortA>  inp2(Pin::kPin4, Pin::kPin5);

   // 1] Set A1, A2, A3 as output pins
   avr::hal::gpio::OutputDeviceInterface<kPortA> obj3(Pin::kPin1, 
                                                      Pin::kPin2,
                                                      Pin::kPin3);
   // 2] Apply high voltage on A1, A2 and apply low voltage on A3
   obj3.SetHighVoltage(Pin::kPin1)
       .SetHighVoltage(Pin::kPin2)
       .SetLowVoltage(Pin::kPin3);

   while (1) {/* EMPTY */}
}

