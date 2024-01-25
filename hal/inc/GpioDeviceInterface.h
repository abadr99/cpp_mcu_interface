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
    using DevicePin = utils::types::DevicePin;
    OutputDeviceInterface();
    OutputDeviceInterface& Init(DevicePin dp);
    OutputDeviceInterface& SetHighVoltage(DevicePin dp);
    OutputDeviceInterface& SetLowVoltage(DevicePin dp);
};

// All digital Input devices should inherit from this class
class InputDeviceInterface {
public:
    using Pin = avr::types::Pin;
    using Port = avr::types::Port;
    using Gpio_t = avr::mcal::gpio::Gpio;
    using DigitalLevel = avr::mcal::gpio::Gpio::DigitalLevel;
    using DevicePin = utils::types::DevicePin;
    InputDeviceInterface();
    InputDeviceInterface& Init(DevicePin dp);
    DigitalLevel GetPinState(DevicePin dp);
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H
