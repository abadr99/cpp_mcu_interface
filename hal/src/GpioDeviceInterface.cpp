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

template <Port TPort>
void OutputDeviceInterface<TPort>::SetOutputPin(Pin pin) {
    using DS = DirectionState;
    #define X(Pin_)\
      case (k##Pin_): gpio_.template SetDirection<Pin::k##Pin_, DS::kOutput>();\
      break;

    switch (pin) {
        ATMEGA32_PINS
    }

    #undef X
}

template <Port TPort>
void OutputDeviceInterface<TPort>::SetHighPin(Pin pin) {
    using DL = DigitalLevel;
    #define X(Pin_)\
        case (k##Pin_): gpio_.template Write<Pin::k##Pin_, DL::kHigh>();\
        break;
    
    switch (pin) {
        ATMEGA32_PINS
    }

    #undef X
}

template <Port TPort>
void OutputDeviceInterface<TPort>::SetLowPin(Pin pin) {
    using DL = DigitalLevel;
    #define X(Pin_)\
        case (k##Pin_): gpio_.template Write<Pin::k##Pin_, DL::kLow>();\
        break;
    
    switch (pin) {
        ATMEGA32_PINS
    }
    
    #undef X
}

template <Port TPort>
OutputDeviceInterface<TPort>::OutputDeviceInterface(Pin pin) {
    SetOutputPin(pin);
}

template <Port TPort>
void OutputDeviceInterface<TPort>::SetHighVoltage(Pin pin) {
    SetHighPin(pin);
}

template <Port TPort>
void OutputDeviceInterface<TPort>::SetLowVoltage(Pin pin) {
    SetLowPin(pin);
}

template <Port TPort>
template<typename T, typename... Ts>
OutputDeviceInterface<TPort>::OutputDeviceInterface(T pin, Ts... pins) {
    SetOutputPin(pin);
    OutputDeviceInterface(pins...);
}

template <Port TPort>
template<typename T, typename... Ts>
void OutputDeviceInterface<TPort>::SetHighVoltage(T pin, Ts... pins) {
    SetHighPin(pin);
    SetHighVoltage(pins...);
}

template <Port TPort>
template<typename T, typename... Ts>
void OutputDeviceInterface<TPort>::SetLowVoltage(T pin, Ts... pins) {
    SetLowPin(pin);
    SetLowVoltage(pins...);
}

// =============================================================================
// ------------------Explicit template method instantiations-------------------
// =============================================================================
template class OutputDeviceInterface<Port::kPortA>;
template class OutputDeviceInterface<Port::kPortB>;
template class OutputDeviceInterface<Port::kPortC>;
template class OutputDeviceInterface<Port::kPortD>;
