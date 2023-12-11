#include <stdint.h>
#include "atmega32.h"
#include "register.h"
#include "gpio.h"

using namespace utils;
using namespace avr::mcu::gpio;
using namespace avr::types;

template<Port TPort> 
Gpio<TPort>::GpioRegisters::GpioRegisters(const AvrRegWidth base_address):  
port(Register<AvrRegWidth>(base_address)),  
ddr (Register<AvrRegWidth>(base_address - 1)),
pin (Register<AvrRegWidth>(base_address - 2))
{/* EMPTY */}

template <Port TPort>
Gpio<TPort>::Gpio(){
    using PortType = avr::types::Port;
    switch(TPort) {
        case PortType::kPortA: gpioRegisters_(GPIOA_BASE_ADDRESS); break;
        case PortType::kPortB: gpioRegisters_(GPIOB_BASE_ADDRESS); break;
        case PortType::kPortC: gpioRegisters_(GPIOC_BASE_ADDRESS); break;
        case PortType::kPortD: gpioRegisters_(GPIOD_BASE_ADDRESS); break;
        default:                                                                   break;
    }
}

// template <Port TPort>
// template <Pin TPinNumber>
// void Gpio<TPort>::Write(DigitalLevel val) {
//     switch(val) {
//         case DigitalLevel::kHigh : gpioRegisters_->port.SetBit<TPinNumber>();   break;
//         case DigitalLevel::kLow  : gpioRegisters_->port.ClearBit<TPinNumber>(); break;
//         default                  :                                              break;
//     }
// }

template class Gpio<avr::types::Port::kPortA>;
template class Gpio<avr::types::Port::kPortB>;
template class Gpio<avr::types::Port::kPortC>;
template class Gpio<avr::types::Port::kPortD>;
