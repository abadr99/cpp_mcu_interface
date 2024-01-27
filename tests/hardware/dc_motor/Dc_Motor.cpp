#include <stdint.h>
#include <util/delay.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../hal/inc/GpioDeviceInterface.h"
#include "../../../hal/inc/DcMotor.h"

#define MOVE_TIME       (3000)
using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;
using namespace avr::hal::dc_motor;
using DIR = DcMotor::Direction;

int main() {
    // Connect first dc to PA0 and PB0
    DcMotor dc1({kPortA, kPin0}, {kPortB, kPin0});

    // Connect second dc to PA1, PA2
    DcMotor dc2(kPortA, kPin1, kPin2);
    
    while (1) {
    
        // move forward
        dc1.Move<DIR::kClockWise>();
        dc2.Move<DIR::kClockWise>();
        _delay_ms(MOVE_TIME);

        // move backward
        dc1.Move<DIR::kCounterClockWise>();
        dc2.Move<DIR::kCounterClockWise>();
        _delay_ms(MOVE_TIME);

        // stop
        dc1.Stop();
        _delay_ms(MOVE_TIME);
    }

}
