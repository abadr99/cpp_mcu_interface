#ifndef _BUZZER_H_
#define _BUZZER_H_


namespace avr {
namespace hal {
namespace buzzer {


enum Buzzerstate {
    kOff,
    kOn
};
template <avr::types::Port TPort>
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
