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
 adcl_(baseAddr - 2), adch_(baseAddr - 3),
 sfior_(SFIOR)
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
Register<AvrRegWidth>& AdcRegisters::GetSFIOR() {
    return sfior_;
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
    registers_.GetADMUX().SetRegisterWithMask<ADC_CHANNEL_MODE_MASK, 0, M>();
}
#define X(mode_, val_)\
 template void Adc::SelectChannel<ChannelMode::k##mode_>();
 ADC_CHANNEL_MODES
#undef X

void Adc::Enable() {
    registers_.GetADCSRA().SetBit<Adcsra::kADEN>();
}

void Adc::Disable() {
    registers_.GetADCSRA().ClearBit<Adcsra::kADEN>();
}

template<DivisionFactorMode M>
void Adc::SetPreScalarMode() {
    registers_.GetADCSRA().SetRegisterWithMask<ADC_PRESCALAR_MASK, 0, M>();
}
#define X(mode_, val_)\
 template void Adc::SetPreScalarMode<DivisionFactorMode::k##mode_>();
 ADC_DIVISION_FACTOR
#undef X

template <AutoTriggerMode M>
void Adc::SetAutoTriggerMode() {
    // Enable auto trigger
    registers_.GetADCSRA().SetBit<Adcsra::kADATE>();
    // Select auto trigger source
    registers_.GetSFIOR().SetRegisterWithMask<ADC_AUTO_TRIGGER_MASK, 5, M>();
}
#define X(mode_, val_)\
 template void Adc::SetAutoTriggerMode<AutoTriggerMode::k##mode_>();
 ADC_AUTO_TRIGGER_MODE
#undef X

template<ResultAdjustMode M>
void Adc::SetAdjustMode() {
    using RAM = ResultAdjustMode;
    switch (M) {
        case RAM::kLeft : registers_.GetADMUX().SetBit<AdmuxReg::kADLAR>();
        case RAM::kRight: registers_.GetADMUX().ClearBit<AdmuxReg::kADLAR>();
    }
}
template void Adc::SetAdjustMode<ResultAdjustMode::kLeft>();
template void Adc::SetAdjustMode<ResultAdjustMode::kRight>();

