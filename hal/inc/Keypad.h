#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#define KEYPAD_DEBOUNCING_TIME 20

namespace avr {
namespace hal {
namespace keypad  {

class Keypad : 
 public avr::hal::gpio::InputDeviceInterface,
 public avr::hal::gpio::OutputDeviceInterface{
   
    public:
    enum KeypadState { KPressed, KNotPressed };
    using Port = avr::mcal::gpio::Gpio::Port;
    using Pin = avr::mcal::gpio::Gpio::Pin;
    Keypad(Port colport, 
           Port rowport, 
           uint8_t colsize, 
           uint8_t rowsize, 
           Pin* colpins, 
           Pin* rowpins);
    void KeypadKeysInit(char** arr);
    uint8_t KeypadGetPressed();

private:
      Port ColPort_;
      Port RowPort_;
      uint8_t ColSize_;
      uint8_t RowSize_;
      Pin* ColPins_;
      Pin* RowPins_;
      char** KEYPAD_KEYS;

};
}}} // avr::hal::keypad
#endif // _KEYPAD_H_
