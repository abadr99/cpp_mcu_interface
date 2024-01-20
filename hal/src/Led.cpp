#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Gpio.h"
#include "GpioDeviceInterface.h"
#include "Led.h"

using namespace avr::types;
using namespace avr::mcal::gpio;
using namespace avr::hal;
using namespace avr::hal::led;

template <OutputMode M>
Led<M>::Led(Port port, Pin pin): gpio::OutputDeviceInterface(port),
                                 pin_(pin),
                                 currentState_(LedState::kOff)
{
    this->Init(pin);
}

template <OutputMode M>
void Led<M>::TurnOn() {
    using OM = OutputMode;
    switch (M) {
        case OM::kActiveLow:  this->SetLowVoltage(pin_);  break;
        case OM::kActiveHigh: this->SetHighVoltage(pin_); break;
    }
    currentState_ = LedState::kOn;
}

template <OutputMode M>
void Led<M>::TurnOff() {
    using OM = OutputMode;
    switch (M) {
        case OM::kActiveLow:  this->SetHighVoltage(pin_); break;
        case OM::kActiveHigh: this->SetLowVoltage(pin_);  break;
    }
    currentState_ = LedState::kOff;
}

template <OutputMode M>
void Led<M>::Toggle() {
    if (currentState_ == LedState::kOff) {
        TurnOn();
        currentState_ = LedState::kOn;
        return;
    }
    TurnOff();
    currentState_ = LedState::kOff;
}

template <OutputMode M>
bool Led<M>::IsOn() {
    return currentState_ == LedState::kOn;
}

template <OutputMode M>
bool Led<M>::IsOff() {
    return currentState_ == LedState::kOff;
}
