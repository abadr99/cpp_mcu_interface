#ifndef _IR_H_
#define _IR_H_

namespace avr {
namespace hal {
namespace ir  {

class Ir : public avr::hal::gpio::InputDeviceInterface{
public:
    enum IrState { kNotDetected, kDetected };
    using DevicePin = utils::types::DevicePin;
    using Port = avr::types::Port;
    using Pin = avr::types::Pin;
    using IRState = avr::hal::ir::Ir::IrState;
    Ir(DevicePin dp);
    IRState GetState();
private:
    DevicePin IrPin_;
};
}}} // avr::hal::ir
#endif // _IR_H_
