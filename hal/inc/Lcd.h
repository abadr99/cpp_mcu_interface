#ifndef _LCD_H_
#define _LCD_H_


namespace avr {
namespace hal {
namespace lcd {

#define LCD_NUMBER_OF_ROWS      (2)
#define LCD_NUMBER_OF_COLS      (16)

enum DataTransferModes {
    kFourBits,
    kEightBits,
};

struct LcdConfig {
    DataTransferModes transferMode;
    using Port = avr::types::Port;
    using Pin  = avr::types::Pin;
    Port ctrlPort; Pin rs; Pin rw; Pin en;
    Port dataPort; Pin d0; Pin d1; Pin d2; Pin d3;
    bool IsEightBit();
};

enum NumberMode {
    kDec = 10,
    kBin = 2,
    kOct = 8,
    kHex = 16,
};
class Lcd : public avr::hal::gpio::OutputDeviceInterface {
public:
    using DevicePin = utils::types::DevicePin;
    using Port = avr::types::Port;
    using Pin = avr::types::Pin;
    Lcd(LcdConfig& config);
    void ClearScreen();
    void Display(size_t data, NumberMode mode = kDec);
    void Display(char data);
    void Display(const char* data);
    void Display(float data, uint8_t prec = 3);
    void StoreCustomChar(char pChar_Arr[], uint8_t location);
    void DisplayCustomChar(uint8_t location, uint8_t row, uint8_t col);
    void SetCursor(uint8_t row, uint8_t col);
    void EnableCursor();
    void DisableCursor();
    void ShiftRight();
    void ShiftLeft();
    void DisplayOn ();
    void DisplayOff();
    void BlinkOn();
    void BlinkOff();
private:
    LcdConfig config_;
    enum SendMode { kCommand, kData };
    using SM = SendMode;
    enum Command {
        kCGRAM                       = 0x40,
        kDDRAM                       = 0x80,
        kBlinkOn                     = 0x0F,
        kBlinkOff                    = 0x0E,
        kShiftLeft                   = 0x18,
        kShiftRight                  = 0x1C,
        kReturnHome                  = 0x02,
        kClearScreen                 = 0X01,
        kFunctionSet8Bit             = 0x38,
        kFunctionSet4Bit             = 0x28,
        kIncrementCursor             = 0x04,
        kDecrementCursor             = 0x00,
        kDisplayOn_CursorOn          = 0x0E,
        kDisplayOn_CursorOff         = 0x0C,
        kDisplayOff_CursorOff        = 0x09,
        kEntryModeDecrement_ShiftOn  = 0x05,
        kEntryModeIncrement_ShiftOn  = 0x07,
        kEntryModeDecrement_ShiftOff = 0x04,
        kEntryModeIncrement_ShiftOff = 0x06,
    };
    void Pulse();
    template <SendMode M>
    void Send(uint8_t d);
};

}}} // namespace avr::hal::lcd
#endif // _LCD_H_

