#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Adc.h"

using namespace avr::mcal::adc;
using avr::types::AvrRegWidth;
using utils::Register;
// =============================================================================
// -------------------------- AdcRegisters impl --------------------------------
// =============================================================================
AdcRegisters::AdcRegisters(const AvrRegWidth baseAddr) 
:admux_(baseAddr), adcsra_(baseAddr - 1), 
 adcl_(baseAddr - 2), adch_(baseAddr - 3)
 { /* EMPTY */ } 

Register<AvrRegWidth>& AdcRegisters::GetADMUX() {
    return admux_;
}
Register<AvrRegWidth>& AdcRegisters::GetADCSRA() {
    return adcsra_;
}
Register<AvrRegWidth>& AdcRegisters::GetADCL() {
    return adcl_;
}
Register<AvrRegWidth>& AdcRegisters::GetADCH() {
    return adch_;
}
// =============================================================================
// ------------------------------ Adc impl -------------------------------------
// =============================================================================
Adc::Adc() : registers_(ADC_BASE_REG)
{ /* EMPTY */ }

template<VoltageRefMode M>
void Adc::SetReferenceVoltageMode() {
    using VRM = VoltageRefMode;
    switch (M) {
        case VRM::kAref : 
            registers_.GetADMUX().ClearBit<AdmuxReg::kREFS1>()
                                 .ClearBit<AdmuxReg::kREFS0>();
            break;
        case VRM::kAvcc : 
            registers_.GetADMUX().ClearBit<AdmuxReg::kREFS1>()
                                 .SetBit<AdmuxReg::kREFS0>();
            break;
        case VRM::k2_56v:
            registers_.GetADMUX().SetBit<AdmuxReg::kREFS1>()
                                 .SetBit<AdmuxReg::kREFS0>();
            break;
    }
}
template void Adc::SetReferenceVoltageMode<VoltageRefMode::kAref>();
template void Adc::SetReferenceVoltageMode<VoltageRefMode::kAvcc>();
template void Adc::SetReferenceVoltageMode<VoltageRefMode::k2_56v>();

template <ChannelMode M>
void Adc::SelectChannel() {
    uint8_t admuxVal = registers_.GetADMUX().GetRegisterValue();
    admuxVal = (admuxVal & ADC_CHANNEL_MODE_MASK) | M;
    registers_.GetADMUX().SetRegisterValue(admuxVal);
}
#define X(mode_, val_)\
 template void Adc::SelectChannel<ChannelMode::k##mode_>();
 ADC_CHANNEL_MODES
 #undef X
// 
