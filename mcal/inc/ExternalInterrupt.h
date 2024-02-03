#ifndef _EXTERNAL_INTERRUPT_H_
#define _EXTERNAL_INTERRUPT_H_

namespace avr {
namespace mcal {
namespace external_interrupt {

using pFun = void(*)();

enum InterruptSource {
    kInterrupt0, kInterrupt1, kInterrupt2,
};

// --- ORDER MATTERS
enum InterruptMode {
    kLow, 
    kChange, 
    kFalling,
    kRising,
};

void SetInterrupt(InterruptSource interrupt, InterruptMode mode, pFun callback);

}}} // namespace avr::mcal::external_interrupt
#endif // _EXTERNAL_INTERRUPT_H_
