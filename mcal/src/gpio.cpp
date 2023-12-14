#include <stdint.h>
#include "atmega32.h"
#include "register.h"
#include "gpio.h"

using namespace utils;
using namespace avr::mcu::gpio;
using namespace avr::types;

template <Port TPort> 
template <Port UPort>
Gpio<TPort>::GpioRegisters<UPort>::GpioRegisters(const AvrRegWidth base_address):  
port_(Register<AvrRegWidth>(base_address)),  
ddr_ (Register<AvrRegWidth>(base_address - 1)),
pin_ (Register<AvrRegWidth>(base_address - 2))
{/* EMPTY */}


template <Port TPort>
template <Port UPort>
Gpio<TPort>::GpioRegisters<UPort> Gpio<TPort>::GpioRegisters<UPort>::CreateGpioRegistersObj() {
    switch(TPort) {
        case Port::kPortA: return GpioRegisters<TPort>(GPIOA_BASE_ADDRESS);
        case Port::kPortB: return GpioRegisters<TPort>(GPIOB_BASE_ADDRESS);
        case Port::kPortC: return GpioRegisters<TPort>(GPIOC_BASE_ADDRESS);
        case Port::kPortD: return GpioRegisters<TPort>(GPIOD_BASE_ADDRESS);
    }
}

template <Port TPort> 
template <Port UPort>
typename Gpio<TPort>::template GpioRegisters<UPort>::Register_t& Gpio<TPort>::GpioRegisters<UPort>::GetPortRegister() {
    return port_;
}

template <Port TPort> 
template <Port UPort>
typename Gpio<TPort>::template GpioRegisters<UPort>::Register_t& Gpio<TPort>::GpioRegisters<UPort>::GetDdrRegister() {
    return ddr_;
}

template <Port TPort> 
template <Port UPort>
typename Gpio<TPort>::template GpioRegisters<UPort>::Register_t& Gpio<TPort>::GpioRegisters<UPort>::GetPinRegister() {
    return pin_;
}

template <Port TPort>
Gpio<TPort>::Gpio() : gpioRegisters_(GpioRegisters<TPort>::CreateGpioRegistersObj())
{/* EMPTY */}

template <Port TPort>
template <Pin TPinNumber, typename Gpio<TPort>::DigitalLevel TDigitalVal>
void Gpio<TPort>::Write() {
    switch(TDigitalVal) {
        case Gpio<TPort>::DigitalLevel::kHigh : gpioRegisters_.GetPortRegister().template SetBit<TPinNumber>();   break;
        case Gpio<TPort>::DigitalLevel::kLow  : gpioRegisters_.GetPortRegister().template ClearBit<TPinNumber>(); break;
    } 
}


// TEMPLATE INSTANTIATION
template class Gpio<avr::types::Port::kPortA>;
template class Gpio<avr::types::Port::kPortB>;
template class Gpio<avr::types::Port::kPortC>;
template class Gpio<avr::types::Port::kPortD>;

template class Gpio<avr::types::Port::kPortA>::GpioRegisters<avr::types::Port::kPortA>;
template class Gpio<avr::types::Port::kPortB>::GpioRegisters<avr::types::Port::kPortB>;
template class Gpio<avr::types::Port::kPortC>::GpioRegisters<avr::types::Port::kPortC>;
template class Gpio<avr::types::Port::kPortD>::GpioRegisters<avr::types::Port::kPortD>;