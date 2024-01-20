#ifndef _GPIO_DEVICE_INTERFACE_H_H
#define _GPIO_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace gpio {

// All digital output devices should inherit from this class
class OutputDeviceInterface {
public:
    using Pin = avr::types::Pin;
    using Port = avr::types::Port;
    using Gpio_t = avr::mcal::gpio::Gpio;
    OutputDeviceInterface(Port port);
    OutputDeviceInterface& Init(Pin pin);
    OutputDeviceInterface& SetHighVoltage(Pin pin);
    OutputDeviceInterface& SetLowVoltage(Pin pin);
private:
    Gpio_t gpio_;
};

// All digital Input devices should inherit from this class
class InputDeviceInterface {
public:
    using Pin = avr::types::Pin;
    using Port = avr::types::Port;
    using Gpio_t = avr::mcal::gpio::Gpio;
    using DigitalLevel = avr::mcal::gpio::Gpio::DigitalLevel;
    InputDeviceInterface(Port port);
    InputDeviceInterface& Init(Pin pin);
    DigitalLevel GetPinState(Pin pin);
private:
    Gpio_t gpio_;
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H
