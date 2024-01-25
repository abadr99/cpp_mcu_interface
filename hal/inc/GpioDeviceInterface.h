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
    OutputDeviceInterface();
    OutputDeviceInterface& Init(Port port, Pin pin);
    OutputDeviceInterface& SetHighVoltage(Port port, Pin pin);
    OutputDeviceInterface& SetLowVoltage(Port port, Pin pin);
};

// All digital Input devices should inherit from this class
class InputDeviceInterface {
public:
    using Pin = avr::types::Pin;
    using Port = avr::types::Port;
    using Gpio_t = avr::mcal::gpio::Gpio;
    using DigitalLevel = avr::mcal::gpio::Gpio::DigitalLevel;
    InputDeviceInterface();
    InputDeviceInterface& Init(Port port, Pin pin);
    DigitalLevel GetPinState(Port port, Pin pin);
private:
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H
