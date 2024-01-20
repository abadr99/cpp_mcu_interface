#ifndef _GPIO_H_H
#define _GPIO_H_H

namespace avr {
namespace mcal {
namespace gpio{

enum DigitalLevel{kLow, kHigh};

enum DirectionState{
    kInput, 
    kInputPullUp,
    kOutput,
};
template <avr::types::Port UPort>
class GpioRegisters {
public:
    using Register_t = utils::Register<avr::types::AvrRegWidth>;
    explicit GpioRegisters(const avr::types::AvrRegWidth base_address);
    Register_t& GetPortRegister();
    Register_t& GetDdrRegister();
    Register_t& GetPinRegister();
    static GpioRegisters CreateGpioRegistersObj();
private:
    Register_t port_;
    Register_t ddr_;
    Register_t pin_;
};
template <avr::types::Port TPort>
class Gpio {
public:
    Gpio();
    using Pin = avr::types::Pin;
    
    template<Pin TPinNumber, DirectionState TDirectionState>
    void SetDirection();

    void SetDirection(types::AvrRegWidth val);
    template <Pin TPinNumber>
    void Write(DigitalLevel digitalVal);
    void Write(types::AvrRegWidth val);

    template<Pin TPinNumber>
    DigitalLevel Read();
    
    avr::types::AvrRegWidth Read();
private:
    GpioRegisters<TPort> gpioRegisters_;
};

}}} // avr::mcal::gpio


#endif // _GPIO_H_H
