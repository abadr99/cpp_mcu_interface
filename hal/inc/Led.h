#ifndef _LED_H_
#define _LED_H_


namespace avr {
namespace hal {
namespace led {

enum OutputMode {
    kActiveLow,     /**< Indicates the device will be on with low signal>*/
    kActiveHigh,    /**< Indicates the device will be off with low signal>*/
};

enum LedState {
    kOff,
    kOn
};

// TODO(@abadr99): Make LED pin as template parameter
template <avr::types::Port TPort, OutputMode M = OutputMode::kActiveHigh>
class Led : public avr::hal::gpio::OutputDeviceInterface<TPort> {
public:
    Led(avr::types::Pin pin);
    void TurnOn();
    void TurnOff();
    void Toggle();
    bool IsOn();
    bool IsOff();

private:
    avr::types::Pin ledPin_;
    LedState currentState_;
};

}}} // avr::hal::led

#endif // _LED_H_
