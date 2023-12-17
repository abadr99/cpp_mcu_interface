#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Gpio.h"
#include "GpioDeviceInterface.h"

using namespace avr::types;
using namespace avr::mcal::gpio;
using namespace avr::hal::gpio;

template <Port TPort, Pin TPin>
static void SetOutputPin(Gpio<TPort>& gpio) {
    gpio.SetDirection<TPin,DirectionState::kOutput>();
}

template <Port TPort, Pin... TPins>
OutputDeviceInterface<TPort,TPins...>::OutputDeviceInterface() {
    SetOuputPin<TPort, Tpins>();
}

template <Port TPort, Pin... TPins>
template <Pin TPin, OutputMode M>
void OutputDeviceInterface<TPort,TPins...>::TurnOn() {

}

template <Port TPort, Pin... TPins>
template <Pin TPin, OutputMode M >
void OutputDeviceInterface<TPort,TPins...>::TurnOff() {

}
