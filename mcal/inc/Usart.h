#ifndef _USART_H_H
#define _USART_H_H

namespace avr {
namespace mcal {
namespace usart {

#define USART_BASE_ADDR             (0x2C)
#define UCSRC_REGISTER              (0x40)

#define USART_PARITY_MODE\
    X(Disabled, 0b00)\
    X(Even,     0b10)\
    X(Odd,      0b11)

#define USART_STOP_BITS\
    X(OneBit,  0)\
    X(TwoBits, 1)

#define USART_DATA_SIZE\
    X(FiveBits,  0b000)\
    X(SixBits,   0b001)\
    X(SevenBits, 0b010)\
    X(EightBits, 0b011)\
    X(NineBits,  0b111)

#define USART_CLK_POLARITY\
    X(TxRising_RxFalling, 0)\
    X(TxFalling_RxRising, 1)

#define USART_ERROR_TYPE\
    X(FrameError)\
    X(DataOverRun)\
    X(ParityError)\
    X(Success)

#define USART_TRANSFER_MODE\
    X(Asynchronous)\
    X(Synchronous)

enum ParityMode {
    #define X(name_, val_)  k##name_ = val_,
        USART_PARITY_MODE
    #undef X
};

enum StopBits {
    #define X(name_, val_)  k##name_ = val_,
        USART_STOP_BITS
    #undef X
};

enum DataSize {
    #define X(name_, val_)  k##name_ = val_,
        USART_DATA_SIZE
    #undef X
};

enum ClockPolarity {
    #define X(name_, val_)  k##name_ = val_,
        USART_CLK_POLARITY
    #undef X
};

enum ErrorType {
    #define X(name_)  k##name_,
        USART_ERROR_TYPE
    #undef X
};

enum TransferMode {
    #define X(name_)  k##name_,
        USART_TRANSFER_MODE
    #undef X
};

class UsartRegisters {
public:
    enum UCSRC {
        kUCPOL = 0x00,
        kUCSZ0,
        kUCSZ1,
        kUSBS,
        kUPM0,
        kUPM1,
        kUMSEL,
        kURSEL,      
    };
    enum UCSRB {
        kTXB8 = 0,
        kRXB8,
        kUCSZ2,
        kTXEN,
        kRXEN,
        kUDRIE,
        kTXCIE,
        kRXCIE,
    };
    enum UCSRA {
        kMPCM = 0,
        kU2X,
        kPE,
        kDOR,
        kFE,
        kUDRE,
        kTXC,
        kRXC,
    };
    using Register_t = utils::Register<avr::types::AvrRegWidth>;
    UsartRegisters(avr::types::AvrRegWidth baseAddr);
    Register_t& GetUDR();
    Register_t& GetUCSRA();
    Register_t& GetUCSRB();
    Register_t& GetUBRRL();
    Register_t& GetUCSRC();
private:
    Register_t udr_;
    Register_t ucsra_;
    Register_t ucsrb_;
    Register_t ubrrl_;
    Register_t ucsrc_;
};

class Usart {
public:
    using UCSRA = UsartRegisters::UCSRA;
    using UCSRB = UsartRegisters::UCSRB;
    using UCSRC = UsartRegisters::UCSRC;

    Usart();
    void Init();
    template <ParityMode M>
    void SetParityMode();
    template <StopBits N>
    void SetNumberOfStopBits();
    template <DataSize S>
    void SetDataSize();
    template<ClockPolarity P>
    void SetClockPolarity();
    template<ErrorType E>
    void GetErrorType();
    template<TransferMode M>
    void SelectTransferMode();
private:
    UsartRegisters registers_;
    enum Mask {
        kParityMode = 0xC2,
    };
};

}}} // avr::mcal::usart

#endif // _USART_H_H
