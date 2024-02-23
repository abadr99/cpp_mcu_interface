#ifndef _SPI_H_H
#define _SPI_H_H

#define SPCR_REGISTER               (0x2D)
#define SPSR_REGISTER               (0x2E)
#define SPI_BASE_ADDR               (0x2F)


#define SPI_SCK_FREQ_MODE\
    X(f4,      0b00)\
    X(f16,     0b01)\
    X(f64,     0b10)\
    X(f128,    0b11)\
    X(f2,      0b00)\
    X(f8,      0b01)\
    X(f32,     0b10)\
    X(f64x2,     0b11)

#define SPI_DATA_ORDER\
    X(Msb,  0)\
    X(Lsb,  1)


#define SPI_MASTER_SLAVE_SEL\
    X(Slave,  0)\
    X(Master, 1)

#define SPI_CPOL\
    X(LeadingRising, 0)\
    X(TrailingRising, 1)

#define SPI_CLK_PHASE\
    X(LeadingSampleTrailingSetup, 0)\
    X(TrailingSampleLeadingSetup, 1)


namespace avr {
namespace mcal {
namespace spi {
class SpiRegisters {
public:
    enum SPCR {
        KSPR0 = 0, KSPR1, KCPHA, KCPOL, KMSTR, KDORD, KSPE, KSPIE,      
    };
    enum SPSR {
        KSPI2X = 0, KWCOL=6, KSPIF,
    };
    using Register_t = utils::Register<avr::types::AvrRegWidth>;
    SpiRegisters(avr::types::AvrRegWidth baseAddr);
    Register_t& GetSPDR();
    Register_t& GetSPSR();
    Register_t& GetSPCR();
private:
    Register_t spdr_;
    Register_t spsr_;
    Register_t spcr_;
};

class Spi {
public:
    using SPCR = SpiRegisters::SPCR;
    using SPSR = SpiRegisters::SPSR;
    using PFunction_t  = void(*)();
    enum FreqMode {
        #define X(name_, val_)  k##name_ = val_,
            SPI_SCK_FREQ_MODE
        #undef X
    };
    enum DataOrder {
        #define X(name_, val_)  k##name_ = val_,
            SPI_DATA_ORDER
        #undef X
    };
    enum MasterSlaveSel {
        #define X(name_, val_)  k##name_ = val_,
            SPI_MASTER_SLAVE_SEL
        #undef X
    };
    enum ClockPolarity {
        #define X(name_, val_)  k##name_ = val_,
            SPI_CPOL
        #undef X
    };
   
    enum ClockPhase {
        #define X(name_, val_)  k##name_ = val_,
            SPI_CLK_PHASE
        #undef X
    };
    struct SpiConfigurations {
    
        FreqMode        frequency_mode;
        DataOrder       data_order;
        MasterSlaveSel  spi_mode;
        ClockPolarity   clk_polarity;
        ClockPhase      clk_phase;
    };
    Spi();
    void Init(const SpiConfigurations& cnf = {kf16, kMsb, kMaster, kLeadingRising, kLeadingSampleTrailingSetup}); //IGNORE-STYLE-CHECK[L004]
    void Reset();
    uint8_t Transceive(uint8_t data);
    uint8_t Transceive(uint8_t data, PFunction_t pFun);
    void Transmit(uint8_t data);
    uint8_t Receive();
    void SetReceivedData(uint8_t data);
    uint8_t GetDataReg();
    PFunction_t GetTransceiveCallBack();
private:
    SpiRegisters registers_;
    PFunction_t transceive_callback_;
    uint8_t spdr_data_;
    void SetFrequencyMode(FreqMode fm);
    void SetDataOrder(DataOrder d);
    void SetSpiMode(MasterSlaveSel ms);
    void SetClockPolarity(ClockPolarity cp);
    void SetClockPhase(ClockPhase cph);
};

}}} // avr::mcal::spi

extern avr::mcal::spi::Spi SPI;

#undef SPI_SCK_FREQ_MODE
#undef SPI_DATA_ORDER
#undef SPI_MASTER_SLAVE_SEL
#undef SPI_CPOL
#undef SPI_CLK_PHASE

#endif // _SPI_H_H
