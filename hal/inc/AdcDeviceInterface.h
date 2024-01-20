#ifndef _ADC_DEVICE_INTERFACE_H_H
#define _ADC_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace adc {

// All ADC-Devices should inherit from this class
// @note: We should initialize ADC before using any adc device
class AdcDeviceInterface {
public:
    using volt_t = float;
    using pFun_t = void (*) ();
    using pin_t = avr::types::Pin;
    AdcDeviceInterface(const pin_t pin1, 
                       const pin_t pin2 = pin_t::kNotConnected);
    volt_t GetInputVoltage(pFun_t pFunction = nullptr);
private:
    pin_t pins[2];
};

}}} // avr::hal::adc

#endif // _ADC_DEVICE_INTERFACE_H_H
