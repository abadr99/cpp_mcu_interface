#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Gpio.h"
#include "GpioDeviceInterface.h"

// =============================================================================
// ----------------------------- namespaces ------------------------------------
// =============================================================================
using namespace avr::types;
using namespace avr::mcal::gpio;
using namespace avr::hal::gpio;

// =============================================================================
// ----------------- OutputDeviceInterface class impl --------------------------
// =============================================================================
OutputDeviceInterface::OutputDeviceInterface() { /* EMPTY */ }

OutputDeviceInterface& OutputDeviceInterface::Init(Port port, Pin pin) {
    using DS = Gpio::DirectionState;
    Gpio::SetPinDirection(port, pin, DS::kOutput);
    return *this;
}

OutputDeviceInterface& OutputDeviceInterface::SetHighVoltage(Port port, Pin pin) {
    using DL = Gpio::DigitalLevel;
    Gpio::WritePin(port, pin, DL::kHigh);
    return *this;
}

OutputDeviceInterface& OutputDeviceInterface::SetLowVoltage(Port port, Pin pin) {
    using DL = Gpio::DigitalLevel;
    Gpio::WritePin(port, pin, DL::kLow);
    return *this;
}

// =============================================================================
// --------------------- InputDeviceInterface impl ----------------------------
// =============================================================================
 
InputDeviceInterface::InputDeviceInterface() { /* EMPTY */ }

InputDeviceInterface& InputDeviceInterface::Init(Port port, Pin pin) {
    using DS = Gpio::DirectionState;
    Gpio::SetPinDirection(port, pin, DS::kInput);
    return *this;
}

typename InputDeviceInterface::DigitalLevel 
InputDeviceInterface::GetPinState(Port port, Pin pin) {
    return Gpio::ReadPin(port, pin);
}
