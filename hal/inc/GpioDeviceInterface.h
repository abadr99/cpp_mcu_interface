#ifndef _GPIO_DEVICE_INTERFACE_H_H
#define _GPIO_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace gpio {

// All digital output devices should inherit from this class

template <avr::types::Port TPort>
class OutputDeviceInterface {
public:
    OutputDeviceInterface();
    template<avr::types::Pin TPin> OutputDeviceInterface& Init();
    template<avr::types::Pin TPin> OutputDeviceInterface& SetHighVoltage();
    template<avr::types::Pin TPin> OutputDeviceInterface& SetLowVoltage();
private:
    avr::mcal::gpio::Gpio<TPort> gpio_;
};

// All digital Input devices should inherit from this class
template <avr::types::Port TPort>
class InputDeviceInterface {
public:
    InputDeviceInterface();
    template<avr::types::Pin TPin> InputDeviceInterface& Init();
    template<avr::types::Pin TPin>
    avr::mcal::gpio::DigitalLevel GetPinState();
private:
    avr::mcal::gpio::Gpio<TPort> gpio_;
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H
