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
Keypad::Keypad(Port port,
               Pin c1, Pin c2, Pin c3, Pin c4, 
               Pin r1, Pin r2, Pin r3, Pin r4):
               KeypadPort_(port),
               C1Pin_(c1), C2Pin_(c2), C3Pin_(c3), C4Pin_(c4), 
               R1Pin_(r1), R2Pin_(r2), R3Pin_(r3), R4Pin_(r4)
{ //set column pins to be output & row pins to be input
Gpio::SetPinDirection(KeypadPort_, C1Pin_, Gpio::DirectionState::kOutput);
Gpio::SetPinDirection(KeypadPort_, C2Pin_, Gpio::DirectionState::kOutput);
Gpio::SetPinDirection(KeypadPort_, C3Pin_, Gpio::DirectionState::kOutput);
Gpio::SetPinDirection(KeypadPort_, C4Pin_, Gpio::DirectionState::kOutput);

Gpio::SetPinDirection(KeypadPort_, R1Pin_, Gpio::DirectionState::kInputPullUp);
Gpio::SetPinDirection(KeypadPort_, R2Pin_, Gpio::DirectionState::kInputPullUp);
Gpio::SetPinDirection(KeypadPort_, R3Pin_, Gpio::DirectionState::kInputPullUp);
Gpio::SetPinDirection(KeypadPort_, R4Pin_, Gpio::DirectionState::kInputPullUp);

//set column pins to be high (deactivate them)
Gpio::WritePin(KeypadPort_, C1Pin_, DigitalLevel::kHigh);
Gpio::WritePin(KeypadPort_, C2Pin_, DigitalLevel::kHigh);
Gpio::WritePin(KeypadPort_, C3Pin_, DigitalLevel::kHigh);
Gpio::WritePin(KeypadPort_, C4Pin_, DigitalLevel::kHigh);

}
uint8_t Keypad::KeypadGetPressed()
{

 uint8_t RowCounter,
        ColCounter,
        KeyValue=Keypad::KNotPressed;
 DigitalLevel PinVal;

 for (ColCounter=0; ColCounter < COL_SIZE; ColCounter++ )
 {  /*Activate Column by Setting 0 at output*/
    Gpio::WritePin(Keypad::Keypad::KeypadPort_,
                   Keypad::Keypad::ColPinsArr_[ColCounter], 
                   Gpio::DigitalLevel::kHigh);
    for (RowCounter=0; RowCounter < ROW_SIZE; RowCounter++)
    {  /*get row value*/
       PinVal= Gpio::ReadPin(KeypadPort_, RowPinsArr_[RowCounter]);
       if (PinVal==DigitalLevel::kLow) //low-> switch is pressed
       {
        /*get the value of the pressed key*/
       KeyValue=KEYPAD_KEYS[RowCounter][ColCounter];
       /*wait until its not pressed*/
       while (Gpio::ReadPin(KeypadPort_,
              RowPinsArr_[RowCounter])==DigitalLevel::kLow) 
             {/*empty*/}
       /*wait for debouncing time*/
       _delay_ms(KEYPAD_DEBOUNCING_TIME);
       }
       
    }
       /*deactivate current column*/
        Gpio::WritePin(Keypad::Keypad::KeypadPort_, 
              Keypad::Keypad::ColPinsArr_[ColCounter],
              Gpio::DigitalLevel::kLow);
}
        return KeyValue;
}

