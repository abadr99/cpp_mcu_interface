/* 
 * make compile-test src=tests/integration/adc/main.cpp target=tests/integration/adc/adc
 * sh scripts/testing/run-simu-avr.sh tests/integration/adc/adc.testelf
 * sh scripts/testing/run-regressions.sh -d tests/integration/adc/
*/

#include <stdint.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../mcal/inc/Adc.h"
 #include "../../../tests/impl/AVRTest.h"

using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;
using namespace avr::mcal::adc;

#define ADMUX                           (*((volatile uint8_t*)0x27))
#define ADCSRA                           (*((volatile uint8_t*)0x26))
#define ADCL                             (*((volatile uint8_t*)0x24))
#define ADCH                             (*((volatile uint8_t*)0x25))
#define SFIOR_                            (*((volatile uint8_t*)0x50))

int main () {
   {
    avr::test::AVRTest TESTER("Channel modes test");

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC0);
    ADC.Init();
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC1);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x21));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC2);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x22));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC3);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x23));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC4);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x24));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC5);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x25));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC6);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x26));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC7);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x27));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC0_ADC0_10x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x28));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC1_ADC0_10x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x29));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC1_ADC0_200x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x2B));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC0_ADC0_200x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x2A));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));


    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC3_ADC2_10x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x2D));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC3_ADC2_200x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x2F));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC0_ADC1_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x30));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC1_ADC1_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x31));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC2_ADC1_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x32));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));


    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC3_ADC1_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x33));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC4_ADC1_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x34));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC5_ADC1_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x35));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC6_ADC1_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x36));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC7_ADC1_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x37));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC0_ADC2_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x38));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC1_ADC2_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x39));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC2_ADC2_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x3A));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));
    

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC2_ADC2_10x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x2C));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC2_ADC2_200x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x2E));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC3_ADC2_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x3B));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC4_ADC2_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x3C));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kDifferential_ADC5_ADC2_1x);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x3D));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_1_22V);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x3E));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_gnd);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x3F));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));


   }

  {
    avr::test::AVRTest TESTER("Ref modes test & adjust mode");
    Adc::AdcConfigurations fig;
    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC0);

    fig.voltageMode=Adc::VoltageRefMode::k2_56v;

    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0xE0));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    fig.voltageMode=Adc::VoltageRefMode::kAvcc;
    fig.adjustMode=Adc::ResultAdjustMode::kRight;

    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x40));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));
  }  

  {
    avr::test::AVRTest TESTER("prescaler modes test");
    ADC.Init();
    Adc::AdcConfigurations fig;
    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC0);

    fig.divisionFactor=Adc::DivisionFactorMode::kDivisionFactor_4x;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA2));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    fig.divisionFactor=Adc::DivisionFactorMode::kDivisionFactor_8x;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA3));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    fig.divisionFactor=Adc::DivisionFactorMode::kDivisionFactor_16x;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA4));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    fig.divisionFactor=Adc::DivisionFactorMode::kDivisionFactor_32x;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA5));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    fig.divisionFactor=Adc::DivisionFactorMode::kDivisionFactor_64x;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA6));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    fig.divisionFactor=Adc::DivisionFactorMode::kDivisionFactor_128x;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA7));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));


  }
  {

    avr::test::AVRTest TESTER("auto trigger source test");
    ADC.Init();
    Adc::AdcConfigurations fig;
    ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC0);

    fig.triggerMode=Adc::AutoTriggerMode::kAnalogComparator;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x20));

    fig.triggerMode=Adc::AutoTriggerMode::kExternalInterrupt0;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x40));

    fig.triggerMode=Adc::AutoTriggerMode::kTimer0_CompareMatch;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x60));

    fig.triggerMode=Adc::AutoTriggerMode::kTimer0_OverFlow;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x80));

    fig.triggerMode=Adc::AutoTriggerMode::kTimer1_CompareMatchB;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0xA0));


    fig.triggerMode=Adc::AutoTriggerMode::kTimer1_OverFlow;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0xC0));

    fig.triggerMode=Adc::AutoTriggerMode::kTimer1_CaptureEvent;
    
    ADC.Init(fig);
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0xE0));
  }
  {

    avr::test::AVRTest TESTER("enable/disable test");
    ADC.Init();
    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));

    ADC.Disable();

    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));


    ADC.Enable();

    TESTER.Expect_Eq(ADMUX, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(ADCSRA, static_cast<uint8_t>(0xA0));
    TESTER.Expect_Eq(ADCL, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(ADCH, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(SFIOR_, static_cast<uint8_t>(0x00));


  }
}
