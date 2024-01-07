#ifndef _ADC_DEVICE_INTERFACE_H_H
#define _ADC_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace adc {

// All ADC-Devices should inherit from this class
// @note: We should initialize ADC before using any adc device
template <avr::types::Pin TPin1, avr::types::Pin TPin2 = avr::types::Pin::kNotConnected> //IGNORE-STYLE-CHECK[L004]
class AdcDeviceInterface {
public:
    using volt_t = float;
    using pFun_t = void (*) ();
    using pin_t = avr::types::Pin;
    AdcDeviceInterface();
    volt_t GetInputVoltage(pFun_t pFunction = nullptr);
private:

};

}}} // avr::hal::adc

#endif // _ADC_DEVICE_INTERFACE_H_H
