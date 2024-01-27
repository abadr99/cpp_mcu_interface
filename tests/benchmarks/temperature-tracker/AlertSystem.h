#ifndef _ALERT_SYSTEM_H_H
#define _ALERT_SYSTEM_H_H

// ============================================================================
#define DC_MOTOR_PORT       (avr::types::Port::kPortB)
#define DC_MOTOR1_PIN       (avr::types::Pin::kPin0)
#define DC_MOTOR2_PIN       (avr::types::Pin::kPin1)
#define LM35_PIN            (avr::types::Pin::kPin2)
#define LED_PORT            (avr::types::Port::kPortB)
#define LED_PIN             (avr::types::Pin::kPin3)
// ============================================================================

class AlertSystem {
public:
    using DIR = avr::hal::dc_motor::DcMotor::Direction;
    AlertSystem();
    bool IsTemperatureExceed();
    void TurnOnFireSystem();
    void TurnOffFireSystem();
private:
    avr::hal::dc_motor::DcMotor dc;
    avr::hal::led::Led<avr::hal::led::OutputMode::kActiveHigh> alert_led;
    avr::hal::temperature_sensor::Lm35 temp_sensor;
};

#endif // _ALERT_SYSTEM_H_H
