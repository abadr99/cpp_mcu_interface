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
    kNotConnected,
};
using AvrRegWidth  = uint8_t;
}}

#define ATMEGA32_CLK                   (8000000)
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
#define SFIOR                          (0x50)
#define ATMEGA32_PINS\
    X(Pin0)\
    X(Pin1)\
    X(Pin2)\
    X(Pin3)\
    X(Pin4)\
    X(Pin5)\
    X(Pin6)\
    X(Pin7)

#define ATMEGA32_PINS_VALUE\
    X(Pin0, 0)\
    X(Pin1, 1)\
    X(Pin2, 2)\
    X(Pin3, 3)\
    X(Pin4, 4)\
    X(Pin5, 5)\
    X(Pin6, 6)\
    X(Pin7, 7)

#define ATMEGA32_PORTS\
    X(PortA)\
    X(PortB)\
    X(PortC)\
    X(PortD)

#define ATMEGA32_PORT_PIN\
    X(PortA, Pin0)\
    X(PortA, Pin1)\
    X(PortA, Pin2)\
    X(PortA, Pin3)\
    X(PortA, Pin4)\
    X(PortA, Pin5)\
    X(PortA, Pin6)\
    X(PortA, Pin7)\
    X(PortB, Pin0)\
    X(PortB, Pin1)\
    X(PortB, Pin2)\
    X(PortB, Pin3)\
    X(PortB, Pin4)\
    X(PortB, Pin5)\
    X(PortB, Pin6)\
    X(PortB, Pin7)\
    X(PortC, Pin0)\
    X(PortC, Pin1)\
    X(PortC, Pin2)\
    X(PortC, Pin3)\
    X(PortC, Pin4)\
    X(PortC, Pin5)\
    X(PortC, Pin6)\
    X(PortC, Pin7)\
    X(PortD, Pin0)\
    X(PortD, Pin1)\
    X(PortD, Pin2)\
    X(PortD, Pin3)\
    X(PortD, Pin4)\
    X(PortD, Pin5)\
    X(PortD, Pin6)\
    X(PortD, Pin7)

#endif // _ATMEGA32_H_
