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
OutputDeviceInterface::OutputDeviceInterface(Port port): gpio_(port) {}

OutputDeviceInterface& OutputDeviceInterface::Init(Pin pin) {
    using DS = Gpio::DirectionState;
    gpio_.SetPinDirection(pin, DS::kOutput);
    return *this;
}

OutputDeviceInterface& OutputDeviceInterface::SetHighVoltage(Pin pin) {
    using DL = Gpio::DigitalLevel;
    gpio_.WritePin(pin, DL::kHigh);
    return *this;
}

OutputDeviceInterface& OutputDeviceInterface::SetLowVoltage(Pin pin) {
    using DL = Gpio::DigitalLevel;
    gpio_.WritePin(pin, DL::kLow);
    return *this;
}

// =============================================================================
// --------------------- InputDeviceInterface impl ----------------------------
// =============================================================================
 
InputDeviceInterface::InputDeviceInterface(Port port): gpio_(port) { }

InputDeviceInterface& InputDeviceInterface::Init(Pin pin) {
    using DS = Gpio::DirectionState;
    gpio_.SetPinDirection(pin, DS::kInput);
    return *this;
}

typename
InputDeviceInterface::DigitalLevel InputDeviceInterface::GetPinState(Pin pin) {
    return gpio_.ReadPin(pin);
}
