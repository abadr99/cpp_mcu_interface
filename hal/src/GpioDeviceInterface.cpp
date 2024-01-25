#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Helpers.h"
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

OutputDeviceInterface& OutputDeviceInterface::Init(DevicePin dp) {
    using DS = Gpio::DirectionState;
    Gpio::SetPinDirection(dp.port, dp.pin, DS::kOutput);
    return *this;
}

OutputDeviceInterface& OutputDeviceInterface::SetHighVoltage(DevicePin dp) {
    using DL = Gpio::DigitalLevel;
    Gpio::WritePin(dp.port, dp.pin, DL::kHigh);
    return *this;
}

OutputDeviceInterface& OutputDeviceInterface::SetLowVoltage(DevicePin dp) {
    using DL = Gpio::DigitalLevel;
    Gpio::WritePin(dp.port, dp.pin, DL::kLow);
    return *this;
}

// =============================================================================
// --------------------- InputDeviceInterface impl ----------------------------
// =============================================================================
 
InputDeviceInterface::InputDeviceInterface() { /* EMPTY */ }

InputDeviceInterface& InputDeviceInterface::Init(DevicePin dp) {
    using DS = Gpio::DirectionState;
    Gpio::SetPinDirection(dp.port, dp.pin, DS::kInput);
    return *this;
}

typename InputDeviceInterface::DigitalLevel 
InputDeviceInterface::GetPinState(DevicePin dp) {
    return Gpio::ReadPin(dp.port, dp.pin);
}
