/* 
 * make compile-test src=tests/integration/gpio/main.cpp target=tests/integration/gpio/gpio //IGNORE-STYLE-CHECK[L004]
 * sh scripts/testing/run-simu-avr.sh tests/integration/gpio/gpio.testelf
 * sh scripts/testing/run-regressions.sh -d tests/integration/gpio/
*/

#include <stdint.h>

#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../tests/impl/AVRTest.h"
 
using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;

#define PORTA                          (*((volatile uint8_t*)0x3B))
#define DDRA                           (*((volatile uint8_t*)0x3A))
#define PINA                           (*((volatile uint8_t*)0x39))
#define PORTB                          (*((volatile uint8_t*)0x38))
#define DDRB                           (*((volatile uint8_t*)0x37))
#define PINB                           (*((volatile uint8_t*)0x36))
#define PORTC                          (*((volatile uint8_t*)0x35))
#define DDRC                           (*((volatile uint8_t*)0x34))
#define PINC                           (*((volatile uint8_t*)0x33))
#define PORTD                          (*((volatile uint8_t*)0x32))
#define DDRD                           (*((volatile uint8_t*)0x31))
#define PIND                           (*((volatile uint8_t*)0x30))

int main () {
    using DS = Gpio::DirectionState;
    {
        avr::test::AVRTest TESTER("GPIOA");
        
        Gpio::SetPinDirection(kPortA, kPin0, DS::kOutput);
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0x01));
    
        Gpio::SetPinDirection(kPortA, kPin0, DS::kInput );
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0x00));

        Gpio::SetPortDirection(kPortA, 0x0F);
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0x0F));

        Gpio::SetPinDirection(kPortA, kPin0, DS::kInputPullUp);
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0x0E));
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0x01));

        Gpio::SetPortDirection(kPortA, 0xFF);
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0xFF));
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0x01));

        Gpio::WritePin(kPortA, kPin7, Gpio::DigitalLevel::kHigh);
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0x81));

        Gpio::WritePin(kPortA, kPin7, Gpio::DigitalLevel::kLow);
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0x01));

        Gpio::WritePort(kPortA, 0xFF);
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0xFF));
    }
    {
        avr::test::AVRTest TESTER("GPIOB");

        Gpio::SetPinDirection(kPortB, kPin5, DS::kOutput );
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x20));

        Gpio::SetPinDirection(kPortB, kPin6, DS::kOutput);
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x60));
    
        Gpio::SetPinDirection(kPortB, kPin5, DS::kInput );
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x40));
        Gpio::SetPinDirection(kPortB, kPin6, DS::kInput );
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x00));

        Gpio::SetPortDirection(kPortB, 0x88);
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x88));

        Gpio::SetPinDirection(kPortB, kPin1, DS::kInputPullUp);
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x88));
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0x02));

        Gpio::SetPortDirection(kPortB, 0xFF);
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0xFF));
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0x02));

        Gpio::WritePin(kPortB, kPin4, Gpio::DigitalLevel::kHigh);
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0x12));

        Gpio::WritePin(kPortB, kPin4, Gpio::DigitalLevel::kLow);
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0x02));

        Gpio::WritePort(kPortB, 0xFF);
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0xFF));

    }
    {
        avr::test::AVRTest TESTER("GPIOC");

        Gpio::SetPinDirection(kPortC, kPin2, DS::kOutput );
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x04));

        Gpio::SetPinDirection(kPortC, kPin3, DS::kOutput );
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x0C));
    
        Gpio::SetPinDirection(kPortC, kPin3, DS::kInput );
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x04));

        Gpio::SetPinDirection(kPortC, kPin2, DS::kInput );
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x00));

        Gpio::SetPortDirection(kPortC, 0xF0);
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0xF0));

        Gpio::SetPinDirection(kPortC, kPin7, DS::kInputPullUp);
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x70));
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0x80));

        Gpio::SetPortDirection(kPortC, 0xFF);
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0xFF));
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0x80));

        Gpio::WritePin(kPortC, kPin0, Gpio::DigitalLevel::kHigh);
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0x81));

        Gpio::WritePin(kPortC, kPin0, Gpio::DigitalLevel::kLow);
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0x80));

        Gpio::WritePort(kPortC, 0xCD);
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0xCD));
    }
    {
        avr::test::AVRTest TESTER("GPIOD");
   
        Gpio::SetPinDirection(kPortD, kPin1, DS::kOutput );
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0x02));

        Gpio::SetPinDirection(kPortD, kPin0, DS::kOutput );
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0x03));
    
        Gpio::SetPinDirection(kPortD, kPin1, DS::kInput );
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0x01));

        Gpio::SetPinDirection(kPortD, kPin0, DS::kInput );
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0x00));

        Gpio::SetPortDirection(kPortD, 0xB8);
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0xB8));

        Gpio::SetPinDirection(kPortD, kPin0, DS::kInputPullUp);
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0xB8));
        TESTER.Expect_Eq(PORTD, static_cast<uint8_t>(0x01));

        Gpio::SetPortDirection(kPortD, 0xFF);
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0xFF));
        TESTER.Expect_Eq(PORTD, static_cast<uint8_t>(0x01));

        Gpio::WritePin(kPortD, kPin7, Gpio::DigitalLevel::kHigh);
        TESTER.Expect_Eq(PORTD, static_cast<uint8_t>(0x81));

        Gpio::WritePin(kPortD, kPin7, Gpio::DigitalLevel::kLow);
        TESTER.Expect_Eq(PORTD, static_cast<uint8_t>(0x01));

        Gpio::WritePort(kPortD, 0x00);
        TESTER.Expect_Eq(PORTD, static_cast<uint8_t>(0x00));
    }
}
