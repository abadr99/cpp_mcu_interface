#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Adc.h"

// =============================================================================
// ------------------------------ NAMESPACES -----------------------------------
// =============================================================================

using namespace avr::mcal::adc;
using avr::types::AvrRegWidth;
using utils::Register;

// =============================================================================
// ------------------------------ GLOBAL VARIABLES -----------------------------
// =============================================================================

Adc ADC;

// =============================================================================
// -------------------------- AdcRegisters impl --------------------------------
// =============================================================================

AdcRegisters::AdcRegisters(const AvrRegWidth baseAddr) 
:admux_(baseAddr), adcsra_(baseAddr - 1), 
 adch_(baseAddr - 2), adcl_(baseAddr - 3),
 sfior_(SFIOR)
 { /* EMPTY */ } 

Register<AvrRegWidth>& AdcRegisters::GetADMUX()  { return admux_;  }
Register<AvrRegWidth>& AdcRegisters::GetADCSRA() { return adcsra_; }
Register<AvrRegWidth>& AdcRegisters::GetADCL()   { return adcl_;   }
Register<AvrRegWidth>& AdcRegisters::GetADCH()   { return adch_;   }
Register<AvrRegWidth>& AdcRegisters::GetSFIOR()  { return sfior_;  }

// =============================================================================
// ------------------------------ Adc impl -------------------------------------
// =============================================================================

Adc::Adc() : registers_(ADC_BASE_REG), convertedVal_(0), AdcCallBack_(nullptr)
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
    registers_.GetADMUX().WriteWithMask<ADC_CHANNEL_MODE_MASK, 0, M>();
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
    registers_.GetADCSRA().WriteWithMask<ADC_PRESCALAR_MASK, 0, M>();
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
    registers_.GetSFIOR().WriteWithMask<ADC_AUTO_TRIGGER_MASK, 5, M>();
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

ResultAdjustMode Adc::GetAdjustMode() {
    using RAM = ResultAdjustMode;
    return registers_.GetADMUX()
                     .ReadBit<AdmuxReg::kADLAR>() == 1 ? RAM::kLeft
                                                       : RAM::kRight;
}

Adc::digitalVal_t Adc::GetConvertedValue() {
    return convertedVal_;
}

Adc::digitalVal_t Adc::GetDataRegister() {
    Adc::digitalVal_t convertedVal = 0;
    // Read the converted value depending on :
    //   a) Adjust mode {left, right}
    if (GetAdjustMode() == ResultAdjustMode::kLeft) {
        convertedVal = registers_.GetADCL().ReadBits<6, 7>() | 
                       registers_.GetADCH().Read();
    }
    else {
        convertedVal = registers_.GetADCL().Read() | 
                       registers_.GetADCH().Read();
    }
    return convertedVal;
}

void Adc::SetConvertedValue(Adc::digitalVal_t val) {
    convertedVal_ = val;
}

void Adc::SetCallBack(Adc::pFunction_t pFun) {
    AdcCallBack_ = pFun;
}

Adc::pFunction_t Adc::GetCallBack() {
    return AdcCallBack_;
}

Adc::digitalVal_t Adc::StartConversion() {
    Adc::digitalVal_t convertedVal = 0;
    // 1] Start conversion
    registers_.GetADCSRA().SetBit<Adcsra::kADSC>();
    // 2] Wait until conversion be completed
    // TODO(@abadr99): Handle timeout to avoid endless loop
    while (registers_.GetADCSRA().ReadBit<Adcsra::kADSC>() == 1) { /* EMPTY */}
    // 3] Get converted val
    convertedVal = GetDataRegister();
    SetConvertedValue(convertedVal);
    return convertedVal;
}

Adc::digitalVal_t Adc::StartConversion(Adc::pFunction_t pFun) {
    // 1] Enable interrupt 
    // TODO(@abadr): (NOTE: Global interrupt should be enabled)
    registers_.GetADCSRA().SetBit<Adcsra::kADIE>();
    // 2] Set 'ADC' callback
    SetCallBack(pFun);
    // 3] Start Conversion
    registers_.GetADCSRA().SetBit<Adcsra::kADSC>();
    // 4] Get Converted value
    return GetConvertedValue();
}

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
    // Get converted value
    ADC.SetConvertedValue(ADC.GetDataRegister());
    // Execute callback
    auto cb = ADC.GetCallBack();
    cb();
}
