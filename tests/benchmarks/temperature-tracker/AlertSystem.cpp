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


AlertSystem::AlertSystem() : dc(DC_MOTOR_PORT, DC_MOTOR1_PIN, DC_MOTOR2_PIN),
                             alert_led({LED_PORT, LED_PIN}),
                             temp_sensor(LM35_PIN)

{ 
    ADC.Init();
}

bool AlertSystem::IsTemperatureExceed() {
    return temp_sensor.GetTemperature() > 50;
}

void AlertSystem::TurnOnFireSystem() {
    dc.Move<DIR::kClockWise>();
    alert_led.Toggle();
    _delay_ms(250);
}

void AlertSystem::TurnOffFireSystem() {
    dc.Stop();
    alert_led.TurnOff();
}

