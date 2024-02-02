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
    using DevicePin = utils::types::DevicePin;
    Led(DevicePin dp);
    void TurnOn();
    void TurnOff();
    void Toggle();
    bool IsOn();
    bool IsOff();
private:
    DevicePin pin_;
    LedState  currentState_;
};

}}} // avr::hal::led

#endif // _LED_H_
