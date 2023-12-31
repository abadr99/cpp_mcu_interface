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
    void SetHighVoltage(avr::types::Pin pin);
    void SetLowVoltage(avr::types::Pin pin);

    template<typename... Ts>
    OutputDeviceInterface(Ts... pins);

    template<typename T, typename... Ts>
    void SetHighVoltage(T pin, Ts... pins);

    template<typename T, typename... Ts>
    void SetLowVoltage(T pin, Ts... pins);
private:
    avr::mcal::gpio::Gpio<TPort> gpio_;
    template<typename T>
    void helper_OutputDeviceInterface(T pin);
    template<typename T, typename... Ts>
    void helper_OutputDeviceInterface(T pin, Ts... pins);
    void SetOutputPin(avr::types::Pin pin);
    void SetHighPin(avr::types::Pin pin);
    void SetLowPin(avr::types::Pin pin);
};


// All digital Input devices should inherit from this class
template <avr::types::Port TPort>
class InputDeviceInterface {
public:
    // As we use template variadic methods then we should have the base case
    // for each method. 
    // See: https://en.cppreference.com/w/cpp/language/parameter_pack
    // NOTE: Base case should be before recursive case
    InputDeviceInterface(avr::types::Pin pin);

    template<typename T, typename... Ts>
    InputDeviceInterface(T pin, Ts... pins);

    template<avr::types::Pin TPin>
    avr::mcal::gpio::DigitalLevel GetPinState();
private:
    avr::mcal::gpio::Gpio<TPort> gpio_;
    void SetInputPin(avr::types::Pin pin);
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H
