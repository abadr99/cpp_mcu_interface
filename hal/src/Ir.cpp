#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Gpio.h"
#include "GpioDeviceInterface.h"
#include "Ir.h"

using namespace avr::types;
using namespace avr::mcal::gpio;
using namespace avr::hal;
using namespace avr::hal::ir;

template <avr::types::Port TPort, avr::types::Pin TPin>
Ir<TPort, TPin>::Ir() 
: gpio::InputDeviceInterface<TPort>(TPin),
  IrPin_(TPin)
{/* EMPTY */}

template <avr::types::Port TPort, avr::types::Pin TPin>
IrState Ir<TPort, TPin>::GetState() {
    using DL = DigitalLevel;
    return GetPinState<TPin>() == DL::kHigh ? IrState::kDetected 
                                            : IrState::kNotDetected;
}

// --- Template instantiation 
#define X(_pin)     template class Ir<Port::kPortA, Pin::k##_pin>;
    ATMEGA32_PINS
#undef X

#define X(_pin)     template class Ir<Port::kPortB, Pin::k##_pin>;
    ATMEGA32_PINS
#undef X

#define X(_pin)     template class Ir<Port::kPortC, Pin::k##_pin>;
    ATMEGA32_PINS
#undef X

#define X(_pin)     template class Ir<Port::kPortD, Pin::k##_pin>;
    ATMEGA32_PINS
#undef X
