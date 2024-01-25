#ifndef _GPIO_H_H
#define _GPIO_H_H
namespace avr {
namespace mcal {
namespace gpio{
// Wrapper for gpio methods
class Gpio {
public:
    using Port = avr::types::Port;
    using Pin = avr::types::Pin;
    using size = types::AvrRegWidth;
    enum DigitalLevel   {kLow, kHigh};
    enum DirectionState {kInput, kInputPullUp, kOutput};
    
    Gpio();
    
    static void SetPinDirection(Port port, Pin pin, DirectionState direction);
    static void SetPortDirection(Port port, size val);
    
    static void WritePin(Port port, Pin pin, DigitalLevel digitalVal);
    static void WritePort(Port port, size val);

    static DigitalLevel ReadPin(Port port, Pin pinNumber);    
    static size ReadPort(Port port);
};

}}} // avr::mcal::gpio


#endif // _GPIO_H_H
