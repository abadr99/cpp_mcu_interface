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

template <Port TPort, OutputMode M>
Led<TPort, M>::Led(avr::types::Pin pin)
:gpio::OutputDeviceInterface<TPort>(pin),
 ledPin_(pin), 
 currentState_(LedState::kOff)
{/* EMPTY */}

template <Port TPort, OutputMode M>
void Led<TPort, M>::TurnOn() {
    using OM = OutputMode;
    switch (M) {
        case OM::kActiveLow:  this->SetLowVoltage(ledPin_);  break;
        case OM::kActiveHigh: this->SetHighVoltage(ledPin_); break;
    }
    currentState_ = LedState::kOn;
}

template <Port TPort, OutputMode M>
void Led<TPort, M>::TurnOff() {
    using OM = OutputMode;
    switch (M) {
        case OM::kActiveLow:  this->SetHighVoltage(ledPin_); break;
        case OM::kActiveHigh: this->SetLowVoltage(ledPin_);  break;
    }
    currentState_ = LedState::kOff;
}

template <Port TPort, OutputMode M>
void Led<TPort, M>::Toggle() {
    if (currentState_ == LedState::kOff) {
        TurnOn();
        currentState_ = LedState::kOn;
    }
    else {
        TurnOff();
        currentState_ = LedState::kOff;
    }
}

template <Port TPort, OutputMode M>
bool Led<TPort, M>::IsOn() {
    return currentState_ == LedState::kOn;
}

template <Port TPort, OutputMode M>
bool Led<TPort, M>::IsOff() {
    return currentState_ == LedState::kOff;
}

// =============================================================================
// ------------------Explicit template method instantiations-------------------
// =============================================================================
template class Led<Port::kPortA, OutputMode::kActiveHigh>;
template class Led<Port::kPortA, OutputMode::kActiveLow>;
template class Led<Port::kPortB, OutputMode::kActiveHigh>;
template class Led<Port::kPortB, OutputMode::kActiveLow>;
template class Led<Port::kPortC, OutputMode::kActiveHigh>;
template class Led<Port::kPortC, OutputMode::kActiveLow>;
template class Led<Port::kPortD, OutputMode::kActiveHigh>;
template class Led<Port::kPortD, OutputMode::kActiveLow>;
