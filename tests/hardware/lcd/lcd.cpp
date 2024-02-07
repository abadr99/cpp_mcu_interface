 /**
 * @file lcd.cpp
 * @brief  - A test for LCD, 8-bit mode
 *         - Tests displaying a character,
 *         - number in its binary, hex, decmal & octal form
 *         - Tests some commands like shifting left & right,
 *         - enabling curser & blinking it
 * @version 0.1
 * @date 2024-02-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdint.h>
#include <stddef.h>
#include <util/delay.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../hal/inc/GpioDeviceInterface.h"
#include "../../../hal/inc/Lcd.h"
#include "../../../hal/inc/Led.h"


using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;
using namespace avr::hal::lcd;
/*
make compile-hardware-test test=tests/hardware/lcd/lcd.cpp name=lcd
*/

int main() 
{ 
    LcdConfig fig;
    fig.ctrlPort=Gpio::Port::kPortA;
    fig.dataPort=Gpio::Port::kPortC;
    fig.en=Gpio::Pin::kPin0;
    fig.rs=Gpio::Pin::kPin1;
    fig.rw=Gpio::Pin::kPin2;
    fig.transferMode=kEightBits;
    Lcd lcd_1(fig);
    lcd_1.Display('a');
    _delay_ms(1000);
    lcd_1.ClearScreen();
    lcd_1.Display("LCD HW test");
    _delay_ms(1000);
    lcd_1.ClearScreen();
    lcd_1.Display(4, NumberMode::kDec);
    _delay_ms(1000);
    lcd_1.ClearScreen();
    lcd_1.Display(3.1245, 2);
    _delay_ms(1000);
    lcd_1.ClearScreen();
    lcd_1.BlinkOn();
    lcd_1.EnableCursor();
    lcd_1.SetCursor(1, 5);
    lcd_1.Display(4, NumberMode::kBin);
    _delay_ms(1000);
    lcd_1.ClearScreen();
    lcd_1.Display(10, NumberMode::kHex);
    _delay_ms(1000);
    lcd_1.ClearScreen();
    lcd_1.Display(10, NumberMode::kOct);
    _delay_ms(1000);
    lcd_1.ClearScreen();
    lcd_1.SetCursor(0, 2);
    lcd_1.Display("LCD");
    lcd_1.BlinkOn();
    lcd_1.ShiftRight();
     _delay_ms(1000);
    lcd_1.ShiftRight();
    _delay_ms(1000);
    lcd_1.ShiftRight();
    _delay_ms(1000);
    lcd_1.ShiftRight();
     _delay_ms(1000);
    lcd_1.ShiftLeft();
     _delay_ms(1000);
    lcd_1.ShiftLeft();
     _delay_ms(1000);
    lcd_1.ClearScreen();
    lcd_1.SetCursor(1, 1);
     char pChar_Arr[]={0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x1E};
    lcd_1.StoreCustomChar(pChar_Arr, 2);
    lcd_1.DisplayCustomChar(2, 1, 1);

    while (1) {
        /*Empty*/
    }

}
