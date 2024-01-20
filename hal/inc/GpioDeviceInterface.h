#ifndef _GPIO_DEVICE_INTERFACE_H_H
#define _GPIO_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace gpio {

// All digital output devices should inherit from this class

template <avr::types::Port TPort>
class OutputDeviceInterface {
public:
    using Pin = avr::types::Pin;
    using Gpio_t = avr::mcal::gpio::Gpio<TPort>;
    OutputDeviceInterface();
    template<Pin TPin> OutputDeviceInterface& Init();
    template<Pin TPin> OutputDeviceInterface& SetHighVoltage();
    template<Pin TPin> OutputDeviceInterface& SetLowVoltage();
private:
    Gpio_t gpio_;
};

// All digital Input devices should inherit from this class
template <avr::types::Port TPort>
class InputDeviceInterface {
public:
    using Pin = avr::types::Pin;
    using Gpio_t = avr::mcal::gpio::Gpio<TPort>;
    using DigitalLevel = avr::mcal::gpio::DigitalLevel;
    InputDeviceInterface();
    template<Pin TPin> InputDeviceInterface& Init();
    template<Pin TPin>
    DigitalLevel GetPinState();
private:
    Gpio_t gpio_;
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H
