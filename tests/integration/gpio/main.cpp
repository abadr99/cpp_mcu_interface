#include <stdint.h>

#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../utils/inc/Test.h"
 
using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;

int main () {
    //Create a GPIO object of portA
    Gpio<Port::kPortA> GPIOA;
    //Set pin A1 as output
    GPIOA.SetDirection<Pin::kPin1, DirectionState::kOutput>();
    print_str("//////////////////////////GPIO_AA////////////////////////");
    new_line();
    print_str("DDRA: ");
    print_num(*((volatile uint8_t*) DDRA));
    new_line();
    //Set pin A1 as input
    GPIOA.SetDirection<Pin::kPin1, DirectionState::kInput>();
    print_str("DDRA: ");
    print_num(*((volatile uint8_t*) DDRA));
    new_line();
    //Set portA  as output
    GPIOA.SetDirection(255);
    print_str("DDRA: ");
    print_num(*((volatile uint8_t*) DDRA));
    new_line();
    //set pin a0 as high
    GPIOA.Write<Pin:: kPin0, DigitalLevel :: kHigh>();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t*) PORTA));
    new_line();
    //set pin a0 as low
    GPIOA.Write<Pin:: kPin0, DigitalLevel :: kLow>();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t*) PORTA));
    new_line();
    //set port A as high
    GPIOA.Write(255);
    print_str("PORTA: ");
    print_num(*((volatile uint8_t*) PORTA));
    new_line();

    //set port A as low
    GPIOA.Write(0);
    print_str("PORTA: ");
    print_num(*((volatile uint8_t*) PORTA));
    new_line();
    
    //set pin A7 as input pullup
    GPIOA.SetDirection<Pin::kPin7, DirectionState::kInputPullUp>();
    print_str("DDRA: ");
    print_num(*((volatile uint8_t*) DDRA));
    new_line();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t*) PORTA));
    new_line();

    //set port A as input 
    
    GPIOA.SetDirection(0);
    print_str("DDRA: ");
    print_num(*((volatile uint8_t*) DDRA));
    new_line();
    print_str("PORTA: ");
    print_num(*((volatile uint8_t*) PORTA));
    new_line();
    print_str("//////////////////////////GPIO_B////////////////////////");
    new_line();
    //Create a GPIO object of portB
    Gpio<Port::kPortB> GPIOB;
    //Set pin B1 as output
    GPIOB.SetDirection<Pin::kPin1, DirectionState::kOutput>();
    print_str("DDRB: ");
    print_num(*((volatile uint8_t*) DDRB));
    new_line();
    //Set pin B1 as input
    GPIOB.SetDirection<Pin::kPin1, DirectionState::kInput>();
    print_str("DDRB: ");
    print_num(*((volatile uint8_t*) DDRB));
    new_line();
    //Set portB  as output
    GPIOB.SetDirection(255);
    print_str("DDRB: ");
    print_num(*((volatile uint8_t*) DDRB));
    new_line();
    //set pin B0 as high
    GPIOB.Write<Pin:: kPin0, DigitalLevel :: kHigh>();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t*) PORTB));
    new_line();
    //set pin B0 as low
    GPIOB.Write<Pin:: kPin0, DigitalLevel :: kLow>();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t*) PORTB));
    new_line();
    //set port B as high
    GPIOB.Write(255);
    print_str("PORTB: ");
    print_num(*((volatile uint8_t*) PORTB));
    new_line();

    //set port B as low
    GPIOB.Write(0);
    print_str("PORTB ");
    print_num(*((volatile uint8_t*) PORTB));
    new_line();
    
    //set pin A7 as input pullup
    GPIOB.SetDirection<Pin::kPin7, DirectionState::kInputPullUp>();
    print_str("DDRB: ");
    print_num(*((volatile uint8_t*) DDRB));
    new_line();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t*) PORTB));
    new_line();

    //set port B as input 
    
    GPIOB.SetDirection(0);
    print_str("DDRB: ");
    print_num(*((volatile uint8_t*) DDRB));
    new_line();
    print_str("PORTB: ");
    print_num(*((volatile uint8_t*) PORTB));
    new_line();
    
   
    print_str("//////////////////////////GPIO_C////////////////////////");
    new_line();
    //Create a GPIO object of portC
    Gpio<Port::kPortC> GPIOC;
    //Set pin C1 as output
    GPIOC.SetDirection<Pin::kPin1, DirectionState::kOutput>();
    print_str("DDRC: ");
    print_num(*((volatile uint8_t*) DDRC));
    new_line();
    //Set pin C1 as input
    GPIOC.SetDirection<Pin::kPin1, DirectionState::kInput>();
    print_str("DDRC: ");
    print_num(*((volatile uint8_t*) DDRC));
    new_line();
    //Set portC  as output
    GPIOC.SetDirection(255);
    print_str("DDRC: ");
    print_num(*((volatile uint8_t*) DDRC));
    new_line();
    //set pin C0 as high
    GPIOC.Write<Pin:: kPin0, DigitalLevel :: kHigh>();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t*) PORTC));
    new_line();
    //set pin C0 as low
    GPIOC.Write<Pin:: kPin0, DigitalLevel :: kLow>();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t*) PORTC));
    new_line();
    //set port C as high
    GPIOC.Write(255);
    print_str("PORTC: ");
    print_num(*((volatile uint8_t*) PORTC));
    new_line();

    //set port C as low
    GPIOC.Write(0);
    print_str("PORTC ");
    print_num(*((volatile uint8_t*) PORTC));
    new_line();
    
    //set pin C7 as input pullup
    GPIOC.SetDirection<Pin::kPin7, DirectionState::kInputPullUp>();
    print_str("DDRC: ");
    print_num(*((volatile uint8_t*) DDRC));
    new_line();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t*) PORTC));
    new_line();

    //set port C as input 
    
    GPIOC.SetDirection(0);
    print_str("DDRC: ");
    print_num(*((volatile uint8_t*) DDRC));
    new_line();
    print_str("PORTC: ");
    print_num(*((volatile uint8_t*) PORTC));
    new_line();

    print_str("//////////////////////////GPIO_D////////////////////////");
    new_line();
    //Create a GPIO object of portD
    Gpio<Port::kPortD> GPIOD;
   
    //Set pin D1 as output
    GPIOD.SetDirection<Pin::kPin1, DirectionState::kOutput>();
    print_str("DDRD: ");
    print_num(*((volatile uint8_t*) DDRD));
    new_line();
    //Set pin D1 as input
    GPIOD.SetDirection<Pin::kPin1, DirectionState::kInput>();
    print_str("DDRD: ");
    print_num(*((volatile uint8_t*) DDRD));
    new_line();
    //Set portD  as output
    GPIOD.SetDirection(255);
    print_str("DDRD: ");
    print_num(*((volatile uint8_t*) DDRD));
    new_line();
    //set pin D0 as high
    GPIOD.Write<Pin:: kPin0, DigitalLevel :: kHigh>();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t*) PORTD));
    new_line();
    //set pin D0 as low
    GPIOD.Write<Pin:: kPin0, DigitalLevel :: kLow>();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t*) PORTD));
    new_line();
    //set port D as high
    GPIOD.Write(255);
    print_str("PORTD: ");
    print_num(*((volatile uint8_t*) PORTD));
    new_line();

    //set port D as low
    GPIOD.Write(0);
    print_str("PORTD ");
    print_num(*((volatile uint8_t*) PORTD));
    new_line();
    
    //set pin D7 as input pullup
    GPIOD.SetDirection<Pin::kPin7, DirectionState::kInputPullUp>();
    print_str("DDRD: ");
    print_num(*((volatile uint8_t*) DDRD));
    new_line();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t*) PORTD));
    new_line();

    //set port D as input 
    
    GPIOD.SetDirection(0);
    print_str("DDRD: ");
    print_num(*((volatile uint8_t*) DDRD));
    new_line();
    print_str("PORTD: ");
    print_num(*((volatile uint8_t*) PORTD));
    new_line();
    print_num_binary(0);
    print_str("\n");
    print_num_binary(255);
    print_str("\n");
    print_num_binary(15);
    print_str("\n");
    print_num_binary(200);
    print_str("\n");
    print_num_binary(4);
    print_str("\n");
}
