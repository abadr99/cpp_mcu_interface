#ifndef _LED_H_
#define _LED_H_


namespace avr {
namespace hal {
namespace led {

enum OutputMode {
    kActiveLow,    /**< Indicates the device will be on with low signal>*/
    kActiveHigh,   /**< Indicates the device will be off with low signal>*/
};
template <OutputMode M = OutputMode::kActiveHigh>
class Led : public avr::hal::gpio::OutputDeviceInterface {
public:
    enum LedState { kOff, kOn };
    using Port = avr::types::Port;
    using Pin  = avr::types::Pin;
    Led(Port port, Pin pin);
    void TurnOn();
    void TurnOff();
    void Toggle();
    bool IsOn();
    bool IsOff();
private:
    Pin pin_;
    LedState currentState_;
};

}}} // avr::hal::led

#endif // _LED_H_
