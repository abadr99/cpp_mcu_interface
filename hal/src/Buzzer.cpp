#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Gpio.h"
#include "GpioDeviceInterface.h"
#include "Buzzer.h"

using namespace avr::types;
using namespace avr::mcal::gpio;
using namespace avr::hal;
using namespace avr::hal::buzzer;

template <Port TPort, OutputMode M>
Buzzer<TPort, M>::Buzzer(avr::types::Pin pin)
:gpio::OutputDeviceInterface<TPort>(pin),
 buzzerPin_(pin), 
 currentState_(Buzzerstate::kOff)
{/* EMPTY */}

template <Port TPort, OutputMode M>
void Buzzer<TPort, M>::TurnOn() {
    using OM = OutputMode;
    switch (M) {
        case OM::kActiveLow:  this->SetLowVoltage(buzzerPin_);  break;
        case OM::kActiveHigh: this->SetHighVoltage(buzzerPin_); break;
    }
    currentState_ = Buzzerstate::kOn;
}

template <Port TPort, OutputMode M>
void Buzzer<TPort, M>::TurnOff() {
    using OM = OutputMode;
    switch (M) {
        case OM::kActiveLow:  this->SetHighVoltage(buzzerPin_); break;
        case OM::kActiveHigh: this->SetLowVoltage(buzzerPin_);  break;
    }
    currentState_ = Buzzerstate::kOff;
}

template <Port TPort, OutputMode M>
void Buzzer<TPort, M>::Toggle() {
    if (currentState_ == Buzzerstate::kOff) {
        TurnOn();
        currentState_ = Buzzerstate::kOn;
    }
    else {
        TurnOff();
        currentState_ = Buzzerstate::kOff;
    }
}

// =============================================================================
// ------------------Explicit template method instantiations-------------------
// =============================================================================
template class Buzzer<Port::kPortA, OutputMode::kActiveHigh>;
template class Buzzer<Port::kPortA, OutputMode::kActiveLow>;
template class Buzzer<Port::kPortB, OutputMode::kActiveHigh>;
template class Buzzer<Port::kPortB, OutputMode::kActiveLow>;
template class Buzzer<Port::kPortC, OutputMode::kActiveHigh>;
template class Buzzer<Port::kPortC, OutputMode::kActiveLow>;
template class Buzzer<Port::kPortD, OutputMode::kActiveHigh>;
template class Buzzer<Port::kPortD, OutputMode::kActiveLow>;
