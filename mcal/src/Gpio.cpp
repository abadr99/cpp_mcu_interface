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
template <Port TPort> 
template <Port UPort>
Gpio<TPort>::GpioRegisters<UPort>::GpioRegisters(const AvrRegWidth base_address)
:port_(Register<AvrRegWidth>(base_address)), 
 ddr_ (Register<AvrRegWidth>(base_address - 1)),
 pin_ (Register<AvrRegWidth>(base_address - 2))
{/* EMPTY */}


template <Port TPort>
template <Port UPort>
Gpio<TPort>::GpioRegisters<UPort>
Gpio<TPort>::GpioRegisters<UPort>::CreateGpioRegistersObj() {
    switch (TPort) {
        case Port::kPortA: return GpioRegisters<TPort>(GPIOA_BASE_ADDRESS);
        case Port::kPortB: return GpioRegisters<TPort>(GPIOB_BASE_ADDRESS);
        case Port::kPortC: return GpioRegisters<TPort>(GPIOC_BASE_ADDRESS);
        case Port::kPortD: return GpioRegisters<TPort>(GPIOD_BASE_ADDRESS);
    }
}

template <Port TPort> 
template <Port UPort>
typename Gpio<TPort>::template GpioRegisters<UPort>::Register_t& 
Gpio<TPort>::GpioRegisters<UPort>::GetPortRegister() {
    return port_;
}

template <Port TPort> 
template <Port UPort>
typename Gpio<TPort>::template GpioRegisters<UPort>::Register_t& 
Gpio<TPort>::GpioRegisters<UPort>::GetDdrRegister() {
    return ddr_;
}

template <Port TPort> 
template <Port UPort>
typename Gpio<TPort>::template GpioRegisters<UPort>::Register_t& 
Gpio<TPort>::GpioRegisters<UPort>::GetPinRegister() {
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
            gpioRegisters_.GetDdrRegister().template ClearBit<TPinNumber>(); 
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
    gpioRegisters_.GetDdrRegister().SetRegisterValue(val);
}

template <Port TPort>
template <Pin TPinNumber, DigitalLevel TDigitalVal>
void Gpio<TPort>::Write() {
    using DL = DigitalLevel;
    switch (TDigitalVal) {
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
    gpioRegisters_.GetPortRegister().SetRegisterValue(val);
}

template <Port TPort>
AvrRegWidth Gpio<TPort>::Read() {
    return gpioRegisters_.GetPortRegister().Read();
}

template <Port TPort>
template <Pin TPinNumber>
DigitalLevel Gpio<TPort>::Read() {
    return static_cast<DigitalLevel>(gpioRegisters_.GetPinRegister()
                                            .template ReadBit<TPinNumber>());
}

// TEMPLATE INSTANTIATION
template class Gpio<Port::kPortA>; 
template class Gpio<Port::kPortB>;
template class Gpio<Port::kPortC>;
template class Gpio<Port::kPortD>;

template class Gpio<Port::kPortA>::GpioRegisters<Port::kPortA>;
template class Gpio<Port::kPortB>::GpioRegisters<Port::kPortB>;
template class Gpio<Port::kPortC>::GpioRegisters<Port::kPortC>;
template class Gpio<Port::kPortD>::GpioRegisters<Port::kPortD>;

// TODO(@abadr99): Check if there are better implementation for 
//                 template instantiations 

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

#define X(port_, pin_)      T void Gpio<Port::k##port_>::Write<Pin::k##pin_, DigitalLevel::kLow>();  //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)      T void Gpio<Port::k##port_>::Write<Pin::k##pin_, DigitalLevel::kHigh>();  //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X

#define X(port_, pin_)      T DigitalLevel Gpio<Port::k##port_>::Read<Pin::k##pin_>();  //IGNORE-STYLE-CHECK[L004]
    ATMEGA32_PORT_PIN
#undef X

#undef T
