/**
 * @file adc.cpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief   Out converted digital value on PORTB as be read on A0. This is done
 *          by connecting potentiometer to A0 and out the converted value to 
 *          PORTB. You can connect any output device (e.g. LEDs) to PORTB to 
 *          visualize converted value. 
 * @version 0.1
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdint.h>
#include <util/delay.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../mcal/inc/Adc.h"

using namespace avr::mcal::gpio;
using namespace avr::mcal::adc;
using namespace avr::types;

int main() {
   // ------- Set ADC configurations
   //  Enable ADC
   ADC.Init();
   ADC.Enable();
   
   //  Select ADC channel to be channel1 i.e. A0
   ADC.SelectChannel(Adc::ChannelMode::kSingleEnded_ADC0);
   //  Select Adjust mode to be left

   // ------- Set GPIOB configurations
   //  Set all pins as output pins
   Gpio::SetPortDirection(kPortB, 0xFF);
   Gpio::WritePort(kPortB, 0xFF);
   _delay_ms(500);
   Gpio::WritePort(kPortB, 0x00);

   while (1) {
      Gpio::WritePin(kPortB, kPin0, Gpio::DigitalLevel::kHigh);
      _delay_ms(300);
      auto C = ADC.StartConversion();
      Gpio::WritePort(kPortB, (AvrRegWidth)C);
      Gpio::WritePin(kPortB, kPin0, Gpio::DigitalLevel::kLow);
      _delay_ms(300);
   }
}
