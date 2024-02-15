#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#define KEYPAD_DEBOUNCING_TIME 20
#define COL_SIZE               4
#define ROW_SIZE               4

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
    Keypad(Port port,
           Pin c1, Pin c2, Pin c3, Pin c4,
           Pin r1, Pin r2, Pin r3, Pin r4);
    void KeypadKeysInit(char arr[COL_SIZE][ROW_SIZE]);
    uint8_t KeypadGetPressed();

private:
      Port KeypadPort_;
      Pin pins_[8];
      char KEYPAD_KEYS [ROW_SIZE][COL_SIZE];

};
}}} // avr::hal::keypad
#endif // _KEYPAD_H_
