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
    {
        avr::test::AVRTest TESTER("GPIOA");
        Gpio GPIO(kPortA);
        
        GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kOutput );
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0x01));
    
        GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kInput );
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0x00));

        GPIO.SetPortDirection(0x0F);
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0x0F));

        GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kInputPullUp);
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0x0E));
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0x01));

        GPIO.SetPortDirection(0xFF);
        TESTER.Expect_Eq(DDRA, static_cast<uint8_t>(0xFF));
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0x01));

        GPIO.WritePin(kPin7, Gpio::DigitalLevel::kHigh);
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0x81));

        GPIO.WritePin(kPin7, Gpio::DigitalLevel::kLow);
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0x01));

        GPIO.WritePort(0xFF);
        TESTER.Expect_Eq(PORTA, static_cast<uint8_t>(0xFF));
    }
    {
        avr::test::AVRTest TESTER("GPIOB");
        Gpio GPIO(kPortB);
        GPIO.SetPinDirection(kPin5, Gpio::DirectionState::kOutput );
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x20));

        GPIO.SetPinDirection(kPin6, Gpio::DirectionState::kOutput );
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x60));
    
        GPIO.SetPinDirection(kPin5, Gpio::DirectionState::kInput );
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x40));
        GPIO.SetPinDirection(kPin6, Gpio::DirectionState::kInput );
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x00));

        GPIO.SetPortDirection(0x88);
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x88));

        GPIO.SetPinDirection(kPin1, Gpio::DirectionState::kInputPullUp);
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0x88));
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0x02));

        GPIO.SetPortDirection(0xFF);
        TESTER.Expect_Eq(DDRB, static_cast<uint8_t>(0xFF));
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0x02));

        GPIO.WritePin(kPin4, Gpio::DigitalLevel::kHigh);
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0x12));

        GPIO.WritePin(kPin4, Gpio::DigitalLevel::kLow);
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0x02));

        GPIO.WritePort(0xFF);
        TESTER.Expect_Eq(PORTB, static_cast<uint8_t>(0xFF));

    }
    {
        avr::test::AVRTest TESTER("GPIOC");
        Gpio GPIO(kPortC);

        GPIO.SetPinDirection(kPin2, Gpio::DirectionState::kOutput );
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x04));

        GPIO.SetPinDirection(kPin3, Gpio::DirectionState::kOutput );
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x0C));
    
        GPIO.SetPinDirection(kPin3, Gpio::DirectionState::kInput );
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x04));

        GPIO.SetPinDirection(kPin2, Gpio::DirectionState::kInput );
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x00));

        GPIO.SetPortDirection(0xF0);
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0xF0));

        GPIO.SetPinDirection(kPin7, Gpio::DirectionState::kInputPullUp);
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0x70));
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0x80));

        GPIO.SetPortDirection(0xFF);
        TESTER.Expect_Eq(DDRC, static_cast<uint8_t>(0xFF));
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0x80));

        GPIO.WritePin(kPin0, Gpio::DigitalLevel::kHigh);
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0x81));

        GPIO.WritePin(kPin0, Gpio::DigitalLevel::kLow);
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0x80));

        GPIO.WritePort(0xCD);
        TESTER.Expect_Eq(PORTC, static_cast<uint8_t>(0xCD));
    }
    {
        avr::test::AVRTest TESTER("GPIOD");
        Gpio GPIO(kPortD);
   
        GPIO.SetPinDirection(kPin1, Gpio::DirectionState::kOutput );
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0x02));

        GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kOutput );
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0x03));
    
        GPIO.SetPinDirection(kPin1, Gpio::DirectionState::kInput );
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0x01));

        GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kInput );
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0x00));

        GPIO.SetPortDirection(0xB8);
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0xB8));

        GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kInputPullUp);
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0xB8));
        TESTER.Expect_Eq(PORTD,static_cast<uint8_t>(0x01));

        GPIO.SetPortDirection(0xFF);
        TESTER.Expect_Eq(DDRD, static_cast<uint8_t>(0xFF));
        TESTER.Expect_Eq(PORTD, static_cast<uint8_t>(0x01));

        GPIO.WritePin(kPin7, Gpio::DigitalLevel::kHigh);
        TESTER.Expect_Eq(PORTD, static_cast<uint8_t>(0x81));

        GPIO.WritePin(kPin7, Gpio::DigitalLevel::kLow);
        TESTER.Expect_Eq(PORTD, static_cast<uint8_t>(0x01));

        GPIO.WritePort(0x00);
        TESTER.Expect_Eq(PORTD, static_cast<uint8_t>(0x00));
    }
   
}
