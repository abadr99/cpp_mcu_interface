#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#define KEYPAD_DEBOUNCING_TIME 20
#define COL_SIZE               4
#define ROW_SIZE               4

namespace avr {
namespace hal {
namespace keypad  {

class Keypad : public avr::hal::gpio::InputDeviceInterface{
public:

    enum KeypadState { KPressed, KNotPressed };
    using Port = avr::mcal::gpio::Gpio::Port;
    using Pin = avr::mcal::gpio::Gpio::Pin;
    //using DS = Gpio::DirectionState;
    Keypad(Port port,
           Pin c1, Pin c2, Pin c3, Pin c4,
           Pin r1, Pin r2, Pin r3, Pin r4);
    uint8_t KeypadGetPressed();

private:
      Port KeypadPort_;
      Pin C1Pin_;
      Pin C2Pin_;
      Pin C3Pin_;
      Pin C4Pin_;
      Pin R1Pin_;
      Pin R2Pin_;
      Pin R3Pin_;
      Pin R4Pin_;
      Pin ColPinsArr_[COL_SIZE] = {C1Pin_, C2Pin_, C3Pin_, C4Pin_};
      Pin RowPinsArr_[ROW_SIZE] = {R1Pin_, R2Pin_, R3Pin_, R4Pin_};
      uint8_t KEYPAD_KEYS [ROW_SIZE][COL_SIZE]=  {{'1', '2', '3', '+'},
         {'4', '5', '6', '-'},
         {'7', '8', '9', '*'},
         {'0', '=', '%', '/'}};

};
}}} // avr::hal::keypad
#endif // _KEYPAD_H_
