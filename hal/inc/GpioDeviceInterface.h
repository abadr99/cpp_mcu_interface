#ifndef _GPIO_DEVICE_INTERFACE_H_H
#define _GPIO_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace gpio {

enum OutputMode {
    kActiveLow,     /**< Indicates the device will be on with low signal>*/
    kActiveHigh,    /**< Indicates the device will be off with low signal>*/
};

// All digital output devices should inherit from this class
template <avr::types::Port TPort, avr::types::Pin... TPins>
class OutputDeviceInterface {
public:
    OutputDeviceInterface();
    template <avr::types::Pin TPin, avr::hal::gpio::OutputMode M = kActiveLow>
    void TurnOn();
    template <avr::types::Pin TPin, avr::hal::gpio::OutputMode M = kActiveLow>
    void TurnOff();
private:
    avr::mcal::gpio::Gpio<TPort> gpio_;
};

}}} // avr::hal::gpio

#endif // _GPIO_DEVICE_INTERFACE_H_H