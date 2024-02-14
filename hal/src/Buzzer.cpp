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

template <Port TPort>
Buzzer<TPort>::Buzzer(avr::types::Pin pin)
:gpio::OutputDeviceInterface<TPort>(pin),
 buzzerPin_(pin), 
 currentState_(Buzzerstate::kOff)
{/* EMPTY */}

template <Port TPort>
void Buzzer<TPort>::TurnOn() {
     
     this->SetHighVoltage(buzzerPin_);
     currentState_ = Buzzerstate::kOn;
}

template <Port TPort>
void Buzzer<TPort>::TurnOff() {
  
     this->SetLowVoltage(buzzerPin_);
     currentState_ = Buzzerstate::kOff;
}

template <Port TPort>
void Buzzer<TPort>::Toggle() {
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

#define X(port_)      template class Buzzer<Port::k##port_>; //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORTS
#undef X
