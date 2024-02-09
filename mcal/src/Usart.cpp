#include <stdint.h>
#include "Helpers.h"
#include "Atmega32.h"
#include "Register.h"
#include "Usart.h"

#define READ_BIT(val_, bit_)        ((val_ & (1 << bit_)) >> bit_)
// ============================================================================
// --------------------------------- NAMESPACES -------------------------------
// ============================================================================
using namespace avr::mcal::usart;
Usart USART;

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

typename UsartRegisters::Register_t& UsartRegisters::GetUDR() { return udr_; }
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
typename UsartRegisters::Register_t& UsartRegisters::GetUCSRB() { return ucsrb_; } //IGNORE-STYLE-CHECK[L004]
typename UsartRegisters::Register_t& UsartRegisters::GetUBRRL() { return ubrrl_; } //IGNORE-STYLE-CHECK[L004]
typename UsartRegisters::Register_t& UsartRegisters::GetUCSRC() { return ucsrc_; } //IGNORE-STYLE-CHECK[L004]
typename UsartRegisters::Register_t& UsartRegisters::GetUBRRH() { return ubrrh_; } //IGNORE-STYLE-CHECK[L004]

// ============================================================================
// -------------------------------- USART ------------------------------------
// ============================================================================
Usart::Usart() : registers_(USART_BASE_ADDR), 
                 transmitterCallBack_(nullptr),
                 receiverCallBack_(nullptr),
                 tx_data_(0),
                 rx_data_(0),
                 config_(0x80)  // to select UCSRC
 { /* EMPTY */ }
void Usart::Reset() {
    registers_ = USART_BASE_ADDR;
    transmitterCallBack_ = nullptr;
    receiverCallBack_ = nullptr; 
    tx_data_ = 0;
    rx_data_ = 0;
    config_ = 0x80;
}

void Usart::Init(const UsartConfigurations& confg) {
    // For multiple initiate we should reset all data members values
    Reset();
    SetDataSize(confg.dataSize);
    SetParityMode(confg.parityMode);
    SetNumberOfStopBits(confg.stopBitsNumber);
    SelectTransferMode(confg.transferMode);
    SetBaudRate(confg.baudRate);
    SetTxRxMode(confg.tx_rx_mode);
    if (confg.transferMode == kSynchronous) {
        SetClockPolarity(confg.clkPolarity);
    }
    registers_.GetUCSRC().WriteRegister(config_);
}

void Usart::SetParityMode(ParityMode pm) {
    config_ |= pm << UCSRC::kUPM0;
}

void Usart::SetNumberOfStopBits(StopBits sp) {
    config_ |= sp << UCSRC::kUSBS;
}

void Usart::SetDataSize(DataSize ds) {
    registers_.GetUCSRB().WriteBits<UCSRB::kUCSZ2>(READ_BIT(ds, 2));
    config_ |= ((ds & 0x3) << UCSRC::kUCSZ0);
}

typename Usart::DataSize Usart::GetDataSize() {
    if (registers_.GetUCSRB().ReadBit<UCSRB::kUCSZ2>()) {
        return DataSize::kNineBits;
    }
    return static_cast<DataSize>((config_ >> UCSRC::kUCSZ0) & 0b11);
}

void Usart::SetClockPolarity(ClockPolarity cp) {
    config_ |= cp << UCSRC::kUCPOL;
}

typename Usart::ErrorType Usart::GetErrorType() {
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

void Usart::SelectTransferMode(TransferMode tm) {
    config_ |= (tm & 1) << UCSRC::kUMSEL;
    registers_.GetUCSRA().WriteBits<UCSRA::kU2X>(((tm & 2) >> 1) & 1);
}

typename Usart::TransferMode Usart::GetTransferMode() {
    if (READ_BIT(config_, UCSRC::kUMSEL)) {
        return TransferMode::kSynchronous;
    }
    if (registers_.GetUCSRA().ReadBit<UCSRC::kUMSEL>()) {
        return TransferMode::kAsynchronous_2x;
    }
    return TransferMode::kAsynchronous_1x;
}

void Usart::SetBaudRate(BaudRate_t baudRate) {

    auto Calculate_ubrr = [&](const uint8_t mode) -> uint32_t {
        return ((ATMEGA32_CLK) / (static_cast<float>(mode) * baudRate)) - 1; //IGNORE-STYLE-CHECK[L004]
    };
    uint32_t ubrr = 0;
    TransferMode mode = GetTransferMode();
    switch (mode) {
        case TransferMode::kAsynchronous_1x: ubrr = Calculate_ubrr(16); break;
        case TransferMode::kAsynchronous_2x: ubrr = Calculate_ubrr(8);  break;
        case TransferMode::kSynchronous:     ubrr = Calculate_ubrr(2);  break;
    }
    registers_.GetUBRRL().WriteRegister(static_cast<uint8_t>(ubrr));
    uint8_t ubbrh = utils::ExtractBits<uint16_t, 8, 11>(ubrr);
    registers_.GetUBRRH().WriteBits<0, 3>(ubbrh);
}

void Usart::SetTxRxMode(TX_RX_Mode mode) {
    registers_.GetUCSRB().WriteBits<UCSRB::kTXEN, UCSRB::kRXEN>(mode);
}

void Usart::WriteDataRegister(uint16_t data) {
    //  Check if we have more than one byte to transfer and according to specs:
    //  – TXB8 :Must be written before writing the low bits to UDR.
    if (GetDataSize() == DataSize::kNineBits) {
        registers_.GetUCSRB().WriteBits<UCSRB::kTXB8>(utils::ExtractBits<uint16_t, 8>(data)); //IGNORE-STYLE-CHECK[L004]
    }
    registers_.GetUDR().WriteRegister(data);
}

uint16_t Usart::ReadDataRegister() {
    uint16_t data = 0;
    if (GetDataSize() == DataSize::kNineBits) {
        data = registers_.GetUCSRB().ReadBit<UCSRB::kRXB8>();
    }
    return (data << 8) | registers_.GetUDR().ReadRegister();
}

void Usart::Send(uint16_t data) {
    // 1]  --- WAIT UNTIL TRANSMIT BUFFER BE EMPTY
    while (registers_.GetUCSRA().ReadBit<UCSRA::kUDRE>() == 0) { /* EMPTY */}
    // 2]  ---  WRITE DATA TO TRANSMIT BUFFER
    WriteDataRegister(data);
}

typename Usart::PFunction_t Usart::GetTransmitterCallBack() {
    return transmitterCallBack_;
}

typename Usart::PFunction_t Usart::GetReceiverCallBack() {
    return receiverCallBack_;
}

uint16_t Usart::GetTransmittedData() { return tx_data_; }

void Usart::SetReceivedData(uint16_t data) { rx_data_ = data; }

uint16_t Usart::GetReceivedData() { return rx_data_; }

// Instead of busy waiting in UDRE flag we can use UDRE-INTERRUPT to execute 
// ISR i.e. to send data.
void Usart::Send(uint16_t data, PFunction_t pFun) {
    // --- Set callback
    transmitterCallBack_ = pFun;
    // --- Set data
    tx_data_ = data;
    // --- Enable transmit complete interrupt 
    registers_.GetUCSRB().SetBit<UCSRB::kUDRIE>();
    // TODO(abadr99): --- Enable global interrupt
}

uint16_t Usart::Receive() {
    // WAIT FOR DATA UNTIL BE RECEIVED
    while (registers_.GetUCSRA().ReadBit<UCSRA::kRXC>() == 0) { /* EMPTY */}
    return ReadDataRegister();
}

uint16_t Usart::Receive(PFunction_t pFun) {
    // --- Set callback
    receiverCallBack_ = pFun;
    // --- Enable transmit complete interrupt 
    registers_.GetUCSRB().SetBit<UCSRB::kUDRIE>();
    // --- Enable global interrupt
    SEI();
    return rx_data_;
}

//  ---- USART, Rx Complete
ISR(USART_RXC)
{
    USART.SetReceivedData(USART.ReadDataRegister());
    if (USART.GetReceiverCallBack()) {
        USART.GetReceiverCallBack()();
    }
}

//  ----  USART Data Register Empty
ISR(USART_UDRE)
{
    USART.WriteDataRegister(USART.GetTransmittedData());
    if (USART.GetTransmitterCallBack()) {
        USART.GetTransmitterCallBack()();
    }
}

//  ----  USART, Tx Complete
ISR(USART_TXC)
{
    
}
