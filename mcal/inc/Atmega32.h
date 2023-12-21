#ifndef _ATMEGA32_H_
#define _ATMEGA32_H_

namespace avr{
namespace types{

enum Port {
    kPortA,
    kPortB,
    kPortC,
    kPortD,
};

enum Pin {
    kPin0, kPin1, kPin2, kPin3,
    kPin4, kPin5, kPin6, kPin7,
};
using AvrRegWidth  = uint8_t;
}}

#define GPIOA_BASE_ADDRESS             (PORTA)
#define PORTA                          (0x3B)
#define DDRA                           (0x3A)
#define PINA                           (0x39)
#define GPIOB_BASE_ADDRESS             (PORTB)
#define PORTB                          (0x38)
#define DDRB                           (0x37)
#define PINB                           (0x36)
#define GPIOC_BASE_ADDRESS             (PORTC)
#define PORTC                          (0x35)
#define DDRC                           (0x34)
#define PINC                           (0x33)
#define GPIOD_BASE_ADDRESS             (PORTD)
#define PORTD                          (0x32)
#define DDRD                           (0x31)
#define PIND                           (0x30)

#define ATMEGA32_PINS\
    X(Pin0)\
    X(Pin1)\
    X(Pin2)\
    X(Pin3)\
    X(Pin4)\
    X(Pin5)\
    X(Pin6)\
    X(Pin7)
#define ATMEGA32_PORTS\
    X(PortA)\
    X(PortB)\
    X(PortC)\
    X(PortD)

#endif // _ATMEGA32_H_
