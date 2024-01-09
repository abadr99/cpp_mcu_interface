#include <stdint.h>

#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../mcal/inc/Adc.h"
#include "../../../utils/inc/Test.h"
 
using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;
using namespace avr::mcal::adc;

int main () {
    ADC.SelectChannel<ChannelMode::kSingleEnded_ADC0>();
    ADC.Init<>();
    print_str("**********************");
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    print_str("ADCSRA: ");
    print_num_binary(*((volatile uint8_t*) 0x26));
    new_line();
    print_str("ADCL: ");
    print_num_binary(*((volatile uint8_t*) 0x24));
    new_line();
    print_str("ADCH: ");
    print_num_binary(*((volatile uint8_t*) 0x25));
    new_line();
    print_str("SFIOR: ");
    print_num_binary(*((volatile uint8_t*) 0x50));
    new_line();

    ADC.Init<VoltageRefMode::kAvcc,
            DivisionFactorMode::kDivisionFactor_4x,  //IGNORE-STYLE-CHECK[L004]
              AutoTriggerMode::kTimer1_CaptureEvent,       //IGNORE-STYLE-CHECK[L004]
             ResultAdjustMode::kRight>();
    print_str("**********************");
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    print_str("ADCSRA: ");
    print_num_binary(*((volatile uint8_t*) 0x26));
    new_line();
    print_str("ADCL: ");
    print_num_binary(*((volatile uint8_t*) 0x24));
    new_line();
    print_str("ADCH: ");
    print_num_binary(*((volatile uint8_t*) 0x25));
    new_line();
    print_str("SFIOR: ");
    print_num_binary(*((volatile uint8_t*) 0x50));
    new_line();

    ADC.Init<VoltageRefMode::k2_56v,
            DivisionFactorMode::kDivisionFactor_8x,  //IGNORE-STYLE-CHECK[L004]
              AutoTriggerMode::kExternalInterrupt0,       //IGNORE-STYLE-CHECK[L004]
             ResultAdjustMode::kRight>();
    print_str("**********************");
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    print_str("ADCSRA: ");
    print_num_binary(*((volatile uint8_t*) 0x26));
    new_line();
    print_str("ADCL: ");
    print_num_binary(*((volatile uint8_t*) 0x24));
    new_line();
    print_str("ADCH: ");
    print_num_binary(*((volatile uint8_t*) 0x25));
    new_line();
    print_str("SFIOR: ");
    print_num_binary(*((volatile uint8_t*) 0x50));
    new_line();

    ADC.Init<VoltageRefMode::kAref,
            DivisionFactorMode::kDivisionFactor_16x,  //IGNORE-STYLE-CHECK[L004]
              AutoTriggerMode::kTimer0_CompareMatch,       //IGNORE-STYLE-CHECK[L004]
             ResultAdjustMode::kRight>();
    print_str("**********************");
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    print_str("ADCSRA: ");
    print_num_binary(*((volatile uint8_t*) 0x26));
    new_line();
    print_str("ADCL: ");
    print_num_binary(*((volatile uint8_t*) 0x24));
    new_line();
    print_str("ADCH: ");
    print_num_binary(*((volatile uint8_t*) 0x25));
    new_line();
    print_str("SFIOR: ");
    print_num_binary(*((volatile uint8_t*) 0x50));
    new_line();

    ADC.Init<VoltageRefMode::kAref,
            DivisionFactorMode::kDivisionFactor_32x,  //IGNORE-STYLE-CHECK[L004]
              AutoTriggerMode::kTimer0_OverFlow,       //IGNORE-STYLE-CHECK[L004]
             ResultAdjustMode::kRight>();
    print_str("**********************");
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    print_str("ADCSRA: ");
    print_num_binary(*((volatile uint8_t*) 0x26));
    new_line();
    print_str("ADCL: ");
    print_num_binary(*((volatile uint8_t*) 0x24));
    new_line();
    print_str("ADCH: ");
    print_num_binary(*((volatile uint8_t*) 0x25));
    new_line();
    print_str("SFIOR: ");
    print_num_binary(*((volatile uint8_t*) 0x50));
    new_line();

    ADC.Init<VoltageRefMode::kAref,
            DivisionFactorMode::kDivisionFactor_64x,  //IGNORE-STYLE-CHECK[L004]
              AutoTriggerMode::kTimer1_OverFlow,       //IGNORE-STYLE-CHECK[L004]
             ResultAdjustMode::kRight>();
    print_str("**********************");
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    print_str("ADCSRA: ");
    print_num_binary(*((volatile uint8_t*) 0x26));
    new_line();
    print_str("ADCL: ");
    print_num_binary(*((volatile uint8_t*) 0x24));
    new_line();
    print_str("ADCH: ");
    print_num_binary(*((volatile uint8_t*) 0x25));
    new_line();
    print_str("SFIOR: ");
    print_num_binary(*((volatile uint8_t*) 0x50));
    new_line();

    ADC.Init<VoltageRefMode::kAref,
            DivisionFactorMode::kDivisionFactor_128x,  //IGNORE-STYLE-CHECK[L004]
              AutoTriggerMode::kTimer1_CompareMatchB,       //IGNORE-STYLE-CHECK[L004]
             ResultAdjustMode::kRight>();
    print_str("**********************");
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    print_str("ADCSRA: ");
    print_num_binary(*((volatile uint8_t*) 0x26));
    new_line();
    print_str("ADCL: ");
    print_num_binary(*((volatile uint8_t*) 0x24));
    new_line();
    print_str("ADCH: ");
    print_num_binary(*((volatile uint8_t*) 0x25));
    new_line();
    print_str("SFIOR: ");
    print_num_binary(*((volatile uint8_t*) 0x50));
    new_line();

    ADC.Disable();
    print_str("**********************");
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    print_str("ADCSRA: ");
    print_num_binary(*((volatile uint8_t*) 0x26));
    new_line();
    print_str("ADCL: ");
    print_num_binary(*((volatile uint8_t*) 0x24));
    new_line();
    print_str("ADCH: ");
    print_num_binary(*((volatile uint8_t*) 0x25));
    new_line();
    print_str("SFIOR: ");
    print_num_binary(*((volatile uint8_t*) 0x50));
    new_line();

    ADC.Enable();
    ADC.SetAutoTriggerMode<kAnalogComparator>();
    print_str("**********************");
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    print_str("ADCSRA: ");
    print_num_binary(*((volatile uint8_t*) 0x26));
    new_line();
    print_str("ADCL: ");
    print_num_binary(*((volatile uint8_t*) 0x24));
    new_line();
    print_str("ADCH: ");
    print_num_binary(*((volatile uint8_t*) 0x25));
    new_line();
    print_str("SFIOR: ");
    print_num_binary(*((volatile uint8_t*) 0x50));
    new_line();

    print_str("*********CHANNELS*************");
    new_line();
    ADC.SelectChannel<ChannelMode::kSingleEnded_ADC1>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kSingleEnded_ADC2>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kSingleEnded_ADC3>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kSingleEnded_ADC4>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kSingleEnded_ADC5>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kSingleEnded_ADC6>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kSingleEnded_ADC7>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC0_ADC0_10x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC1_ADC0_10x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC0_ADC0_200x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC1_ADC0_200x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC2_ADC2_10x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC3_ADC0_10x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC2_ADC2_200x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC3_ADC0_200x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC0_ADC1_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC0_ADC2_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC1_ADC1_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC1_ADC2_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();   
    ADC.SelectChannel<ChannelMode::kDifferential_ADC2_ADC1_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kDifferential_ADC2_ADC2_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kDifferential_ADC3_ADC1_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kDifferential_ADC3_ADC2_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kDifferential_ADC4_ADC1_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kDifferential_ADC4_ADC2_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kDifferential_ADC5_ADC1_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kDifferential_ADC5_ADC2_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kDifferential_ADC6_ADC1_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kDifferential_ADC7_ADC1_1x>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kSingleEnded_1_22V>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();    
    ADC.SelectChannel<ChannelMode::kSingleEnded_gnd>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SelectChannel<ChannelMode::kSingleEnded_ADC0>();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();

    print_str("*********GET ADJUST MODE*************");
    new_line();
    ResultAdjustMode RES=ADC.GetAdjustMode();
    print_str("ResultAdjustMode: ");
    print_num(RES);
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
    ADC.SetAdjustMode<kLeft>();
    RES=ADC.GetAdjustMode();
    print_str("ResultAdjustMode: ");
    print_num(RES); 
    new_line();
    print_str("ADMUX: ");
    print_num_binary(*((volatile uint8_t*) 0x27));
    new_line();
}
