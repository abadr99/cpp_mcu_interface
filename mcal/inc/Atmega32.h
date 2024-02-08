#ifndef _ATMEGA32_H_
#define _ATMEGA32_H_

namespace avr{
namespace types{

enum Port : uint8_t {
    kPortA,
    kPortB,
    kPortC,
    kPortD,
    kPortNotConnected,
};

enum Pin : uint8_t {
    kPin0, kPin1, kPin2, kPin3,
    kPin4, kPin5, kPin6, kPin7,
    kPinNotConnected,
};
using AvrRegWidth  = uint8_t;
}} // namespace avr::types

namespace avr {
namespace errors {

inline void ERROR() {
    // TODO(@abadr99): Handle error
}

inline void ERROR(const char* msg) {
    // TODO(@abadr99): Handle error
}
}} // namespace avr::utils

// Set enable interrupt
#define SEI() asm volatile ("sei" ::: "memory");

#define INT0                            (1)
#define INT1                            (2)
#define INT2                            (3)
#define TIMER2_COMP                     (4)
#define TIMER2_OVF                      (5)
#define TIMER1_CAPT                     (6)
#define TIMER1_COMPA                    (7)
#define TIMER1_COMPB                    (8)
#define TIMER1_OVF                      (9)
#define TIMER0_COMP                     (10)
#define TIMER0_OVF                      (11)
#define SPI_STC                         (12)
#define USART_RXC                       (13)
#define USART_UDRE                      (14)
#define USART_TXC                       (15)
#define ADC_CONVERSION                  (16)
#define EE_RDY                          (17)
#define ANA_COMP                        (18)
#define TWI                             (19)
#define SPM_RDY                         (20)

#define ISR(vec_)\
 extern "C"\
 void __vector_##vec_(void) __attribute__((signal, used, externally_visible));\
 void __vector_##vec_(void)

#define ATMEGA32_CLK                   (8000000)
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
