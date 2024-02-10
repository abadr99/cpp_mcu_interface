#include <stdint.h>
#include "Atmega32.h"
#include "Register.h"
#include "ExternalInterrupt.h"

#define MCUCR_REG    (0x55)
#define MCUCSR_REG   (0x54)
#define GICR_REG     (0x5B)

using namespace avr::mcal::external_interrupt;
using namespace utils;
using namespace avr::errors;
using namespace avr::types;
namespace EXTI=avr::mcal::external_interrupt;

static volatile pFun ExternalInterruptCallBacks[3];

struct ExternalInterruptRegisters {
    Register<AvrRegWidth> mcucr;
    Register<AvrRegWidth> mcucsr;
    Register<AvrRegWidth> gicr;
    ExternalInterruptRegisters(): mcucr(MCUCR_REG),
                                  mcucsr(MCUCSR_REG),
                                  gicr(GICR_REG) 
    { /* EMPTY */}
    enum MCUCR  {kISC00, kISC01, kISC10, kISC11};
    enum MCUCSR {kISC2 = 6};
    enum GICR   {kINT2=5, kINT0, kINT1};
};

void EXTI::SetInterrupt(InterruptSource interrupt,
 InterruptMode mode, pFun callback)
{
    using EIR = ExternalInterruptRegisters;
    EIR reg;
    // --- ENABLE GLOBAL INTERRUPT 
    SEI();
    // --- ENABLE EXTERNAL INTERRUPT AND MODE
    switch (interrupt) {
        case kInterrupt0: 
            reg.gicr.SetBit<EIR::GICR::kINT0>();
            reg.mcucr.WriteBits<EIR::MCUCR::kISC00, EIR::MCUCR::kISC01>(mode);
            break;
        case kInterrupt1:
            reg.gicr.SetBit<EIR::GICR::kINT1>();
            reg.mcucr.WriteBits<EIR::MCUCR::kISC10, EIR::MCUCR::kISC11>(mode);
            break;
        case kInterrupt2: 
            reg.gicr.SetBit<EIR::GICR::kINT2>(); 
            switch (mode) {
                case kFalling: reg.mcucsr.ClearBit<EIR::MCUCSR::kISC2>(); break;
                case kRising:  reg.mcucsr.SetBit<EIR::MCUCSR::kISC2>(); break;
                default: ERROR("[EXTI]: INT2 is supporting falling and rising only"); //IGNORE-STYLE-CHECK[L004]
            }
            break;
    }
    // --- SET CALLBACK
    ExternalInterruptCallBacks[interrupt] = callback;
}

ISR(1) {
    if (ExternalInterruptCallBacks[0]) {
        ExternalInterruptCallBacks[0]();
    }
}

ISR(2) {
    if (ExternalInterruptCallBacks[1]) {
        ExternalInterruptCallBacks[1]();
    }
}

ISR(3) {
    if (ExternalInterruptCallBacks[2]) {
        ExternalInterruptCallBacks[2]();
    }
}
