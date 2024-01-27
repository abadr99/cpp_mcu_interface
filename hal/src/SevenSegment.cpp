#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "Helpers.h"
#include "Gpio.h"
#include "GpioDeviceInterface.h"
#include "SevenSegment.h"

using namespace avr::hal::seven_segment;

#define SEVEN_SEG_PINS  {pins_.a, pins_.b, pins_.c, pins_.d, pins_.e, pins_.f, pins_.g} //IGNORE-STYLE-CHECK[L004]
template<SevenSegmentType Type>
SevenSegment<Type>::SevenSegment(Port port, 
                                 Pin pin_a,
                                 Pin pin_b,
                                 Pin pin_c,
                                 Pin pin_d,
                                 Pin pin_e,
                                 Pin pin_f,
                                 Pin pin_g,
                                 bool isDot, 
                                 DevicePin dotPin)
: port_(port),
  pins_{pin_g, pin_f, pin_e, pin_d, pin_c, pin_b, pin_a},
  isDot_(isDot),
  dotPin_(dotPin)
{
    for (uint8_t i = 0 ; i < 7; ++i) {
        this->Init({port_, pins_[i]});
    }
    if (isDot_) {
        this->Init(dotPin_);
    }
    TurnOff();
}

template<SevenSegmentType Type>
void SevenSegment<Type>::Display(size num) {
    using DL = avr::mcal::gpio::Gpio::DigitalLevel;
    using SSN = SevenSegmentNumbers;
    auto WritePins = [&](size val)->void {
        for (uint8_t i = 0 ; i < 7 ; ++i) {
            SetVoltage({port_, pins_[0]}, static_cast<DL>(READ_BIT(val, i)));
        }
    };

    if (Type == SevenSegmentType::kCommonCathode) {
        switch (num) {
            case 0:   WritePins(SSN::kZero);    return;
            case 1:   WritePins(SSN::kOne);     return;
            case 2:   WritePins(SSN::kTwo);     return;
            case 3:   WritePins(SSN::kThree);   return;
            case 4:   WritePins(SSN::kFour);    return;
            case 5:   WritePins(SSN::kFive);    return;
            case 6:   WritePins(SSN::kSix);     return;
            case 7:   WritePins(SSN::kSeven);   return;
            case 8:   WritePins(SSN::kEight);   return;
            case 9:   WritePins(SSN::kNine);    return;
            default:  WritePins(SSN::kError);   return;
        }
    }
    switch (num) {
        case 0:   WritePins(~SSN::kZero);    return;
        case 1:   WritePins(~SSN::kOne);     return;
        case 2:   WritePins(~SSN::kTwo);     return;
        case 3:   WritePins(~SSN::kThree);   return;
        case 4:   WritePins(~SSN::kFour);    return;
        case 5:   WritePins(~SSN::kFive);    return;
        case 6:   WritePins(~SSN::kSix);     return;
        case 7:   WritePins(~SSN::kSeven);   return;
        case 8:   WritePins(~SSN::kEight);   return;
        case 9:   WritePins(~SSN::kNine);    return;
        default:  WritePins(~SSN::kError);   return;
    }
}

template<SevenSegmentType Type>
void SevenSegment<Type>::TurnOnDot() {
    if (isDot_ == false) {
        return;  // EARLY EXIT
    }
    if (Type == SevenSegmentType::kCommonCathode) {
        SetLowVoltage(dotPin_);
        return;
    }
    SetHighVoltage(dotPin_);
}

template<SevenSegmentType Type>
void SevenSegment<Type>::TurnOffDot() {
    if (isDot_ == false) {
        return;  // EARLY EXIT
    }
    if (Type == SevenSegmentType::kCommonCathode) {
        SetHighVoltage(dotPin_);
        return;
    }
    SetLowVoltage(dotPin_);
}

template<SevenSegmentType Type>
void SevenSegment<Type>::TurnOff() {
    if (Type == SevenSegmentType::kCommonCathode) {
        // Turn off segment pins
        for (uint8_t i = 0 ; i < 7; ++i) {
            SetLowVoltage({port_, pins_[i]});
        }
    } 
    else {
        for (uint8_t i = 0 ; i < 7; ++i) {
            SetHighVoltage({port_, pins_[i]});
        }
    }
    // turn of dot
    TurnOffDot();
}


template class SevenSegment<SevenSegmentType::kCommonCathode>;
template class SevenSegment<SevenSegmentType::kCommonAnode>;
