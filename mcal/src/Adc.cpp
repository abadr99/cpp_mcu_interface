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
AdcRegisters::AdcRegisters(const AvrRegWidth baseAddr): admux_(baseAddr),
                                                        adcsra_(baseAddr - 1),
                                                        adch_(baseAddr - 2),
                                                        adcl_(baseAddr - 3),
                                                        sfior_(SFIOR)
 { /* EMPTY */ } 

typename AdcRegisters::reg_t& AdcRegisters::GetADMUX()  { return admux_;  }
typename AdcRegisters::reg_t& AdcRegisters::GetADCSRA() { return adcsra_; }
typename AdcRegisters::reg_t& AdcRegisters::GetADCL()   { return adcl_;   }
typename AdcRegisters::reg_t& AdcRegisters::GetADCH()   { return adch_;   }
typename AdcRegisters::reg_t& AdcRegisters::GetSFIOR()  { return sfior_;  }

// =============================================================================
// ------------------------------ Adc impl -------------------------------------
// =============================================================================

Adc::Adc() : registers_(ADC_BASE_REG), convertedVal_(0), AdcCallBack_(nullptr)
{ /* EMPTY */ }

void Adc::Init(const AdcConfigurations& conf) {
    Enable();
    SetReferenceVoltageMode(conf.voltageMode);
    SetPreScalarMode(conf.divisionFactor);
    SetAutoTriggerMode(conf.triggerMode);
    SetAdjustMode(conf.adjustMode);
}

void Adc::SetReferenceVoltageMode(VoltageRefMode mode) {
    registers_.GetADMUX()
              .template WriteBits<ADMUX::kREFS0, ADMUX::kREFS1>(mode);
}

void Adc::SelectChannel(ChannelMode cm) {
    registers_.GetADMUX().WriteBits<ADMUX::kMUX0, ADMUX::kMUX4>(cm);
}

void Adc::Enable() {
    registers_.GetADCSRA().SetBit<ADCSRA::kADEN>();
}

void Adc::Disable() {
    registers_.GetADCSRA().ClearBit<ADCSRA::kADEN>();
}

void Adc::SetPreScalarMode(DivisionFactorMode dfm) {
    registers_.GetADCSRA().WriteBits<ADCSRA::kADPS0, ADCSRA::kADPS2>(dfm);
}

void Adc::SetAutoTriggerMode(AutoTriggerMode atm) {
    // Enable auto trigger
    registers_.GetADCSRA().SetBit<ADCSRA::kADATE>();
    // Select auto trigger source
    registers_.GetSFIOR().WriteBits<5, 7>(atm);
}

void Adc::SetAdjustMode(ResultAdjustMode ram) {
    registers_.GetADMUX().WriteBits<ADMUX::kADLAR>(ram);
}

typename Adc::ResultAdjustMode Adc::GetAdjustMode() {
    using RAM = ResultAdjustMode;
    return static_cast<RAM>(registers_.GetADMUX().ReadBit<ADMUX::kADLAR>());
}

Adc::digitalVal_t Adc::GetConvertedValue() {
    return convertedVal_;
}

Adc::digitalVal_t Adc::GetDataRegister() {
    Adc::digitalVal_t convertedVal = 0;
    // Read the converted value depending on :
    //   a) Adjust mode {left, right}
    if (GetAdjustMode() == ResultAdjustMode::kLeft) {
        convertedVal = registers_.GetADCL().ReadBits<6, 7>()
                     | registers_.GetADCH().ReadRegister();
        return convertedVal;
    }
    convertedVal = registers_.GetADCL().ReadRegister()
                 | registers_.GetADCH().ReadRegister();
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
    registers_.GetADCSRA().SetBit<ADCSRA::kADSC>();
    // 2] Wait until conversion be completed
    // TODO(@abadr99): Handle timeout to avoid endless loop
    while (registers_.GetADCSRA().ReadBit<ADCSRA::kADSC>() == 1) { /* EMPTY */}
    // 3] Get converted val
    convertedVal = GetDataRegister();
    SetConvertedValue(convertedVal);
    return convertedVal;
}

Adc::digitalVal_t Adc::StartConversion(Adc::pFunction_t pFun) {
    // 1] Enable interrupt 
    SEI();
    registers_.GetADCSRA().SetBit<ADCSRA::kADIE>();
    // 2] Set 'ADC' callback
    SetCallBack(pFun);
    // 3] Start Conversion
    registers_.GetADCSRA().SetBit<ADCSRA::kADSC>();
    // 4] Get Converted value
    return GetConvertedValue();
}

ISR(ADC_CONVERSION)
{
    // Get converted value
    ADC.SetConvertedValue(ADC.GetDataRegister());
    // Execute callback
    auto cb = ADC.GetCallBack();
    cb();
}
