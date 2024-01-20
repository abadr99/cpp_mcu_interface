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

template <Port TPort, Pin TPin, OutputMode M>
Led<TPort, TPin, M>::Led(): gpio::OutputDeviceInterface<TPort>(),
                            currentState_(LedState::kOff)
{
    this->template Init<TPin>();
}

template <Port TPort, Pin TPin, OutputMode M>
void Led<TPort, TPin, M>::TurnOn() {
    using OM = OutputMode;
    switch (M) {
        case OM::kActiveLow:  this->template SetLowVoltage<TPin>();  break;
        case OM::kActiveHigh: this->template SetHighVoltage<TPin>(); break;
    }
    currentState_ = LedState::kOn;
}

template <Port TPort, Pin TPin, OutputMode M>
void Led<TPort, TPin, M>::TurnOff() {
    using OM = OutputMode;
    switch (M) {
        case OM::kActiveLow:  this->template SetHighVoltage<TPin>(); break;
        case OM::kActiveHigh: this->template SetLowVoltage<TPin>();  break;
    }
    currentState_ = LedState::kOff;
}

template <Port TPort, Pin TPin, OutputMode M>
void Led<TPort, TPin, M>::Toggle() {
    if (currentState_ == LedState::kOff) {
        TurnOn();
        currentState_ = LedState::kOn;
        return;
    }
    TurnOff();
    currentState_ = LedState::kOff;
}

template <Port TPort, Pin TPin, OutputMode M>
bool Led<TPort, TPin, M>::IsOn() {
    return currentState_ == LedState::kOn;
}

template <Port TPort, Pin TPin, OutputMode M>
bool Led<TPort, TPin, M>::IsOff() {
    return currentState_ == LedState::kOff;
}

// =============================================================================
// ------------------Explicit template method instantiations-------------------
// =============================================================================

#define X(port_, pin_)      template class Led<Port::k##port_, Pin::k##pin_, OutputMode::kActiveHigh>; //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)      template class Led<Port::k##port_, Pin::k##pin_, OutputMode::kActiveLow>; //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X
