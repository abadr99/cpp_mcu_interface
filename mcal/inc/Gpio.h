#ifndef _GPIO_H_H
#define _GPIO_H_H

#define GPIOA_BASE_ADDRESS             (0x3B)
#define GPIOB_BASE_ADDRESS             (0x38)
#define GPIOC_BASE_ADDRESS             (0x35)
#define GPIOD_BASE_ADDRESS             (0x32)
namespace avr {
namespace mcal {
namespace gpio{

class GpioRegisters {
public:
    using size = avr::types::AvrRegWidth;
    using Register_t = utils::Register<size>;
    GpioRegisters();
    void SetRegisterAddresses(const avr::types::AvrRegWidth base_address);
    Register_t& GetPortRegister();
    Register_t& GetDdrRegister();
    Register_t& GetPinRegister();
private:
    Register_t portReg_;
    Register_t ddrReg_;
    Register_t pinReg_;
};

// As many cases of GPIO we shouldn't template any parameter to save more 
// memory 
class Gpio {
public:
    using Port = avr::types::Port;
    using Pin = avr::types::Pin;
    using size = types::AvrRegWidth;
    enum DigitalLevel   {kLow, kHigh};
    enum DirectionState {kInput, kInputPullUp, kOutput};
    
    Gpio(Port port);
    
    void SetPinDirection(Pin pinNumber, DirectionState directionState);
    void SetPortDirection(size val);
    
    void WritePin(Pin pinNumber, DigitalLevel digitalVal);
    void WritePort(size val);

    DigitalLevel ReadPin(Pin pinNumber);    
    size ReadPort();
private:
    GpioRegisters gpioRegisters_;
};

}}} // avr::mcal::gpio


#endif // _GPIO_H_H
