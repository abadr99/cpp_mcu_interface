#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Adc.h"
#include "AdcDeviceInterface.h"

using namespace avr::mcal::adc;
using namespace avr::hal::adc;
using avr::types::Pin;


template <avr::types::Pin TPin1, avr::types::Pin TPin2>
AdcDeviceInterface<TPin1, TPin2>::AdcDeviceInterface() {/* EMPTY */}

template <avr::types::Pin TPin1, avr::types::Pin TPin2>
typename AdcDeviceInterface<TPin1, TPin2>::volt_t
AdcDeviceInterface<TPin1, TPin2>::GetInputVoltage(pFun_t pFunction) {
    using CM = avr::mcal::adc::ChannelMode;
    // Select Channel according to device pins
    if (TPin2 == pin_t::kNotConnected) {
      switch (TPin1) {
        case pin_t::kPin0: ADC.SelectChannel<CM::kSingleEnded_ADC0>(); break;
        case pin_t::kPin1: ADC.SelectChannel<CM::kSingleEnded_ADC1>(); break;
        case pin_t::kPin2: ADC.SelectChannel<CM::kSingleEnded_ADC2>(); break;
        case pin_t::kPin3: ADC.SelectChannel<CM::kSingleEnded_ADC3>(); break;
        case pin_t::kPin4: ADC.SelectChannel<CM::kSingleEnded_ADC4>(); break;
        case pin_t::kPin5: ADC.SelectChannel<CM::kSingleEnded_ADC5>(); break;
        case pin_t::kPin6: ADC.SelectChannel<CM::kSingleEnded_ADC6>(); break;
        case pin_t::kPin7: ADC.SelectChannel<CM::kSingleEnded_ADC7>(); break;
      }
    }
    else {
        // TODO(@abadr99): Support differential modes. For now if we need to 
        // use differential mode then we can use the following algorithm as a 
        // workaround until be supported.
        // AdcDeviceInterface<kPin0, kPin1> adc_device;
        // ADC.SelectChannel<DIFFERENTIAL_MODE>();
        // volt_t volt = adc_device.GetInputVoltage();
    }
    // Now we have to calculate the input voltage 
    auto digitalValue = pFunction == nullptr ? ADC.StartConversion()
                                             : ADC.StartConversion(pFunction);
    return 0.00488758553 * digitalValue;
}

#define X(pin_)\
    template class AdcDeviceInterface<Pin::k##pin_, Pin::kNotConnected>;
    ATMEGA32_PINS
#undef X
