#ifndef _DC_MOTOR_H_H
#define _DC_MOTOR_H_H

namespace avr {
namespace hal {
namespace dc_motor {

class DcMotor : public avr::hal::gpio::OutputDeviceInterface {
public:
    enum Direction {kClockWise, kCounterClockWise};
    using Port      = avr::types::Port;
    using Pin       = avr::types::Pin;
    using DevicePin = utils::types::DevicePin;
    // Connected to the same port
    DcMotor(Port port, Pin pin1, Pin pin2);
    // Connected to different ports
    DcMotor(DevicePin dp1, DevicePin dp2);
    template <Direction D>
    void Move();
    void Stop();
private:
    DevicePin m1_;
    DevicePin m2_;
};
}}} // namespace avr::hal::dc_motor

#endif // _DC_MOTOR_H_H
