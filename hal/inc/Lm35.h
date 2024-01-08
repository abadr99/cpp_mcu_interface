#ifndef _LM35_H_
#define _LM35_H_

namespace avr {
namespace hal {
namespace temperature_sensor {

template <avr::types::Pin TPin1>
class Lm35 : avr::hal::adc::AdcDeviceInterface<TPin1> {
public:
    using temperature_t = float;
    Lm35();
    temperature_t GetTemperature();
};

}}} // avr::hal::temperature_sensor

#endif // _LM35_H_
