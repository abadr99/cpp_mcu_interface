#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Gpio.h"

using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;

// -----------------------------------------------------------------------------
// GpioRegisters class implementations
// -----------------------------------------------------------------------------
template <Port UPort>
GpioRegisters<UPort>::GpioRegisters(const AvrRegWidth base_address)
    :port_(Register<AvrRegWidth>(base_address)), 
     ddr_ (Register<AvrRegWidth>(base_address - 1)),
     pin_ (Register<AvrRegWidth>(base_address - 2))
{/* EMPTY */}


template <Port UPort>
GpioRegisters<UPort> GpioRegisters<UPort>::CreateGpioRegistersObj() { 
    switch (UPort) {
        case Port::kPortA: return GpioRegisters<UPort>(GPIOA_BASE_ADDRESS);
        case Port::kPortB: return GpioRegisters<UPort>(GPIOB_BASE_ADDRESS);
        case Port::kPortC: return GpioRegisters<UPort>(GPIOC_BASE_ADDRESS);
        case Port::kPortD: return GpioRegisters<UPort>(GPIOD_BASE_ADDRESS);
    }
}

template <Port UPort>
typename 
GpioRegisters<UPort>::Register_t& GpioRegisters<UPort>::GetPortRegister() {
    return port_;
}

template <Port UPort>
typename
GpioRegisters<UPort>::Register_t& GpioRegisters<UPort>::GetDdrRegister() {
    return ddr_;
}

template <Port UPort>
typename
GpioRegisters<UPort>::Register_t& GpioRegisters<UPort>::GetPinRegister() {
    return pin_;
}

// -----------------------------------------------------------------------------
// Gpio class implementations
// -----------------------------------------------------------------------------
template <Port TPort>
Gpio<TPort>::Gpio() 
: gpioRegisters_(GpioRegisters<TPort>::CreateGpioRegistersObj())
{/* EMPTY */}

template <Port TPort>
template<Pin TPinNumber, DirectionState TDirectionState>
void Gpio<TPort>::SetDirection() {
    using DIR = DirectionState;
    switch (TDirectionState) {
        case DIR::kInput :  
            gpioRegisters_.GetDdrRegister(). template ClearBit<TPinNumber>(); 
            gpioRegisters_.GetPortRegister().template ClearBit<TPinNumber>(); 
            break;
        case DIR::kOutput:  
            gpioRegisters_.GetDdrRegister().template SetBit<TPinNumber>();
            break;
        case DIR::kInputPullUp: 
            gpioRegisters_.GetDdrRegister().template ClearBit<TPinNumber>(); 
            gpioRegisters_.GetPortRegister().template SetBit<TPinNumber>();
            break;
    }
}

template <Port TPort>
void Gpio<TPort>::SetDirection(types::AvrRegWidth val) {
    gpioRegisters_.GetDdrRegister().WriteRegister(val);
}

template <Port TPort>
template <Pin TPinNumber>
void Gpio<TPort>::Write(DigitalLevel digitalLevel) {
    using DL = DigitalLevel;
    switch (digitalLevel) {
        case DL::kHigh : 
            gpioRegisters_.GetPortRegister().template SetBit<TPinNumber>();   
            break;
        case DL::kLow : 
            gpioRegisters_.GetPortRegister().template ClearBit<TPinNumber>(); 
            break;
    } 
}

template <Port TPort>
void Gpio<TPort>::Write(AvrRegWidth val) {
    gpioRegisters_.GetPortRegister().WriteRegister(val);
}

template <Port TPort>
AvrRegWidth Gpio<TPort>::Read() {
    return gpioRegisters_.GetPortRegister().ReadRegister();
}

template <Port TPort>
template <Pin TPinNumber>
DigitalLevel Gpio<TPort>::Read() {
    return static_cast<DigitalLevel>(gpioRegisters_.GetPinRegister().template ReadBit<TPinNumber>()); //IGNORE-STYLE-CHECK[L004]
}

#define X(port_)    template class Gpio<Port::k##port_>;
    ATMEGA32_PORTS
#undef X

#define X(port_)    template class GpioRegisters<Port::k##port_>;
    ATMEGA32_PORTS
#undef X

#define T       template 

#define X(port_, pin_)      T void Gpio<Port::k##port_>::SetDirection<Pin::k##pin_, DirectionState::kInput>(); //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)      T void Gpio<Port::k##port_>::SetDirection<Pin::k##pin_, DirectionState::kInputPullUp>(); //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)      T void Gpio<Port::k##port_>::SetDirection<Pin::k##pin_, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)      T void Gpio<Port::k##port_>::Write<Pin::k##pin_>(DigitalLevel);  //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)      T DigitalLevel Gpio<Port::k##port_>::Read<Pin::k##pin_>();  //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X

#undef T
