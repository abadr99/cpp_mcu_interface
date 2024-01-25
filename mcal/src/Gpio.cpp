#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Gpio.h"

#define PORTA                          (0x3B)
#define DDRA                           (0x3A)
#define PINA                           (0x39)
#define PORTB                          (0x38)
#define DDRB                           (0x37)
#define PINB                           (0x36)
#define PORTC                          (0x35)
#define DDRC                           (0x34)
#define PINC                           (0x33)
#define PORTD                          (0x32)
#define DDRD                           (0x31)
#define PIND                           (0x30)

using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;

// -----------------------------------------------------------------------------
// Gpio class implementations
// -----------------------------------------------------------------------------

static Register<AvrRegWidth> Get_DDR(Port p) {
    switch (p) {
        case kPortA: return Register<AvrRegWidth>(DDRA); 
        case kPortB: return Register<AvrRegWidth>(DDRB);
        case kPortC: return Register<AvrRegWidth>(DDRC);
        case kPortD: return Register<AvrRegWidth>(DDRD);
    }
    return Register<AvrRegWidth>(0);
}
static Register<AvrRegWidth> Get_PORT(Port p) {
    switch (p) {
        case kPortA: return Register<AvrRegWidth>(PORTA); 
        case kPortB: return Register<AvrRegWidth>(PORTB);
        case kPortC: return Register<AvrRegWidth>(PORTC);
        case kPortD: return Register<AvrRegWidth>(PORTD);
    }
    return Register<AvrRegWidth>(0);
}
static Register<AvrRegWidth> Get_PIN(Port p) {
    switch (p) {
        case kPortA: return Register<AvrRegWidth>(PINA); 
        case kPortB: return Register<AvrRegWidth>(PINB);
        case kPortC: return Register<AvrRegWidth>(PINC);
        case kPortD: return Register<AvrRegWidth>(PIND);
    }
    return Register<AvrRegWidth>(0);
}

Gpio::Gpio() { }

void Gpio::SetPinDirection(Port port, Pin pin, DirectionState direction) {
    using DIR = DirectionState;
    switch (direction) {
        case DIR::kInput :  
            Get_DDR(port). ClearBit(pin); 
            Get_PORT(port).ClearBit(pin); 
            break;
        case DIR::kOutput:  
            Get_DDR(port).SetBit(pin);
            break;
        case DIR::kInputPullUp: 
            Get_DDR(port).ClearBit(pin); 
            Get_PORT(port).SetBit(pin);
            break;
    }
}

void Gpio::SetPortDirection(Port port, size val) {
    Get_DDR(port).WriteRegister(val);
}

void Gpio::WritePin(Port port, Pin pin, DigitalLevel digitalVal) {
    using DL = DigitalLevel;
    switch (digitalVal) {
        case DL::kHigh : 
            Get_PORT(port).SetBit(pin);   
            break;
        case DL::kLow : 
            Get_PORT(port).ClearBit(pin); 
            break;
    } 
}

void Gpio::WritePort(Port port, size val) {
    Get_PORT(port).WriteRegister(val);
}

typename Gpio::DigitalLevel Gpio::ReadPin(Port port, Pin pin) {
    return static_cast<DigitalLevel>(Get_PIN(port).ReadBit(pin));
}

AvrRegWidth Gpio::ReadPort(Port port) {
    return Get_PORT(port).ReadRegister();
}

#undef PORTA
#undef DDRA
#undef PINA
#undef PORTB
#undef DDRB
#undef PINB
#undef PORTC
#undef DDRC
#undef PINC
#undef PORTD
#undef DDRD
#undef PIND
