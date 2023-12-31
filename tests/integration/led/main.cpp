#include <stdint.h>
#include <util/delay.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../hal/inc/GpioDeviceInterface.h"
#include "../../../hal/inc/Led.h"
#include "../../../utils/inc/Test.h"

using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::hal::led;
using namespace avr::types;

int main()
{
    // create led object for A0
    Led<kPortA, kActiveHigh> led_1(kPin0);

    print_str("//////////////////////////PORT_A////////////////////////");
    new_line();
    print_str("DDRA: ");
    print_num(*((volatile uint8_t *)DDRA));
    new_line();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    // turn on the led
    led_1.TurnOn();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    // turn off the led
    led_1.TurnOff();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    // toggle the led
    led_1.Toggle();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    bool led_state;
    // print state of the led
    led_state = led_1.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_1.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // toggle the led
    led_1.Toggle();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    // print state of the led
    led_state = led_1.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_1.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();

    // create led object for A5
    Led<kPortA, kActiveHigh> led_2(kPin5);
    new_line();
    print_str("DDRA: ");
    print_num(*((volatile uint8_t *)DDRA));
    new_line();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    // turn on the led
    led_2.TurnOn();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    // turn off the led
    led_2.TurnOff();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    // toggle the led
    led_2.Toggle();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    // print state of the led
    led_state = led_2.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_2.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // toggle the led
    led_2.Toggle();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t *)PORTA));
    new_line();
    // print state of the led
    led_state = led_2.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_2.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();

    // create led object for B1
    Led<kPortB, kActiveLow> led_3(kPin1);

    print_str("//////////////////////////PORT_B////////////////////////");
    new_line();
    print_str("DDRB: ");
    print_num(*((volatile uint8_t *)DDRB));
    new_line();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();
    // turn on the led
    led_3.TurnOn();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();
    // turn off the led
    led_3.TurnOff();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();
    // toggle the led
    led_3.Toggle();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();

    // print state of the led
    led_state = led_3.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_3.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // toggle the led
    led_3.Toggle();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();
    // print state of the led
    led_state = led_3.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_3.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();

    // create led object for B2
    Led<kPortB, kActiveHigh> led_4(kPin2);
    new_line();
    print_str("DDRB: ");
    print_num(*((volatile uint8_t *)DDRB));
    new_line();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();
    // turn on the led
    led_4.TurnOn();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();
    // turn off the led
    led_4.TurnOff();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();
    // toggle the led
    led_4.Toggle();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();

    // print state of the led
    led_state = led_4.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_4.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // toggle the led
    led_4.Toggle();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t *)PORTB));
    new_line();
    // print state of the led
    led_state = led_4.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_4.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();

    //create object of led C3
    Led<kPortC, kActiveHigh> led_5(kPin3);
    print_str("//////////////////////////PORT_C////////////////////////");
    new_line();
    print_str("DDRC: ");
    print_num(*((volatile uint8_t *)DDRC));
    new_line();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();
    // turn on the led
    led_5.TurnOn();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();
    // turn off the led
    led_5.TurnOff();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();
    // toggle the led
    led_5.Toggle();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();

    // print state of the led
    led_state = led_5.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_5.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // toggle the led
    led_5.Toggle();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();
    // print state of the led
    led_state = led_5.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_5.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    //create object of led C4
    Led<kPortC, kActiveHigh> led_6(kPin4);
    new_line();
    print_str("DDRC: ");
    print_num(*((volatile uint8_t *)DDRC));
    new_line();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();
    // turn on the led
    led_6.TurnOn();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();
    // turn off the led
    led_6.TurnOff();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();
    // toggle the led
    led_6.Toggle();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();

    // print state of the led
    led_state = led_6.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_6.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // toggle the led
    led_6.Toggle();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTC));
    new_line();
    // print state of the led
    led_state = led_6.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_6.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();

    //create object of led D6
    Led<kPortD, kActiveHigh> led_7(kPin6);
    print_str("//////////////////////////PORT_D////////////////////////");
    new_line();
    print_str("DDRD: ");
    print_num(*((volatile uint8_t *)DDRD));
    new_line();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();
    // turn on the led
    led_7.TurnOn();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();
    // turn off the led
    led_7.TurnOff();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();
    // toggle the led
    led_7.Toggle();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();

    // print state of the led
    led_state = led_7.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_7.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // toggle the led
    led_7.Toggle();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();
    // print state of the led
    led_state = led_7.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_7.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();

    //create object of led D7
    Led<kPortD, kActiveHigh> led_8(kPin7);
    new_line();
    print_str("DDRD: ");
    print_num(*((volatile uint8_t *)DDRD));
    new_line();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();
    // turn on the led
    led_8.TurnOn();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();
    // turn off the led
    led_8.TurnOff();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();
    // toggle the led
    led_8.Toggle();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();

    // print state of the led
    led_state = led_8.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_8.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // toggle the led
    led_8.Toggle();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t *)PORTD));
    new_line();
    // print state of the led
    led_state = led_8.IsOn();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
    // print state of the led
    led_state = led_8.IsOff();
    print_str("Led state: ");
    print_num(led_state);
    new_line();
}
