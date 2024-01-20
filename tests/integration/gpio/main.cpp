#include <stdint.h>

#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../tests/impl/AVRTest.h"
 
using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;

/*make compile-test src=tests/integration/gpio/main.cpp 
target=tests/integration/gpio/gpio
*/
//sh scripts/testing/run-simu-avr.sh tests/integration/gpio/gpio.testelf
//sh scripts/testing/run-regressions.sh -d tests/integration/gpio/

int main () {
    {
    //Create a test for GPIO
    avr::test::AVRTest TESTER("GPIOA");
    //Create a GPIO object of portA
    Gpio GPIO(kPortA);
    //Set pin A0 as output
    GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kOutput );
    //Test DDRA
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRA), static_cast<uint8_t>(0x01));
  
    //Set pin A0 as input
    GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kInput );
    //Test DDRA
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRA), static_cast<uint8_t>(0x00));

    //Set portA  as output
    GPIO.SetPortDirection(0x0F);
    //Test DDRA
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRA), static_cast<uint8_t>(0x0F));

    //set pin a0 as input pullup
    GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kInputPullUp);
    //Test DDRA
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRA), static_cast<uint8_t>(0x0E));
    //Test PORTA
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTA), static_cast<uint8_t>(0x01));

    //set port A as output
    GPIO.SetPortDirection(0xFF);
    //Test DDRA
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRA), static_cast<uint8_t>(0xFF));
    //Test PORTA
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTA), static_cast<uint8_t>(0x01));

    //set pin a7 as high
    GPIO.WritePin(kPin7, Gpio::DigitalLevel::kHigh);
    //Test PORTA
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTA), static_cast<uint8_t>(0x81));

    //set pin a7 as low
    GPIO.WritePin(kPin7, Gpio::DigitalLevel::kLow);
    //Test PORTA
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTA), static_cast<uint8_t>(0x01));

    //set port A as high
    GPIO.WritePort(0xFF);
    //Test PORTA
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTA), static_cast<uint8_t>(0xFF));

    }

        {
    //Create a test for gpioB
    avr::test::AVRTest TESTER("GPIOB");
    //Create a GPIO object of portB
    Gpio GPIO(kPortB);
    //Set pin B5 as output
    GPIO.SetPinDirection(kPin5, Gpio::DirectionState::kOutput );
    //Test DDRB
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRB), static_cast<uint8_t>(0x20));

    //Set pin B6 as output
    GPIO.SetPinDirection(kPin6, Gpio::DirectionState::kOutput );
    //Test DDRB
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRB), static_cast<uint8_t>(0x60));
  
    //Set pin B5 as input
    GPIO.SetPinDirection(kPin5, Gpio::DirectionState::kInput );
    //Test DDRB
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRB), static_cast<uint8_t>(0x40));
    //Set pin B6 as input
    GPIO.SetPinDirection(kPin6, Gpio::DirectionState::kInput );
    //Test DDRB
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRB), static_cast<uint8_t>(0x00));

    //Set portB  
    GPIO.SetPortDirection(0x88);
    //Test DDRB
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRB), static_cast<uint8_t>(0x88));

    //set pin B1 as input pullup
    GPIO.SetPinDirection(kPin1, Gpio::DirectionState::kInputPullUp);
    //Test DDRB
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRB), static_cast<uint8_t>(0x88));
    //Test PORTB
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTB), static_cast<uint8_t>(0x02));

    //set port B as output
    GPIO.SetPortDirection(0xFF);
    //Test DDRB
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRB), static_cast<uint8_t>(0xFF));
    //Test PORTB
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTB), static_cast<uint8_t>(0x02));

    //set pin B4 as high
    GPIO.WritePin(kPin4, Gpio::DigitalLevel::kHigh);
    //Test PORTB
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTB), static_cast<uint8_t>(0x12));

    //set pin B4 as low
    GPIO.WritePin(kPin4, Gpio::DigitalLevel::kLow);
    //Test PORTB
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTB), static_cast<uint8_t>(0x02));

    //set port B as high
    GPIO.WritePort(0xFF);
    //Test PORTB
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTB), static_cast<uint8_t>(0xFF));

    }
            {
    //Create a test for gpioC
    avr::test::AVRTest TESTER("GPIOC");
    //Create a GPIO object of portC
    Gpio GPIO(kPortC);
    //Set pin C2 as output
    GPIO.SetPinDirection(kPin2, Gpio::DirectionState::kOutput );
    //Test DDRC
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRC), static_cast<uint8_t>(0x04));

    //Set pin B3 as output
    GPIO.SetPinDirection(kPin3, Gpio::DirectionState::kOutput );
    //Test DDRC
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRC), static_cast<uint8_t>(0x0C));
  
    //Set pin B3 as input
    GPIO.SetPinDirection(kPin3, Gpio::DirectionState::kInput );
    //Test DDRC
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRC), static_cast<uint8_t>(0x04));
    //Set pin B2 as input
    GPIO.SetPinDirection(kPin2, Gpio::DirectionState::kInput );
    //Test DDRC
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRC), static_cast<uint8_t>(0x00));

    //Set portC 
    GPIO.SetPortDirection(0xF0);
    //Test DDRC
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRC), static_cast<uint8_t>(0xF0));

    //set pin C7 as input pullup
    GPIO.SetPinDirection(kPin7, Gpio::DirectionState::kInputPullUp);
    //Test DDRC
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRC), static_cast<uint8_t>(0x70));
    //Test PORTC
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTC), static_cast<uint8_t>(0x80));

    //set port C as output
    GPIO.SetPortDirection(0xFF);
    //Test DDRC
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRC), static_cast<uint8_t>(0xFF));
    //Test PORTC
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTC), static_cast<uint8_t>(0x80));

    //set pin C0 as high
    GPIO.WritePin(kPin0, Gpio::DigitalLevel::kHigh);
    //Test PORTC
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTC), static_cast<uint8_t>(0x81));

    //set pin C0 as low
    GPIO.WritePin(kPin0, Gpio::DigitalLevel::kLow);
    //Test PORTC
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTC), static_cast<uint8_t>(0x80));

    //set port B 
    GPIO.WritePort(0xCD);
    //Test PORTC
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTC), static_cast<uint8_t>(0xCD));

    }

            {
    //Create a test for gpioD
    avr::test::AVRTest TESTER("GPIOD");
    //Create a GPIO object of portD
    Gpio GPIO(kPortD);
    //Set pin D1 as output
    GPIO.SetPinDirection(kPin1, Gpio::DirectionState::kOutput );
    //Test DDRD
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRD), static_cast<uint8_t>(0x02));

    //Set pin D0 as output
    GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kOutput );
    //Test DDRD
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRD), static_cast<uint8_t>(0x03));
  
    //Set pin D1 as input
    GPIO.SetPinDirection(kPin1, Gpio::DirectionState::kInput );
    //Test DDRD
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRD), static_cast<uint8_t>(0x01));
    //Set pin D0 as input
    GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kInput );
    //Test DDRD
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRD), static_cast<uint8_t>(0x00));

    //Set portD
    GPIO.SetPortDirection(0xB8);
    //Test DDRD
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRD), static_cast<uint8_t>(0xB8));

    //set pin D0 as input pullup
    GPIO.SetPinDirection(kPin0, Gpio::DirectionState::kInputPullUp);
    //Test DDRD
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRD), static_cast<uint8_t>(0xB8));
    //Test PORTD
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTD), static_cast<uint8_t>(0x01));

    //set port D as output
    GPIO.SetPortDirection(0xFF);
    //Test DDRD
    TESTER.Expect_Eq(*((volatile uint8_t*)DDRD), static_cast<uint8_t>(0xFF));
    //Test PORTD
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTD), static_cast<uint8_t>(0x01));

    //set pin D7 as high
    GPIO.WritePin(kPin7, Gpio::DigitalLevel::kHigh);
    //Test PORTD
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTD), static_cast<uint8_t>(0x81));

    //set pin D7 as low
    GPIO.WritePin(kPin7, Gpio::DigitalLevel::kLow);
    //Test PORTD
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTD), static_cast<uint8_t>(0x01));

    //set port D 
    GPIO.WritePort(0x00);
    //Test PORTD
    TESTER.Expect_Eq(*((volatile uint8_t*)PORTD), static_cast<uint8_t>(0x00));

    }
   
}
