#ifndef _GPIO_DEVICE_INTERFACE_H_H
#define _GPIO_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace gpio {

// All digital output devices should inherit from this class
template <avr::types::Port TPort>
class OutputDeviceInterface {
public:
    // As we use template variadic methods then we should have the base case
    // for each method. 
    // See: https://en.cppreference.com/w/cpp/language/parameter_pack
    // NOTE: Base case should be before recursive case
    OutputDeviceInterface(avr::types::Pin pin);
    void SetHighVoltage(avr::types::Pin pin);
    void SetLowVoltage(avr::types::Pin pin);

    template<typename T, typename... Ts>
    OutputDeviceInterface(T pin, Ts... pins);

    template<typename T, typename... Ts>
    void SetHighVoltage(T pin, Ts... pins);

    template<typename T, typename... Ts>
    void SetLowVoltage(T pin, Ts... pins);
private:
    avr::mcal::gpio::Gpio<TPort> gpio_;
    void SetOutputPin(avr::types::Pin pin);
    void SetHighPin(avr::types::Pin pin);
    void SetLowPin(avr::types::Pin pin);
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H
