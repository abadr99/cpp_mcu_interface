#ifndef _SEVEN_SEGMENT_H_H
#define _SEVEN_SEGMENT_H_H

namespace avr {
namespace hal {
namespace seven_segment {

enum SevenSegmentType {kCommonAnode, kCommonCathode};

// Assumed all 7Segment pins are connected to the same port (except for dot)
// TODO(@abadr99): Support different ports if needed
template<SevenSegmentType Type>
class SevenSegment: public avr::hal::gpio::OutputDeviceInterface {
public:
    // These values are selected assuming:
    // 'abcdefg' connection
    enum SevenSegmentNumbers : uint8_t {
        kZero  = 0x7E, kOne   = 0x30, kTwo   = 0x6D, kThree = 0x79, 
        kFour  = 0x33, kFive  = 0x5B, kSix   = 0x5F, kSeven = 0x70, 
        kEight = 0x7F, kNine  = 0x7B, kError = 0x4F,
    };
    using size = uint8_t; 
    using Port = avr::types::Port;
    using Pin = avr::types::Pin;
    using DevicePin = utils::types::DevicePin;
    SevenSegment(Port port, 
                 Pin pin_a, Pin pin_b, Pin pin_c, Pin pin_d, Pin pin_e,
                 Pin pin_f, Pin pin_g,
                 bool isDot = false, 
                 DevicePin dotPin = {Port::kPortNotConnected, 
                                     Pin::kPinNotConnected});
    void Display(size num);
    void TurnOnDot();
    void TurnOffDot();
private:
    Port port_;
    Pin pins_[7];
    bool isDot_;
    DevicePin dotPin_;
    void TurnOff();
};

}}} // namespace avr::hal::seven_segment
#endif // _SEVEN_SEGMENT_H_H
