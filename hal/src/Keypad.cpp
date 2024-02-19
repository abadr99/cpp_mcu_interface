#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Gpio.h"
#include "GpioDeviceInterface.h"
#include "Keypad.h"
#include <util/delay.h>

using namespace avr::types;
using namespace avr::mcal::gpio;
using namespace avr::hal;
using namespace avr::hal::keypad;
using OP = avr::hal::gpio::OutputDeviceInterface;
using IP = avr::hal::gpio::InputDeviceInterface;
Keypad::Keypad(Port colport, 
               Port rowport, 
               uint8_t colsize, 
               uint8_t rowsize, 
               Pin* colpins, 
               Pin* rowpins):
               ColPort_(colport), 
               RowPort_(rowport), 
               ColSize_(colsize), 
               RowSize_(rowsize), 
               ColPins_(colpins), 
               RowPins_(rowpins) 

{ //set column pins to be output & row pins to be input
 for (uint8_t i = 0 ; i < ColSize_; ++i) {
        this->OP::Init({ColPort_, ColPins_[i]});
    }

 for (uint8_t i = 0 ; i < RowSize_ ; ++i) {
        this->IP::Init({RowPort_, RowPins_[i]}, Input_mode::kpullup);
    }

 //set column pins to be high (deactivate them)
 for (uint8_t i = 0 ; i < ColSize_; ++i) {
        this->OP::SetHighVoltage({ColPort_, ColPins_[i]});
    }

}
void Keypad::KeypadKeysInit(char** arr)
{
 for (uint8_t i = 0 ; i < ColPort_; ++i) {
   for (uint8_t y=0 ; y < RowSize_; ++y)
   {
     KEYPAD_KEYS[i][y]=arr[i][y];
   }  
    }
}
uint8_t Keypad::KeypadGetPressed()
{

 uint8_t RowCounter,
        ColCounter,
        KeyValue=Keypad::KNotPressed;
 DigitalLevel PinVal;

 for (ColCounter=0; ColCounter < ColSize_; ColCounter++ )
 {  /*Activate Column by Setting 0 at output*/
    OP::SetLowVoltage({ColPort_, ColPins_[ColCounter]});

    for (RowCounter=0; RowCounter < RowSize_ ; RowCounter++)
    {  /*get row value*/
       PinVal= GetPinState({RowPort_, RowPins_[RowCounter]});
       if (PinVal==DigitalLevel::kLow) //low-> switch is pressed
       {
        /*get the value of the pressed key*/
       KeyValue=KEYPAD_KEYS[RowCounter][ColCounter];
       /*wait until its not pressed*/
       while (GetPinState({RowPort_, RowPins_[RowCounter]})
            == DigitalLevel::kLow) 
             {/*empty*/}
       /*wait for debouncing time*/
       _delay_ms(KEYPAD_DEBOUNCING_TIME);
       }
       
    }
   //De activate the column
   OP::SetHighVoltage({ColPort_, ColPins_[ColCounter]});
}
        return KeyValue;
}
