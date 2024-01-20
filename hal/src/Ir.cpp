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

Ir::Ir(Port port, Pin pin) : gpio::InputDeviceInterface(port), 
                             IrPin_(pin)
{/* EMPTY */}

typename
Ir::IRState Ir::GetState() {
    using DL = DigitalLevel;
    return GetPinState(IrPin_) == DL::kHigh ? IRState::kDetected 
                                            : IRState::kNotDetected;
}
