#ifndef _IR_H_
#define _IR_H_

namespace avr {
namespace hal {
namespace ir  {

enum IrState {
    kNotDetected,
    kDetected
};

template <avr::types::Port TPort, avr::types::Pin TPin>
class Ir : public avr::hal::gpio::OutputDeviceInterface<TPort>{
public:
    Ir();
    avr::hal::ir::IrState GetState();
private:
    avr::types::Pin IrPin_;
};
}}} // avr::hal::ir
#endif // _IR_H_
