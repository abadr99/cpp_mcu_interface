#include <stdint.h>
#include <Helpers.h>
#include "Atmega32.h"
#include "Register.h"
#include "Adc.h"
#include "AdcDeviceInterface.h"
#include "Lm35.h"

using namespace avr::hal::adc;
using namespace avr::hal::temperature_sensor;

template <avr::types::Pin TPin1>
Lm35<TPin1>::Lm35() 
{ /*    EMPTY   */}

template <avr::types::Pin TPin1>
typename Lm35<TPin1>::temperature_t 
Lm35<TPin1>::GetTemperature() {
    // According to LM35 specs: https://www.ti.com/lit/ds/symlink/lm35.pdf
    // Vo = 10T where: Vo: Output Voltage in mVolt   T: Temperature in C
    // then T = V0(mv) / 10
    typename AdcDeviceInterface<TPin1>::volt_t Vo = this->GetInputVoltage();
    temperature_t temperature = utils::ConvertToMilli(Vo) / 10.00;
    return temperature;
}
