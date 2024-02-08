#ifndef _GPIO_DEVICE_INTERFACE_H_H
#define _GPIO_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace gpio {

// All digital output devices should inherit from this class
class OutputDeviceInterface {
protected:
    using Pin = avr::types::Pin;
    using Port = avr::types::Port;
    using DevicePin = utils::types::DevicePin;
    using AvrRegWidth = avr::types::AvrRegWidth;
    using DL = avr::mcal::gpio::Gpio::DigitalLevel;
    OutputDeviceInterface();
    void Init(DevicePin dp);
    void Init(Port port);
    void Init(Port port, Pin pin);
    void WritePort(Port port, AvrRegWidth val);
    void SetHighVoltage(DevicePin dp);
    void SetHighVoltage(Port port, Pin pin);
    void SetLowVoltage(DevicePin dp);
    void SetLowVoltage(Port port, Pin pin);
    void SetVoltage(DevicePin dp, DL val);
    void SetVoltage(Port port, Pin pin, DL val);
};

// All digital Input devices should inherit from this class
class InputDeviceInterface {
protected:
    using Pin = avr::types::Pin;
    using Port = avr::types::Port;
    using Gpio_t = avr::mcal::gpio::Gpio;
    using DigitalLevel = avr::mcal::gpio::Gpio::DigitalLevel;
    using DevicePin = utils::types::DevicePin;
    InputDeviceInterface();
    void Init(DevicePin dp);
    DigitalLevel GetPinState(DevicePin dp);
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H
