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
GpioRegisters::GpioRegisters() : portReg_(0), ddrReg_(0), pinReg_(0)
{ /* EMPTY */ }

void GpioRegisters::SetRegisterAddresses(const size base_address) {
    portReg_ = Register<AvrRegWidth>(base_address);
    ddrReg_  = Register<AvrRegWidth>(base_address - 1);
    pinReg_  = Register<AvrRegWidth>(base_address - 2);
}

typename 
GpioRegisters::Register_t& GpioRegisters::GetPortRegister() { return portReg_; }

typename
GpioRegisters::Register_t& GpioRegisters::GetDdrRegister() { return ddrReg_; }

typename
GpioRegisters::Register_t& GpioRegisters::GetPinRegister() { return pinReg_; }

// -----------------------------------------------------------------------------
// Gpio class implementations
// -----------------------------------------------------------------------------

Gpio::Gpio(Port port) {
    switch (port) {
        case Port::kPortA: 
            gpioRegisters_.SetRegisterAddresses(GPIOA_BASE_ADDRESS);
            break;
        case Port::kPortB: 
            gpioRegisters_.SetRegisterAddresses(GPIOB_BASE_ADDRESS);
            break;
        case Port::kPortC: 
            gpioRegisters_.SetRegisterAddresses(GPIOC_BASE_ADDRESS);
            break;
        case Port::kPortD: 
            gpioRegisters_.SetRegisterAddresses(GPIOD_BASE_ADDRESS);
            break;
    }
}

void Gpio::SetPinDirection(Pin pinNumber, DirectionState directionState) {
    using DIR = DirectionState;
    switch (directionState) {
        case DIR::kInput :  
            gpioRegisters_.GetDdrRegister(). ClearBit(pinNumber); 
            gpioRegisters_.GetPortRegister().ClearBit(pinNumber); 
            break;
        case DIR::kOutput:  
            gpioRegisters_.GetDdrRegister().SetBit(pinNumber);
            break;
        case DIR::kInputPullUp: 
            gpioRegisters_.GetDdrRegister().ClearBit(pinNumber); 
            gpioRegisters_.GetPortRegister().SetBit(pinNumber);
            break;
    }
}

void Gpio::SetPortDirection(size val) {
    gpioRegisters_.GetDdrRegister().WriteRegister(val);
}

void Gpio::WritePin(Pin pinNumber, DigitalLevel digitalVal) {
    using DL = DigitalLevel;
    switch (digitalVal) {
        case DL::kHigh : 
            gpioRegisters_.GetPortRegister().SetBit(pinNumber);   
            break;
        case DL::kLow : 
            gpioRegisters_.GetPortRegister().ClearBit(pinNumber); 
            break;
    } 
}

void Gpio::WritePort(AvrRegWidth val) {
    gpioRegisters_.GetPortRegister().WriteRegister(val);
}

typename Gpio::DigitalLevel Gpio::ReadPin(Pin pinNumber) {
    return static_cast<DigitalLevel>(gpioRegisters_.GetPinRegister().ReadBit(pinNumber)); //IGNORE-STYLE-CHECK[L004] 
}

AvrRegWidth  Gpio::ReadPort() {
    return gpioRegisters_.GetPortRegister().ReadRegister();
}
