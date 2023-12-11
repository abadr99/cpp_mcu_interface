#ifndef _GPIO_H_H
#define _GPIO_H_H

namespace avr {
namespace mcu {
namespace gpio{

template <avr::types::Port TPort>
class Gpio {
public:
    enum DigitalLevel{kLow, kHigh};
    enum DirectionState{kInput, kOutput};
    Gpio();
    
    /**
     * @brief Write a specific value to 'TPinNumber' at 'TPort'
     * 
     * @tparam pinNumber pin number that the voltage will be applied for
     * @param val voltage level kHigh OR kLow
     */
    // TODO(@abadr99): Support variadic templates for pinNumbers
    template <avr::types::Pin TPinNumber>
    void Write(DigitalLevel val);

    /**
     * @brief Read applied voltage at 'TPinNumber' at 'TPort'
     * 
     * @tparam TPinNumber 
     * @return DigitalLevel 
     */
    template<avr::types::Pin TPinNumber>
    DigitalLevel Read();
    
    /**
     * @brief Read applied voltage at 'TPort'
     * 
     * @return types::AvrRegWidth 
     */
    avr::types::AvrRegWidth Read();
    void Write(types::AvrRegWidth val);
    
    /**
     * @brief Set the Direction of 'TPinNumber' at 'TPort'
     * 
     * @tparam TPinNumber 
     * @tparam TdirectionState 
     */
    template<avr::types::Pin TPinNumber, DirectionState TdirectionState>
    void SetDirection();

    /**
     * @brief Set the Direction of 'TPort'
     * 
     * @param val 
     */
    void SetDirection(types::AvrRegWidth val);
private:
    struct GpioRegisters {
        utils::Register<avr::types::AvrRegWidth> port;
        utils::Register<avr::types::AvrRegWidth> ddr;
        utils::Register<avr::types::AvrRegWidth> pin;
        GpioRegisters(const avr::types::AvrRegWidth base_address);
    };
    GpioRegisters gpioRegisters_;
};

}}} // avr::mcu::gpio

#endif // _GPIO_H_H