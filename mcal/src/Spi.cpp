#include <stdint.h>
#include "Helpers.h"
#include "Atmega32.h"
#include "Register.h"
#include "Spi.h"

#define READ_BIT(val_, bit_)        ((val_ & (1 << bit_)) >> bit_)
// ============================================================================
// --------------------------------- NAMESPACES -------------------------------
// ============================================================================
using namespace avr::mcal::spi;
Spi SPI;

// ============================================================================
// ---------------------------- SPI-REGISTES-IMPL ---------------------------
// ============================================================================
SpiRegisters::SpiRegisters(avr::types::AvrRegWidth baseAddr) 
: spdr_(baseAddr), 
  spsr_(baseAddr - 1), 
  spcr_(baseAddr - 2)
  { /* EMPTY */}

typename SpiRegisters::Register_t& SpiRegisters::GetSPDR() { return spdr_; }
typename SpiRegisters::Register_t& SpiRegisters::GetSPCR() { return spcr_; }
typename SpiRegisters::Register_t& SpiRegisters::GetSPSR() { return spsr_; } //IGNORE-STYLE-CHECK[L004]

// ============================================================================
// -------------------------------- SPI ------------------------------------
// ============================================================================
Spi::Spi() :     registers_(SPI_BASE_ADDR), 
                 transceive_callback_(nullptr),
                 spdr_data_(0)
 { /* EMPTY */ }

 void Spi::Reset() {
    registers_ = SPI_BASE_ADDR;
    transceive_callback_ = nullptr;
    spdr_data_=0;
}


void Spi::Init(const SpiConfigurations& confg) {
    // For multiple initiate we should reset all data members values
    Reset();
    SetFrequencyMode(confg.frequency_mode);
    SetDataOrder(confg.data_order);
    SetSpiMode(confg.spi_mode);
    SetClockPolarity(confg.clk_polarity);
    SetClockPhase(confg.clk_phase);
    registers_.GetSPCR().SetBit<SPCR::KSPE>();
}

void Spi::SetFrequencyMode(FreqMode fm) {
    registers_.GetSPCR().WriteBits<SPCR::KSPR0, SPCR::KSPR1>(fm);
    if (fm==kf2 || fm==kf8 || fm==kf32 || fm==kf64x2)
    { registers_.GetSPSR().SetBit<SPSR::KSPI2X>(); }
}

void Spi::SetDataOrder(DataOrder d) {
    if (d==kLsb)
    { registers_.GetSPCR().SetBit<SPCR::KDORD>(); }
    else
    { registers_.GetSPCR().ClearBit<SPCR::KDORD>(); }
}
void Spi::SetSpiMode(MasterSlaveSel ms) {
    if (ms==kMaster)
    { registers_.GetSPCR().SetBit<SPCR::KMSTR>(); }
    else
    { registers_.GetSPCR().ClearBit<SPCR::KMSTR>(); }
}
void Spi::SetClockPolarity(ClockPolarity cp) {
    if (cp==kTrailingRising)
    { registers_.GetSPCR().SetBit<SPCR::KCPOL>(); }
    else
    { registers_.GetSPCR().ClearBit<SPCR::KCPOL>(); }
}

void Spi::SetClockPhase(ClockPhase cph) {
    if (cph==kTrailingSampleLeadingSetup)
    { registers_.GetSPCR().SetBit<SPCR::KCPHA>(); }
    else
    { registers_.GetSPCR().ClearBit<SPCR::KCPHA>(); }
}
uint8_t Spi::Transceive(uint8_t data) {
    spdr_data_=data;
    while (registers_.GetSPSR().ReadBit<SPSR::KSPIF>() == 0) {/*emtpy*/};
    registers_.GetSPSR().SetBit<SPSR::KSPIF>();
    spdr_data_=registers_.GetSPDR().ReadRegister();
    return spdr_data_;
}
uint8_t Spi::Transceive(uint8_t data, PFunction_t pFun) {
    //  Set callback
    transceive_callback_ = pFun;
    //  Set data
    spdr_data_ = data;
    //  Enable transceive  interrupt 
    registers_.GetSPCR().SetBit<SPCR::KSPIE>();
    return spdr_data_;
}
void Spi::Spi::Transmit(uint8_t data) {
    spdr_data_=data;
    while (registers_.GetSPSR().ReadBit<SPSR::KSPIF>() == 0) {/*empty*/};
}
uint8_t Spi::Receive() {
    while (registers_.GetSPSR().ReadBit<SPSR::KSPIF>() == 0) {/*empty*/};
    spdr_data_=registers_.GetSPDR().ReadRegister();
    return spdr_data_;
}
void Spi::SetReceivedData(uint8_t data) { 
    spdr_data_ = data;
     }
uint8_t Spi::GetDataReg() {
    return registers_.GetSPDR().ReadRegister();
}
typename Spi::PFunction_t Spi::GetTransceiveCallBack() {
    return transceive_callback_;
}
ISR(12)
{
    SPI.SetReceivedData(SPI.GetDataReg());
    if (SPI.GetTransceiveCallBack()) {
        SPI.GetTransceiveCallBack()();
    }
}
