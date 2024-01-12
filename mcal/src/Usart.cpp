#include <stdint.h>
#include "Helpers.h"
#include "Atmega32.h"
#include "Register.h"
#include "Usart.h"

// ============================================================================
// --------------------------------- NAMESPACES -------------------------------
// ============================================================================

using namespace avr::mcal::usart;

// ============================================================================
// ---------------------------- USART-REGISTES-IMPL ---------------------------
// ============================================================================

UsartRegisters::UsartRegisters(avr::types::AvrRegWidth baseAddr) 
: udr_(baseAddr), 
  ucsra_(baseAddr - 1), 
  ucsrb_(baseAddr - 2), 
  ubrrl_(baseAddr - 3), 
  ubrrh_(UCSRH_REGISTER),
  ucsrc_(UCSRC_REGISTER)
{ /* EMPTY */}

typename UsartRegisters::Register_t& UsartRegisters::GetUDR() {
    return udr_;
}
typename UsartRegisters::Register_t& UsartRegisters::GetUCSRA(bool isWrite) {
    // According to specs:
    // Always set this bit to zero when writing to UCSRA {FE, DOR, PE}
    if (isWrite) {
        ucsra_.ClearBit<UCSRA::kFE>()
              .ClearBit<UCSRA::kDOR>()
              .ClearBit<UCSRA::kPE>();
    }
    return ucsra_;
}
typename UsartRegisters::Register_t& UsartRegisters::GetUCSRB() {
    return ucsrb_;
}
typename UsartRegisters::Register_t& UsartRegisters::GetUBRRL() {
    return ubrrl_;
}
typename UsartRegisters::Register_t& UsartRegisters::GetUCSRC() {
    // if we use this function this mean we are going to modify 
    // this register. According to specs:
    // The URSEL must be one when writing the UCSRC.
    ucsrc_.SetBit<UCSRC::kURSEL>();
    return ucsrc_;
}
typename UsartRegisters::Register_t& UsartRegisters::GetUBRRH() {
    // if we use this function this mean we are going to modify 
    // this register. According to specs:
    // The URSEL must be one when writing the UCSRC.
    ubrrh_.ClearBit<UCSRC::kURSEL>();
    return ubrrh_;
}
// ============================================================================
// -------------------------------- USART ------------------------------------
// ============================================================================

Usart::Usart() : registers_(USART_BASE_ADDR) { /* EMPTY */}

template <ParityMode M>
void Usart::SetParityMode() {
    registers_.GetUCSRC().WriteWithMask<Mask::kParityMode, UCSRC::kUPM0, M>(); 
}

template <StopBits N>
void Usart::SetNumberOfStopBits() {
    using SB = StopBits;
    switch (N) {
        case SB::kOneBit : registers_.GetUCSRC().ClearBit<UCSRC::kUSBS>(); break; //IGNORE-STYLE-CHECK[L004]
        case SB::kTwoBits: registers_.GetUCSRC().SetBit<UCSRC::kUSBS>();   break; //IGNORE-STYLE-CHECK[L004]
    }
}

template <DataSize S>
void Usart::SetDataSize() {
    using DZ = DataSize;
    switch (S) {
        case DZ::kFiveBits:
            registers_.GetUCSRC().ClearBit<UCSRC::kUCSZ1>().ClearBit<UCSRC::kUCSZ0>(); //IGNORE-STYLE-CHECK[L004]
            registers_.GetUCSRB().ClearBit<UCSRB::kUCSZ2>();
            break;
        case DZ::kSixBits:
            registers_.GetUCSRC().ClearBit<UCSRC::kUCSZ1>().SetBit<UCSRC::kUCSZ0>(); //IGNORE-STYLE-CHECK[L004]
            registers_.GetUCSRB().ClearBit<UCSRB::kUCSZ2>();
            break;
        case DZ::kSevenBits:
            registers_.GetUCSRC().SetBit<UCSRC::kUCSZ1>().ClearBit<UCSRC::kUCSZ0>(); //IGNORE-STYLE-CHECK[L004]
            registers_.GetUCSRB().ClearBit<UCSRB::kUCSZ2>();
            break;
        case DZ::kEightBits:
            registers_.GetUCSRC().SetBit<UCSRC::kUCSZ1>().SetBit<UCSRC::kUCSZ0>(); //IGNORE-STYLE-CHECK[L004]
            registers_.GetUCSRB().ClearBit<UCSRB::kUCSZ2>();
            break;
        case DZ::kNineBits:
            registers_.GetUCSRC().SetBit<UCSRC::kUCSZ1>().SetBit<UCSRC::kUCSZ0>(); //IGNORE-STYLE-CHECK[L004]
            registers_.GetUCSRB().SetBit<UCSRB::kUCSZ2>();
            break;
    }
}

template<ClockPolarity P>
void Usart::SetClockPolarity() {
    using CP = ClockPolarity;
    switch (P) {
        case CP::kTxFalling_RxRising : 
            registers_.GetUCSRC().ClearBit<UCSRC::kUCPOL>();
            break;
        case CP::kTxRising_RxFalling:
            registers_.GetUCSRC().SetBit<UCSRC::kUCPOL>();
            break;
    }
}

template<ErrorType E>
void Usart::GetErrorType() {
    // TODO(@abadr99): Check what is the best order for errors?
    if (registers_.GetUCSRA(false).ReadBit<UCSRA::kFE>()) {
        return ErrorType::kFrameError;
    }
    if (registers_.GetUCSRA(false).ReadBit<UCSRA::kDOR>()) {
        return ErrorType::kDataOverRun;
    }
    if (registers_.GetUCSRC().ReadBits<UCSRC::kUPM0, UCSRC::kUPM1>() > 1) {
        if (registers_.GetUCSRA().ReadBit<UCSRA::kPE>()) {
            return ErrorType::kParityError;
        }
    }
    return ErrorType::kSuccess;
}

template<TransferMode M>
void Usart::SelectTransferMode() {
    using TM = TransferMode;
    switch (M) {
        case TM::kAsynchronous_1x: 
            registers_.GetUCSRC().ClearBit<UCSRC::kUMSEL>();
            registers_.GetUCSRA().ClearBit<UCSRA::kU2X>(); 
            break;
        case TM::kAsynchronous_2x:
            registers_.GetUCSRC().ClearBit<UCSRC::kUMSEL>();
            registers_.GetUCSRA().SetBit<UCSRA::kU2X>(); 
            break;
        case TM::kSynchronous:
            registers_.GetUCSRC().SetBit<UCSRC::kUMSEL>();
            registers_.GetUCSRA().ClearBit<UCSRA::kU2X>(); 
            break;
    }
}

TransferMode Usart::GetTransferMode() {
    using TM = TransferMode;
    if (registers_.GetUCSRC().ReadBit<UCSRC::kUMSEL>()) {
        return TM::kSynchronous;
    }
    if (registers_.GetUCSRA().ReadBit<UCSRC::kUMSEL>()) {
        return TM::kAsynchronous_2x;
    }
    return TM::kAsynchronous_1x;
}

template <Usart::BaudRate_t BR>
void Usart::SetBaudRate() {
    using TM = TransferMode;
    constexpr auto Calculate_ubrr = [&](const uint8_t mode) -> uint32_t 
                        {
                          return ((ATMEGA32_CLK) / (static_cast<float>(mode) * BR)) - 1; //IGNORE-STYLE-CHECK[L004]
                        };
    uint32_t ubrr = 0;
    TransferMode mode = GetTransferMode();
    switch (mode) {
        case TM::kAsynchronous_1x: ubrr = Calculate_ubrr(16); break;
        case TM::kAsynchronous_2x: ubrr = Calculate_ubrr(8);  break;
        case TM::kSynchronous:     ubrr = Calculate_ubrr(2);  break;
    }
    registers_.GetUBRRL().WriteRegister(static_cast<uint8_t>(ubrr));
    uint8_t ubbrh = utils::ExtractBits<uint16_t, 8, 11>(ubrr);
    registers_.GetUBRRH().template WriteRegister<Mask::kHighDataBits, 8>(ubbrh);
}

template <TX_RX_Mode M>
void Usart::SetTxRxMode() {
    registers_.GetUCSRB().WriteWithMask<Mask::kTxRx, UCSRB::kTXEN, M>();
}

template<typename T>
void Usart::Send(T data) {
    // 1]  --- WAIT UNTIL TRANSMIT BUFFER BE EMPTY
    while (registers_.GetUCSRA().ReadBit<UCSRA::kUDRE>() == 0) { /* EMPTY */}
    // 2]  ---  WRITE DATA TO TRANSMIT BUFFER
    //  Check if we have more that one byte to transfer and according to specs:
    //  – TXB8 :Must be written before writing the low bits to UDR.
    if (sizeof(T) > 1) {
        registers_.GetUCSRB()
                  .template WriteRegister<Mask::kTxB8, UCSRB::kTXB8>(utils::ExtractBits<8>(data)); //IGNORE-STYLE-CHECK[L004]
    }
    registers_.GetUDR().WriteRegister(data);
}

template<typename T>
T Usart::Receive() {

}
