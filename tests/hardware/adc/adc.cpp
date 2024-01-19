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
   // 1] Enable ADC
   ADC.Enable();
   // 2] Set reference voltage as 'AREF' pin
   ADC.SetReferenceVoltageMode<VoltageRefMode::kAref>();
   // 3] Select ADC channel to be channel1 i.e. A0
   ADC.SelectChannel<ChannelMode::kSingleEnded_ADC0>();
   // 4] Select Adjust mode to be left
   ADC.SetAdjustMode<ResultAdjustMode::kLeft>();

   // ------- Set GPIOB configurations
   // 1] Create GPIOB object
   Gpio<Port::kPortB> GPIOB;
   // 2] Set all pins as output pins
   GPIOB.SetDirection(0xFF);
   GPIOB.Write(0xFF);
   _delay_ms(500);
   GPIOB.Write(0x00);

   while (1) {
      GPIOB.template Write<Pin::kPin0, DigitalLevel::kHigh>();
      _delay_ms(300);
      auto C = ADC.StartConversion();
      GPIOB.Write((AvrRegWidth)C);
      GPIOB.template Write<Pin::kPin0, DigitalLevel::kLow>();
      _delay_ms(300);
   }
}
