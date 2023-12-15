#ifndef _GPIO_H_H
#define _GPIO_H_H

namespace avr {
namespace mcu {
namespace gpio{

enum DigitalLevel{kLow, kHigh};

enum DirectionState{kInput, kOutput};
template <avr::types::Port TPort>
class Gpio {
public:
    Gpio();

    /**
     * @brief Set the Direction of 'TPinNumber' at 'TPort'
     * 
     * @tparam TPinNumber 
     * @tparam TdirectionState 
     */
    template<avr::types::Pin TPinNumber, DirectionState TDirectionState>
    void SetDirection();

    /**
     * @brief Set the Direction of 'TPort'
     * 
     * @param val 
     */
    void SetDirection(types::AvrRegWidth val);

    /**
     * @brief Write a specific value to 'TPinNumber' at 'TPort'
     * 
     * @tparam pinNumber pin number that the voltage will be applied for
     * @param val voltage level kHigh OR kLow
     */
    // TODO(@abadr99): Support variadic templates for pinNumbers
    template <avr::types::Pin TPinNumber, 
              DigitalLevel TDigitalVal>
    void Write();
    void Write(types::AvrRegWidth val);

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
private:
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
    GpioRegisters<TPort> gpioRegisters_;
};

}}} // avr::mcu::gpio

#endif // _GPIO_H_H
