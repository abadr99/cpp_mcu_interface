#ifndef _LM35_H_
#define _LM35_H_

namespace avr {
namespace hal {
namespace temperature_sensor {
class Lm35 : avr::hal::adc::AdcDeviceInterface {
public:
    using temperature_t = float;
    using Pin  = avr::types::Pin;
    Lm35(Pin pin);
    temperature_t GetTemperature();
};

}}} // avr::hal::temperature_sensor

#endif // _LM35_H_
