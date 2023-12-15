#include <stdint.h>
#include "atmega32.h"
#include "register.h"
#include "gpio.h"

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
    return gpioRegisters_.GetPortRegister().GetRegisterValue();
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

template void Gpio<Port::kPortA>::SetDirection<Pin::kPin0, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin1, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin2, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin3, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin4, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin5, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin6, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin7, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin0, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin1, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin2, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin3, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin4, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin5, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin6, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin7, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin0, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin1, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin2, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin3, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin4, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin5, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin6, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortA>::SetDirection<Pin::kPin7, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]

template void Gpio<Port::kPortB>::SetDirection<Pin::kPin0, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin1, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin2, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin3, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin4, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin5, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin6, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin7, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin0, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin1, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin2, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin3, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin4, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin5, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin6, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin7, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin0, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin1, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin2, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin3, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin4, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin5, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin6, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortB>::SetDirection<Pin::kPin7, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]

template void Gpio<Port::kPortC>::SetDirection<Pin::kPin0, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin1, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin2, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin3, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin4, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin5, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin6, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin7, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin0, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin1, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin2, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin3, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin4, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin5, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin6, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin7, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin0, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin1, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin2, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin3, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin4, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin5, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin6, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortC>::SetDirection<Pin::kPin7, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]

template void Gpio<Port::kPortD>::SetDirection<Pin::kPin0, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin1, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin2, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin3, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin4, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin5, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin6, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin7, DirectionState::kInput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin0, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin1, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin2, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin3, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin4, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin5, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin6, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin7, DirectionState::kInputPullUp>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin0, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin1, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin2, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin3, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin4, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin5, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin6, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]
template void Gpio<Port::kPortD>::SetDirection<Pin::kPin7, DirectionState::kOutput>();  //IGNORE-STYLE-CHECK[L004]

template void Gpio<Port::kPortA>::Write<Pin::kPin0, DigitalLevel::kLow>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin1, DigitalLevel::kLow>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin2, DigitalLevel::kLow>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin3, DigitalLevel::kLow>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin4, DigitalLevel::kLow>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin5, DigitalLevel::kLow>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin6, DigitalLevel::kLow>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin7, DigitalLevel::kLow>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin0, DigitalLevel::kHigh>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin1, DigitalLevel::kHigh>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin2, DigitalLevel::kHigh>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin3, DigitalLevel::kHigh>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin4, DigitalLevel::kHigh>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin5, DigitalLevel::kHigh>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin6, DigitalLevel::kHigh>();  
template void Gpio<Port::kPortA>::Write<Pin::kPin7, DigitalLevel::kHigh>();  

template void Gpio<Port::kPortB>::Write<Pin::kPin0, DigitalLevel::kLow>();  
template void Gpio<Port::kPortB>::Write<Pin::kPin1, DigitalLevel::kLow>();  
template void Gpio<Port::kPortB>::Write<Pin::kPin2, DigitalLevel::kLow>();  
template void Gpio<Port::kPortB>::Write<Pin::kPin3, DigitalLevel::kLow>();  
template void Gpio<Port::kPortB>::Write<Pin::kPin4, DigitalLevel::kLow>();  
template void Gpio<Port::kPortB>::Write<Pin::kPin5, DigitalLevel::kLow>();  
template void Gpio<Port::kPortB>::Write<Pin::kPin6, DigitalLevel::kLow>();  
template void Gpio<Port::kPortB>::Write<Pin::kPin7, DigitalLevel::kLow>();  
template void Gpio<Port::kPortB>::Write<Pin::kPin0, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortB>::Write<Pin::kPin1, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortB>::Write<Pin::kPin2, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortB>::Write<Pin::kPin3, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortB>::Write<Pin::kPin4, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortB>::Write<Pin::kPin5, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortB>::Write<Pin::kPin6, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortB>::Write<Pin::kPin7, DigitalLevel::kHigh>(); 

template void Gpio<Port::kPortC>::Write<Pin::kPin0, DigitalLevel::kLow>();  
template void Gpio<Port::kPortC>::Write<Pin::kPin1, DigitalLevel::kLow>();  
template void Gpio<Port::kPortC>::Write<Pin::kPin2, DigitalLevel::kLow>();  
template void Gpio<Port::kPortC>::Write<Pin::kPin3, DigitalLevel::kLow>();  
template void Gpio<Port::kPortC>::Write<Pin::kPin4, DigitalLevel::kLow>();  
template void Gpio<Port::kPortC>::Write<Pin::kPin5, DigitalLevel::kLow>();  
template void Gpio<Port::kPortC>::Write<Pin::kPin6, DigitalLevel::kLow>();  
template void Gpio<Port::kPortC>::Write<Pin::kPin7, DigitalLevel::kLow>();  
template void Gpio<Port::kPortC>::Write<Pin::kPin0, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortC>::Write<Pin::kPin1, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortC>::Write<Pin::kPin2, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortC>::Write<Pin::kPin3, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortC>::Write<Pin::kPin4, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortC>::Write<Pin::kPin5, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortC>::Write<Pin::kPin6, DigitalLevel::kHigh>(); 
template void Gpio<Port::kPortC>::Write<Pin::kPin7, DigitalLevel::kHigh>(); 

template void Gpio<Port::kPortD>::Write<Pin::kPin0, DigitalLevel::kLow>();  
template void Gpio<Port::kPortD>::Write<Pin::kPin1, DigitalLevel::kLow>();  
template void Gpio<Port::kPortD>::Write<Pin::kPin2, DigitalLevel::kLow>();  
template void Gpio<Port::kPortD>::Write<Pin::kPin3, DigitalLevel::kLow>();  
template void Gpio<Port::kPortD>::Write<Pin::kPin4, DigitalLevel::kLow>();  
template void Gpio<Port::kPortD>::Write<Pin::kPin5, DigitalLevel::kLow>();  
template void Gpio<Port::kPortD>::Write<Pin::kPin6, DigitalLevel::kLow>();  
template void Gpio<Port::kPortD>::Write<Pin::kPin7, DigitalLevel::kLow>();  
template void Gpio<Port::kPortD>::Write<Pin::kPin0, DigitalLevel::kHigh>();
template void Gpio<Port::kPortD>::Write<Pin::kPin1, DigitalLevel::kHigh>();
template void Gpio<Port::kPortD>::Write<Pin::kPin2, DigitalLevel::kHigh>();
template void Gpio<Port::kPortD>::Write<Pin::kPin3, DigitalLevel::kHigh>();
template void Gpio<Port::kPortD>::Write<Pin::kPin4, DigitalLevel::kHigh>();
template void Gpio<Port::kPortD>::Write<Pin::kPin5, DigitalLevel::kHigh>();
template void Gpio<Port::kPortD>::Write<Pin::kPin6, DigitalLevel::kHigh>();
template void Gpio<Port::kPortD>::Write<Pin::kPin7, DigitalLevel::kHigh>();

template DigitalLevel Gpio<Port::kPortA>::Read<Pin::kPin0>();
template DigitalLevel Gpio<Port::kPortA>::Read<Pin::kPin1>();
template DigitalLevel Gpio<Port::kPortA>::Read<Pin::kPin2>();
template DigitalLevel Gpio<Port::kPortA>::Read<Pin::kPin3>();
template DigitalLevel Gpio<Port::kPortA>::Read<Pin::kPin4>();
template DigitalLevel Gpio<Port::kPortA>::Read<Pin::kPin5>();
template DigitalLevel Gpio<Port::kPortA>::Read<Pin::kPin6>();
template DigitalLevel Gpio<Port::kPortA>::Read<Pin::kPin7>();

template DigitalLevel Gpio<Port::kPortB>::Read<Pin::kPin0>();
template DigitalLevel Gpio<Port::kPortB>::Read<Pin::kPin1>();
template DigitalLevel Gpio<Port::kPortB>::Read<Pin::kPin2>();
template DigitalLevel Gpio<Port::kPortB>::Read<Pin::kPin3>();
template DigitalLevel Gpio<Port::kPortB>::Read<Pin::kPin4>();
template DigitalLevel Gpio<Port::kPortB>::Read<Pin::kPin5>();
template DigitalLevel Gpio<Port::kPortB>::Read<Pin::kPin6>();
template DigitalLevel Gpio<Port::kPortB>::Read<Pin::kPin7>();

template DigitalLevel Gpio<Port::kPortC>::Read<Pin::kPin0>();
template DigitalLevel Gpio<Port::kPortC>::Read<Pin::kPin1>();
template DigitalLevel Gpio<Port::kPortC>::Read<Pin::kPin2>();
template DigitalLevel Gpio<Port::kPortC>::Read<Pin::kPin3>();
template DigitalLevel Gpio<Port::kPortC>::Read<Pin::kPin4>();
template DigitalLevel Gpio<Port::kPortC>::Read<Pin::kPin5>();
template DigitalLevel Gpio<Port::kPortC>::Read<Pin::kPin6>();
template DigitalLevel Gpio<Port::kPortC>::Read<Pin::kPin7>();

template DigitalLevel Gpio<Port::kPortD>::Read<Pin::kPin0>();
template DigitalLevel Gpio<Port::kPortD>::Read<Pin::kPin1>();
template DigitalLevel Gpio<Port::kPortD>::Read<Pin::kPin2>();
template DigitalLevel Gpio<Port::kPortD>::Read<Pin::kPin3>();
template DigitalLevel Gpio<Port::kPortD>::Read<Pin::kPin4>();
template DigitalLevel Gpio<Port::kPortD>::Read<Pin::kPin5>();
template DigitalLevel Gpio<Port::kPortD>::Read<Pin::kPin6>();
template DigitalLevel Gpio<Port::kPortD>::Read<Pin::kPin7>();
