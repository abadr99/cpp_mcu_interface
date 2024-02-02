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

void OutputDeviceInterface::Init(DevicePin dp) {
    using DS = Gpio::DirectionState;
    Gpio::SetPinDirection(dp.port, dp.pin, DS::kOutput);
}

void OutputDeviceInterface::Init(Port port, Pin pin) {
    using DS = Gpio::DirectionState;
    Gpio::SetPinDirection(port, pin, DS::kOutput);
}

void OutputDeviceInterface::Init(Port port) {
    Gpio::SetPortDirection(port, 0xFF);
}

void OutputDeviceInterface::WritePort(Port port, AvrRegWidth val) { //IGNORE-STYLE-CHECK[L004]
    Gpio::WritePort(port, val);
}

void OutputDeviceInterface::SetHighVoltage(DevicePin dp) {
    using DL = Gpio::DigitalLevel;
    Gpio::WritePin(dp.port, dp.pin, DL::kHigh);
}

void OutputDeviceInterface::SetLowVoltage(DevicePin dp) {
    using DL = Gpio::DigitalLevel;
    Gpio::WritePin(dp.port, dp.pin, DL::kLow);
}

void OutputDeviceInterface::SetHighVoltage(Port port, Pin pin) {
    using DL = Gpio::DigitalLevel;
    Gpio::WritePin(port, pin, DL::kHigh);
}

void OutputDeviceInterface::SetLowVoltage(Port port, Pin pin) {
    using DL = Gpio::DigitalLevel;
    Gpio::WritePin(port, pin, DL::kLow);
}

void OutputDeviceInterface::SetVoltage(DevicePin dp, Gpio::DigitalLevel val) {
    Gpio::WritePin(dp.port, dp.pin, val);
}

void OutputDeviceInterface::SetVoltage(Port port, Pin pin, DL val) {
    Gpio::WritePin(port, pin, val);
}
// =============================================================================
// --------------------- InputDeviceInterface impl ----------------------------
// =============================================================================
 
InputDeviceInterface::InputDeviceInterface() { /* EMPTY */ }

void InputDeviceInterface::Init(DevicePin dp) {
    using DS = Gpio::DirectionState;
    Gpio::SetPinDirection(dp.port, dp.pin, DS::kInput);
}

typename InputDeviceInterface::DigitalLevel 
InputDeviceInterface::GetPinState(DevicePin dp) {
    return Gpio::ReadPin(dp.port, dp.pin);
}
