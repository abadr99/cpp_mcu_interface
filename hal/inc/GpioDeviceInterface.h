#ifndef _GPIO_DEVICE_INTERFACE_H_H
#define _GPIO_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace gpio {

// All digital output devices should inherit from this class
template <avr::types::Port TPort>
class OutputDeviceInterface {
public:
    template<typename... Ts>
    OutputDeviceInterface(Ts... pins);

    OutputDeviceInterface& SetHighVoltage(avr::types::Pin pin);
    OutputDeviceInterface& SetLowVoltage(avr::types::Pin pin);
private:
    avr::mcal::gpio::Gpio<TPort> gpio_;
    template<typename T>
    void helper_OutputDeviceInterface(T pin);
    template<typename T, typename... Ts>
    void helper_OutputDeviceInterface(T pin, Ts... pins);
    void SetOutputPin(avr::types::Pin pin);
};


// All digital Input devices should inherit from this class
template <avr::types::Port TPort>
class InputDeviceInterface {
public:
    // As we use template variadic methods then we should have the base case
    // for each method. 
    // See: https://en.cppreference.com/w/cpp/language/parameter_pack
    // NOTE: Base case should be before recursive case
    template<typename... Ts>
    InputDeviceInterface(Ts... pins);
    avr::mcal::gpio::DigitalLevel GetPinState(avr::types::Pin pin);
private:
    avr::mcal::gpio::Gpio<TPort> gpio_;
    void SetInputPin(avr::types::Pin pin);
    template<typename T>
    void helper_InputDeviceInterface(T pin);
    template<typename T, typename... Ts>
    void helper_InputDeviceInterface(T pin, Ts... pins);
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H
