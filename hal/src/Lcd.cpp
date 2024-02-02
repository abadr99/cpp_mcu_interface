#include <stdint.h>
#include <stdlib.h> // for itoa
#include <util/delay.h>
#include "Atmega32.h"
#include "Register.h"
#include "Helpers.h"
#include "Math.h"
#include "Gpio.h"
#include "GpioDeviceInterface.h"
#include "Lcd.h"

// =============================================================================
// ----------------------------- namespaces ------------------------------------
// =============================================================================
using namespace avr::hal::lcd;

// =============================================================================
// ----------------------------- LcdConfig -------------------------------------
// =============================================================================
bool LcdConfig::IsEightBit() {
    using DTM = DataTransferModes;
    return transferMode == DTM::kEightBits;
}
// =============================================================================
// ------------------------ PRIVATE METHODS ------------------------------------
// =============================================================================

void Lcd::Pulse() {
    SetHighVoltage(config_.ctrlPort, config_.en);
    _delay_ms(1);
    SetLowVoltage(config_.ctrlPort, config_.en);
    _delay_ms(1);
}

template <Lcd::SendMode M>
void Lcd::Send(uint8_t d) {
    auto Write4Bits = [&](uint8_t data) -> void {
        SetVoltage(config_.ctrlPort, config_.d0, static_cast<DL>(READ_BIT(data, 0)));   //IGNORE-STYLE-CHECK[L004]
        SetVoltage(config_.ctrlPort, config_.d1, static_cast<DL>(READ_BIT(data, 1)));   //IGNORE-STYLE-CHECK[L004]
        SetVoltage(config_.ctrlPort, config_.d2, static_cast<DL>(READ_BIT(data, 2)));   //IGNORE-STYLE-CHECK[L004]
        SetVoltage(config_.ctrlPort, config_.d3, static_cast<DL>(READ_BIT(data, 3)));   //IGNORE-STYLE-CHECK[L004]
    };
    switch (M) {
        case SM::kCommand: 
            SetLowVoltage(config_.ctrlPort, config_.rs);
            SetLowVoltage(config_.ctrlPort, config_.rw);
            break;
        case SM::kData:
            SetHighVoltage(config_.ctrlPort, config_.rs);
            SetLowVoltage(config_.ctrlPort, config_.rw);
            break;
    }
    // Handle 8-bits data transfer mode
    if (config_.IsEightBit()) {
        WritePort(config_.ctrlPort, d);
        Pulse();
        return;
    }
    Write4Bits(d >> 4);
    Pulse();
    Write4Bits(d);
    Pulse();
}

template void Lcd::Send<Lcd::SendMode::kCommand>(uint8_t);
template void Lcd::Send<Lcd::SendMode::kData>(uint8_t);

// =============================================================================
// ------------------------- PUBLIC METHODS ------------------------------------
// =============================================================================

Lcd::Lcd(LcdConfig& config): config_(config) {
    // 1) --- Set control pins as output pins
    Init(config_.ctrlPort, config_.en);
    Init(config_.ctrlPort, config_.rs);
    Init(config_.ctrlPort, config_.rw);
    DataTransferModes mode;
    if (config_.IsEightBit()) {
        // 2.a) --- Set pins as output i.e. data port
        Init(config_.dataPort);
        mode = DataTransferModes::kEightBits;
    } 
    else {
        // 2.b) --- Set data pints as output pins
        Init(config_.dataPort, config_.d0);
        Init(config_.dataPort, config_.d1);
        Init(config_.dataPort, config_.d2);
        Init(config_.dataPort, config_.d3);
        mode = DataTransferModes::kFourBits;
    }
    
    // 3) --- Return to home 
    Send<SM::kCommand>(Command::kReturnHome);
    _delay_ms(50);
    
    // 4) --- Function set (data transfer mode)
    Send<SM::kCommand>(mode);
    _delay_ms(1);

    // 5) --- On/off display control
    Send<SM::kCommand>(Command::kDisplayOn_CursorOff);
    _delay_ms(1);

    // 6) --- Clear Screen
    ClearScreen();

    // 7) --- Entry mode
    Send<SM::kCommand>(Command::kEntryModeIncrement_ShiftOff);
    _delay_ms(5);
}

void Lcd::ClearScreen() {
    Send<SM::kCommand>(Command::kClearScreen);
    _delay_ms(5);
}

void Lcd::Display(size_t data, NumberMode mode) {
    char buff[16];
    itoa(data, buff, mode);
}

void Lcd::Display(char data) {
    Send<SM::kData>(data);
}

void Lcd::Display(const char* data) {
    uint8_t i = 0;
    while (data[i] != '\0') {
        Send<SM::kData>(data[i++]);
    }
}

void Lcd::Display(float data, uint8_t prec) {
    using namespace utils::math;
    FloatingNumber floatNum = SeparateFloatingNumber(data, prec);
    // --- Display integer part
    Display(floatNum.integerPart);
    // --- Display prec
    Display('.');
    // --- Display fraction part
    Display(floatNum.fractionPart);
}

void Lcd::SetCursor(uint8_t row, uint8_t col) { // 0-based rows and cols
    // Evaluate the command mode
    // Handle case of invalid rows and cols (return to 0,0)
    if (row < 0 || row >= LCD_NUMBER_OF_ROWS 
     || col < 0 || col >= LCD_NUMBER_OF_COLS) {
        Send<SM::kCommand>(Command::kDDRAM);
        _delay_ms(1);
        return;
    }
    
    // auto GetOffset = [&]() -> uint8_t {
    //     row == 0 ? 0 : 64;
    // };
    // Send<SM::kCommand>(kDDRAM + col + GetOffset());
    Send<SM::kCommand>(kDDRAM + col + (row * 64));
    _delay_us(50);
}

void Lcd::EnableCursor() {
    Send<SM::kCommand>(Command::kDisplayOn_CursorOn);
    _delay_us(50);
}

void Lcd::DisableCursor() {
    Send<SM::kCommand>(Command::kDisplayOn_CursorOff);
    _delay_us(50);
}

void Lcd::ShiftRight() {
    Send<SM::kCommand>(Command::kShiftRight);
    _delay_us(50);
}

void Lcd::ShiftLeft() {
    Send<SM::kCommand>(Command::kShiftLeft);
    _delay_us(50);
}

void Lcd::DisplayOn () {
    Send<SM::kCommand>(Command::kDisplayOn_CursorOff);
    _delay_us(50);
}

void Lcd::DisplayOff() {
    Send<SM::kCommand>(Command::kDisplayOff_CursorOff);
    _delay_us(50);
}

void Lcd::BlinkOn() {
    Send<SM::kCommand>(Command::kBlinkOn);
    _delay_us(50);
}

void Lcd::BlinkOff() {
    Send<SM::kCommand>(Command::kBlinkOff);
    _delay_us(50);
}

void Lcd::StoreCustomChar(char pChar_Arr[], uint8_t location) {
    // 1) Point to CG-RAM
    Send<SM::kCommand>(Command::kCGRAM + (location * 8));
    // 2) Copy characters from byte 0 to byte 7 to CGRAM
    for (uint8_t i = 0 ; i < 8 ; ++i) {
        Send<SM::kData>(pChar_Arr[i]);
    }
    // 3) Back to DDRAM
    Send<SM::kCommand>(Command::kDDRAM);
}

void Lcd::DisplayCustomChar(uint8_t location, uint8_t row, uint8_t col) {
    // THIS STEP IS NECESSARY TO DISPLAY CUSTOM CHARACTER
    SetCursor(row, col); 
    Send<SM::kData>(location);
}
