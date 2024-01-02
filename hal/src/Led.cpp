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
Led<TPort, M>::Led(Pin pin)
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

#define X(port_)      template class Led<Port::k##port_, OutputMode::kActiveHigh>; //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORTS
#undef X

#define X(port_)      template class Led<Port::k##port_, OutputMode::kActiveLow>; //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORTS
#undef X
