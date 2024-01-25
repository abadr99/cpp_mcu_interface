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
    OutputDeviceInterface();
    void Init(DevicePin dp);
    void Init(Port port);
    void WritePort(Port port, AvrRegWidth val);
    void SetHighVoltage(DevicePin dp);
    void SetLowVoltage(DevicePin dp);
    void SetVoltage(DevicePin dp, avr::mcal::gpio::Gpio::DigitalLevel val);
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
