#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Adc.h"
#include "AdcDeviceInterface.h"

using namespace avr::mcal::adc;
using namespace avr::hal::adc;
using avr::types::Pin;

AdcDeviceInterface::AdcDeviceInterface(const pin_t pin1, const pin_t pin2 )
: pins{pin1, pin2} { /* EMPTY */ }

typename AdcDeviceInterface::
volt_t AdcDeviceInterface::GetInputVoltage(pFun_t pFunction) {
    using CM = avr::mcal::adc::Adc::ChannelMode;
    // Select Channel according to device pins
    if (pins[1] == pin_t::kPinNotConnected) {
      ADC.SelectChannel(static_cast<CM>(pins[0]));
    }
    else {
      // TODO(@abadr99): Support differential modes
    }
    // Now we have to calculate the input voltage 
    auto digitalValue = pFunction == nullptr ? ADC.StartConversion()
                                             : ADC.StartConversion(pFunction);
    return 0.00488758553 * digitalValue;
}
