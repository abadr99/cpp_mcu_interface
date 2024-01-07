#ifndef _ADC_DEVICE_INTERFACE_H_H
#define _ADC_DEVICE_INTERFACE_H_H

namespace avr {
namespace hal {
namespace adc {

// All ADC-Devices should inherit from this class
// @note: We should initialize ADC before using any adc device
template<avr::types::Pin TPin1, 
         avr::types::Pin TPin2 = avr::types::Pin::kNotConnected> 
class AdcDeviceInterface {
public:
    using volt_t = uint8_t;
    using pFun_t = void (*) ();
    AdcDeviceInterface();
    volt_t GetInputVoltage();
    volt_t GetInputVoltage(pFun_t pFuntion);
private:
};

}}} // avr::hal::adc

#endif // _ADC_DEVICE_INTERFACE_H_H
