#ifndef _BUZZER_H_
#define _BUZZER_H_


namespace avr {
namespace hal {
namespace buzzer {

enum OutputMode {
    kActiveLow,     /**< Indicates the device will be on with low signal>*/
    kActiveHigh,    /**< Indicates the device will be off with low signal>*/
};

enum Buzzerstate {
    kOff,
    kOn
};
template <avr::types::Port TPort, OutputMode M = OutputMode::kActiveHigh>
class Buzzer : public avr::hal::gpio::OutputDeviceInterface<TPort> {
public:
    Buzzer(avr::types::Pin pin);
    void TurnOn();
    void TurnOff();
    void Toggle();


private:
    avr::types::Pin buzzerPin_;
    Buzzerstate currentState_;
};

}}} // avr::hal::buzzer

#endif // _BUZZER_H_
