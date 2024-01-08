#include <stdint.h>
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
: udr_(baseAddr),       ucsra_(baseAddr - 1), 
  ucsrb_(baseAddr - 2), ubrrl_(baseAddr - 3),
  ucsrc_(UCSRC_REGISTER)
{ /* EMPTY */}

typename UsartRegisters::Register_t& UsartRegisters::GetUDR() {
    return udr_;
}
typename UsartRegisters::Register_t& UsartRegisters::GetUCSRA() {
    // According to specs:
    // Always set this bit to zero when writing to UCSRA {FE, DOR, PE}
    ucsra_.ClearBit<UCSRA::kFE>()
          .ClearBit<UCSRA::kDOR>()
          .ClearBit<UCSRA::kPE>();
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
    if (registers_.GetUCSRA().ReadBit<UCSRA::kFE>()) {
        return ErrorType::kFrameError;
    }
    if (registers_.GetUCSRA().ReadBit<UCSRA::kDOR>()) {
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
        case TM::kAsynchronous: registers_.GetUCSRC().ClearBit<UCSRC::kUMSEL>(); break; //IGNORE-STYLE-CHECK[L004]
        case TM::kSynchronous: registers_.GetUCSRC().SetBit<UCSRC::kUMSEL>(); break; //IGNORE-STYLE-CHECK[L004]
    }
}
