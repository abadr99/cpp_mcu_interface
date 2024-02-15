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
Keypad::Keypad(Port port,
               Pin c1, Pin c2, Pin c3, Pin c4, 
               Pin r1, Pin r2, Pin r3, Pin r4):
               KeypadPort_(port),
               pins_{c1, c2, c3, c4, r1, r2, r3, r4}
{ //set column pins to be output & row pins to be input
 for (uint8_t i = 0 ; i < COL_SIZE; ++i) {
        this->OP::Init({KeypadPort_, pins_[i]});
    }

 for (uint8_t i = COL_SIZE ; i < COL_SIZE + ROW_SIZE; ++i) {
        this->IP::Init({KeypadPort_, pins_[i]}, Input_mode::kpullup);
    }

 //set column pins to be high (deactivate them)
 for (uint8_t i = 0 ; i < COL_SIZE; ++i) {
        this->OP::SetHighVoltage({KeypadPort_, pins_[i]});
    }

}
void Keypad::KeypadKeysInit(char arr[COL_SIZE][ROW_SIZE])
{
 for (uint8_t i = 0 ; i < COL_SIZE; ++i) {
   for (uint8_t y=0 ; y < ROW_SIZE; ++y)
   {
     KEYPAD_KEYS[i][y]=arr[i][y];
   }  
    }
}
uint8_t Keypad::KeypadGetPressed()
{

 uint8_t RowCounter,
        ColCounter,
        Counter=COL_SIZE,
        KeyValue=Keypad::KNotPressed;
 DigitalLevel PinVal;

 for (ColCounter=0; ColCounter < COL_SIZE; ColCounter++ )
 {  /*Activate Column by Setting 0 at output*/
    OP::SetLowVoltage({KeypadPort_, pins_[ColCounter]});

    for (RowCounter=0; RowCounter < ROW_SIZE ; RowCounter++, Counter++)
    {  /*get row value*/
       PinVal= GetPinState({KeypadPort_, pins_[Counter]});
       if (PinVal==DigitalLevel::kLow) //low-> switch is pressed
       {
        /*get the value of the pressed key*/
       KeyValue=KEYPAD_KEYS[Counter][ColCounter];
       /*wait until its not pressed*/
       while (GetPinState({KeypadPort_, pins_[Counter]})==DigitalLevel::kLow) 
             {/*empty*/}
       /*wait for debouncing time*/
       _delay_ms(KEYPAD_DEBOUNCING_TIME);
       }
       
    }
   OP::SetHighVoltage({KeypadPort_, pins_[ColCounter]});
}
        return KeyValue;
}
