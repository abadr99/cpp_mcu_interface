#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Helpers.h"
#include "Gpio.h"
#include "GpioDeviceInterface.h"
#include "DcMotor.h"

using namespace avr::hal::dc_motor;

DcMotor::DcMotor(Port port, Pin pin1, Pin pin2) 
: m1_({.port = port, .pin = pin1}), m2_({.port = port, .pin = pin2})
{
    this->Init(m1_)
         .Init(m2_);
    Stop();
}
DcMotor::DcMotor(DevicePin dp1, DevicePin dp2)
: m1_(dp1), m2_(dp2)
{
    this->Init(m1_)
         .Init(m2_);
    Stop();
}

template <DcMotor::Direction D>
void DcMotor::Move() {
    using DIR = DcMotor::Direction;
    switch (D) {
        case DIR::kClockWise:
            SetHighVoltage(m1_);
            SetLowVoltage(m2_);
            break;
        case DIR::kCounterClockWise:
            SetLowVoltage(m1_);
            SetHighVoltage(m2_);
            break;
    }
}
template void DcMotor::Move<DcMotor::Direction::kClockWise>();
template void DcMotor::Move<DcMotor::Direction::kCounterClockWise>();

void DcMotor::Stop() {
    SetLowVoltage(m1_);
    SetLowVoltage(m2_);
}
