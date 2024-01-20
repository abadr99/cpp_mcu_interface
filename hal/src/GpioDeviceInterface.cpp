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
OutputDeviceInterface<TPort>::OutputDeviceInterface() {}

template <Port TPort>
template<Pin TPin> 
OutputDeviceInterface<TPort>& OutputDeviceInterface<TPort>::Init() {
    gpio_.template SetDirection<TPin, DirectionState::kOutput>();
    return *this;
}

template <Port TPort>
template<Pin TPin>  
OutputDeviceInterface<TPort>& OutputDeviceInterface<TPort>::SetHighVoltage() {
    gpio_.template Write<TPin>(DigitalLevel::kHigh);
    return *this;
}

template <Port TPort>
template<Pin TPin>  
OutputDeviceInterface<TPort>& OutputDeviceInterface<TPort>::SetLowVoltage() {
    gpio_.template Write<TPin>(DigitalLevel::kLow);
    return *this;
}
// =============================================================================
// ------------------Explicit template method instantiations-------------------
// =============================================================================
#define X(port_)    template class OutputDeviceInterface<Port::k##port_>;
ATMEGA32_PORTS
#undef X

#define X(port_, pin_)\
    template OutputDeviceInterface<Port::k##port_>& OutputDeviceInterface<Port::k##port_>::Init<Pin::k##pin_>(); //IGNORE-STYLE-CHECK[L004]
ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)\
    template OutputDeviceInterface<Port::k##port_>& OutputDeviceInterface<Port::k##port_>::SetHighVoltage<Pin::k##pin_>(); //IGNORE-STYLE-CHECK[L004]
ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)\
    template OutputDeviceInterface<Port::k##port_>& OutputDeviceInterface<Port::k##port_>::SetLowVoltage<Pin::k##pin_>(); //IGNORE-STYLE-CHECK[L004]
ATMEGA32_PORT_PIN
#undef X

// =============================================================================
// --------------------- InputDeviceInterface impl ----------------------------
// =============================================================================
template <Port TPort> 
InputDeviceInterface<TPort>::InputDeviceInterface() { }

template <Port TPort> 
template<Pin TPin> 
InputDeviceInterface<TPort>& InputDeviceInterface<TPort>::Init() {
    gpio_.template SetDirection<TPin, DirectionState::kInput>();
    return *this;
}

template <Port TPort> 
template<Pin TPin>
DigitalLevel InputDeviceInterface<TPort>::GetPinState() {
    return gpio_.template Read<TPin>();
}
// =============================================================================
// ------------------Explicit template method instantiations-------------------
// =============================================================================

#define X(port_)    template class InputDeviceInterface<Port::k##port_>;
ATMEGA32_PORTS
#undef X

#define X(port_, pin_)\
    template InputDeviceInterface<Port::k##port_>& InputDeviceInterface<Port::k##port_>::Init<Pin::k##pin_>(); //IGNORE-STYLE-CHECK[L004]
ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)\
    template DigitalLevel InputDeviceInterface<Port::k##port_>::GetPinState<Pin::k##pin_>(); //IGNORE-STYLE-CHECK[L004]
ATMEGA32_PORT_PIN
#undef X
