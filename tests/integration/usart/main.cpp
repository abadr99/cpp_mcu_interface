/* 
 * make compile-test src=tests/integration/usart/main.cpp 
   target=tests/integration/usart/usart
 * sh scripts/testing/run-simu-avr.sh tests/integration/usart/usart.testelf
 * sh scripts/testing/run-regressions.sh -d tests/integration/usart/
*/

#include <stdint.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../mcal/inc/Usart.h"
 #include "../../../tests/impl/AVRTest.h"

using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;
using namespace avr::mcal::usart;

#define UDR                              (*((volatile uint8_t*)0x2C))
#define UCSRA                            (*((volatile uint8_t*)0x2B))
#define UCSRB                            (*((volatile uint8_t*)0x2A))
#define UCSRC                            (*((volatile uint8_t*)0x40))
#define UBBRL                            (*((volatile uint8_t*)0x29))
#define UBBRH                            (*((volatile uint8_t*)0x40))


int main () {
 {
    avr::test::AVRTest TESTER("RX/TX enable/disable test");

    uint8_t val=0;
    USART.Init();
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    Usart::UsartConfigurations fig;
    fig.tx_rx_mode= Usart::TX_RX_Mode::kDisableRX_DisableTX;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.tx_rx_mode= Usart::TX_RX_Mode::kDisableRX_EnableTX;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x08));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.tx_rx_mode= Usart::TX_RX_Mode::kEnableRX_DisableTX;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x10));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));
 }
 {
    avr::test::AVRTest TESTER("Data size test");

    uint8_t val=0;
    USART.Init();
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    Usart::UsartConfigurations fig;
    fig.dataSize=Usart::DataSize::kFiveBits;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.dataSize=Usart::DataSize::kSixBits;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x02));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.dataSize=Usart::DataSize::kSevenBits;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x04));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.dataSize=Usart::DataSize::kEightBits;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.dataSize=Usart::DataSize::kNineBits;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x1C));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

 }
 {
    avr::test::AVRTest TESTER("Stop bits/Pairty/Transfer bits test");

    uint8_t val=0;
    USART.Init();
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    Usart::UsartConfigurations fig;
    fig.parityMode=Usart::ParityMode::kEven;
    fig.dataSize=Usart::DataSize::kFiveBits;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.parityMode=Usart::ParityMode::kOdd;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x30));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.transferMode=Usart::TransferMode::kAsynchronous_2x;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x22));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x21));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.transferMode=Usart::TransferMode::kAsynchronous_1x;
    fig.stopBitsNumber=Usart::StopBits::kTwoBits;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x38));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.transferMode=Usart::TransferMode::kSynchronous;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x78));

    fig.clkPolarity=Usart::ClockPolarity::kTxFalling_RxRising;
    USART.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x79));
 }
 {
    avr::test::AVRTest TESTER("Baudrate test");

    uint8_t val=0;
    Usart::UsartConfigurations fig;
    Usart Usart_;
    Usart_.Init();
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x33));

    fig.baudRate=600;
    Usart_.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x03));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x40));

    fig.baudRate=115200;
    Usart_.Init(fig);
    TESTER.Expect_Eq(UDR,   static_cast<uint8_t>(0x00));
    TESTER.Expect_Eq(UCSRA, static_cast<uint8_t>(0x20));
    TESTER.Expect_Eq(UCSRB, static_cast<uint8_t>(0x18));
    TESTER.Expect_Eq(UBBRH, static_cast<uint8_t>(0x00));
    val=UCSRC;
    val=UCSRC;
    TESTER.Expect_Eq(val, static_cast<uint8_t>(0x06));
    TESTER.Expect_Eq(UBBRL, static_cast<uint8_t>(0x03));
 }
 }
