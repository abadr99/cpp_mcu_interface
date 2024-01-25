// 
#include <stdint.h>
#include <util/delay.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../hal/inc/GpioDeviceInterface.h"
#include "../../../hal/inc/SevenSegment.h"


using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::hal::seven_segment;
using namespace avr::types;

#define SEVEN_SEG_PORT      (kPortA)
#define SEVEN_SEG_PINA      (kPin0)
#define SEVEN_SEG_PINB      (kPin1)
#define SEVEN_SEG_PINC      (kPin2)
#define SEVEN_SEG_PIND      (kPin3)
#define SEVEN_SEG_PINE      (kPin4)
#define SEVEN_SEG_PINF      (kPin5)
#define SEVEN_SEG_PING      (kPin6)


int main() {
    SevenSegment<kCommonCathode> _7Seg(SEVEN_SEG_PORT,
                                       SEVEN_SEG_PINA,
                                       SEVEN_SEG_PINB,
                                       SEVEN_SEG_PINC,
                                       SEVEN_SEG_PIND,
                                       SEVEN_SEG_PINE,
                                       SEVEN_SEG_PINF,
                                       SEVEN_SEG_PING);
    while (1) {
        for (int i = 0; i < 10; ++i) {
            _7Seg.Display(i);
            _delay_ms(300);
        }
    }
}
