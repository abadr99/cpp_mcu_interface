/**
 * @file Adc.h
 * @brief  How to use this driver?
 *          // TODO(@abadr99): Make this class as singleton class
 *          - As we have only one ADC in atmega32 then you should deal with 
 *            'ADC' object and not creat any new objects from this class.
 *          - Here is the steps of configuring ADC and how to deal with it.
 *              1] According to specs if ADC is not enable no configurations 
 *                 would be configured. So THIS STEP SHOULD BE THE FIRST STEP.
 *                 ADC.Enable();
 *              2] Select Reference voltage mode 
 *              3] Select Channel 
 *              4] Select Adjust mode
 *              5] Start conversion (either with callback or without)
 * @version 0.1
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _ADC_H_H
#define _ADC_H_H

// Mode Value
#define ADC_CHANNEL_MODES\
    X(SingleEnded_ADC0,             0b00000)\
    X(SingleEnded_ADC1,             0b00001)\
    X(SingleEnded_ADC2,             0b00010)\
    X(SingleEnded_ADC3,             0b00011)\
    X(SingleEnded_ADC4,             0b00100)\
    X(SingleEnded_ADC5,             0b00101)\
    X(SingleEnded_ADC6,             0b00110)\
    X(SingleEnded_ADC7,             0b00111)\
    X(Differential_ADC0_ADC0_10x,   0b01000)\
    X(Differential_ADC1_ADC0_10x,   0b01001)\
    X(Differential_ADC0_ADC0_200x,  0b01010)\
    X(Differential_ADC1_ADC0_200x,  0b01011)\
    X(Differential_ADC2_ADC2_10x,   0b01100)\
    X(Differential_ADC3_ADC0_10x,   0b01101)\
    X(Differential_ADC2_ADC2_200x,  0b01110)\
    X(Differential_ADC3_ADC0_200x,  0b01111)\
    X(Differential_ADC0_ADC1_1x,    0b10000)\
    X(Differential_ADC1_ADC1_1x,    0b10001)\
    X(Differential_ADC2_ADC1_1x,    0b10010)\
    X(Differential_ADC3_ADC1_1x,    0b10011)\
    X(Differential_ADC4_ADC1_1x,    0b10100)\
    X(Differential_ADC5_ADC1_1x,    0b10101)\
    X(Differential_ADC6_ADC1_1x,    0b10110)\
    X(Differential_ADC7_ADC1_1x,    0b10111)\
    X(Differential_ADC0_ADC2_1x,    0b11000)\
    X(Differential_ADC1_ADC2_1x,    0b11001)\
    X(Differential_ADC2_ADC2_1x,    0b11010)\
    X(Differential_ADC3_ADC2_1x,    0b11011)\
    X(Differential_ADC4_ADC2_1x,    0b11100)\
    X(Differential_ADC5_ADC2_1x,    0b11101)\
    X(SingleEnded_1_22V,            0b11110)\
    X(SingleEnded_gnd,              0b11111)

#define ADC_DIVISION_FACTOR\
    X(DivisionFactor_2x,     0b000)\
    X(DivisionFactor_4x,     0b010)\
    X(DivisionFactor_8x,     0b011)\
    X(DivisionFactor_16x,    0b100)\
    X(DivisionFactor_32x,    0b101)\
    X(DivisionFactor_64x,    0b110)\
    X(DivisionFactor_128x,   0b111)

#define ADC_AUTO_TRIGGER_MODE\
    X(FreeRunningMode,          0b000)\
    X(AnalogComparator,         0b001)\
    X(ExternalInterrupt0,       0b010)\
    X(Timer0_CompareMatch,      0b011)\
    X(Timer0_OverFlow,          0b100)\
    X(Timer1_CompareMatchB,     0b101)\
    X(Timer1_OverFlow,          0b110)\
    X(Timer1_CaptureEvent,      0b111)

namespace avr {
namespace mcal {
namespace adc {

#define ADC_BASE_REG             (0x27)
class AdcRegisters {
public:
    enum Admux : uint8_t {
        kMUX0 = 0x00, kMUX1, kMUX2, kMUX3, kMUX4, kADLAR, kREFS0, kREFS1
    };
    enum Adcsra : uint8_t {
        kADPS0 = 0x00, kADPS1, kADPS2, kADIE, kADIF, kADATE, kADSC, kADEN
    };
    using reg_t = utils::Register<avr::types::AvrRegWidth>;
    AdcRegisters(const avr::types::AvrRegWidth baseAddr);
    reg_t& GetADMUX();
    reg_t& GetADCSRA();
    reg_t& GetADCL();
    reg_t& GetADCH();
    reg_t& GetSFIOR();
private:
    reg_t admux_;
    reg_t adcsra_;
    reg_t adch_;
    reg_t adcl_;
    reg_t sfior_;
};
class Adc {
public:
    enum VoltageRefMode: uint8_t {
        kAref = 0x00,   /*< AREF, Internal Vref turned off >*/
        kAvcc = 0x01,   /*< AVCC with external capacitor at AREF pin >*/
        k2_56v = 0x03   /*< Internal 2.56V Voltage Reference with external 
                            capacitor at AREF pin >*/
    };
    enum ChannelMode : uint8_t {
        #define X(mode_, val_)  k##mode_ = val_,
        ADC_CHANNEL_MODES
        #undef X
    };
    enum DivisionFactorMode : uint8_t {
        #define X(factor_, val_)    k##factor_ = val_,
        ADC_DIVISION_FACTOR
        #undef X
    };
    enum AutoTriggerMode : uint8_t {
        #define X(mode_, val_)       k##mode_ = val_,
        ADC_AUTO_TRIGGER_MODE
        #undef X
    };
    enum ResultAdjustMode : uint8_t { kRight, kLeft };
    using pFunction_t = void (*)();
    using digitalVal_t = uint16_t;
    using ADMUX = adc::AdcRegisters::Admux;
    using ADCSRA = adc::AdcRegisters::Adcsra;
    Adc();
    struct AdcConfigurations {
        VoltageRefMode     voltageMode;
        DivisionFactorMode divisionFactor;
        AutoTriggerMode    triggerMode;
        ResultAdjustMode   adjustMode;
    };
    void Init(const AdcConfigurations& conf = {kAref, kDivisionFactor_2x, kFreeRunningMode, kLeft}); //IGNORE-STYLE-CHECK[L004]
    void SelectChannel(ChannelMode cm);
    void Enable();
    void Disable();
    digitalVal_t StartConversion();
    digitalVal_t StartConversion(pFunction_t pFun);
    digitalVal_t GetConvertedValue();
    digitalVal_t GetDataRegister();
    void SetCallBack(pFunction_t pFun);
    pFunction_t GetCallBack();
    ResultAdjustMode GetAdjustMode();
    void SetConvertedValue(digitalVal_t val);
private:
    AdcRegisters registers_;
    volatile digitalVal_t convertedVal_;
    pFunction_t AdcCallBack_;
    void SetReferenceVoltageMode(VoltageRefMode mode);
    void SetPreScalarMode(DivisionFactorMode dfm);
    void SetAutoTriggerMode(AutoTriggerMode atm);
    void SetAdjustMode(ResultAdjustMode ram);
};

}}}

extern avr::mcal::adc::Adc ADC;

#undef ADC_CHANNEL_MODES
#undef ADC_DIVISION_FACTOR
#undef ADC_AUTO_TRIGGER_MODE
#endif // _ADC_H_H
