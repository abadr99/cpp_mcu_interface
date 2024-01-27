#include <stdint.h>
#include <util/delay.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Helpers.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../mcal/inc/Adc.h"
#include "../../../hal/inc/AdcDeviceInterface.h"
#include "../../../hal/inc/Lm35.h"
#include "../../../hal/inc/GpioDeviceInterface.h"
#include "../../../hal/inc/Led.h"
#include "../../../hal/inc/DcMotor.h"
#include "AlertSystem.h"

int main () {
    AlertSystem AS;
    while (1) {
        if (AS.IsTemperatureExceed()) {
            AS.TurnOnFireSystem();
        }
        else {
            AS.TurnOffFireSystem();
        }
    }
}
