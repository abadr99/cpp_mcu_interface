#ifndef _USART_H_H
#define _USART_H_H

namespace avr {
namespace mcal {
namespace usart {

#define USART_BASE_ADDR             (0x2C)
#define UCSRC_REGISTER              (0x40)
#define UCSRH_REGISTER              (UCSRC_REGISTER)

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
    X(Asynchronous_1x)\
    X(Asynchronous_2x)\
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

enum TX_RX_Mode {
    kDisableRX_DisableTX = 0x00,
    kDisableRX_EnableTX  = 0x01,
    kEnableRX_DisableTX  = 0x10,
    kEnableRX_EnableTX   = 0x11,
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
    enum Mask {
        kParityMode = 0xC2,
        kHighDataBits = 0xF0,
        kTxRx = 0xE7,
        kTxB8 = 0x01,
    };
    using Register_t = utils::Register<avr::types::AvrRegWidth>;
    UsartRegisters(avr::types::AvrRegWidth baseAddr);
    Register_t& GetUDR();
    // NOTE: We need this parameter with this register because if we are going
    // to write then we MUST clear certain bits, otherwise we shouldn't modify
    // register before reading,
    Register_t& GetUCSRA(bool isWrite = true);
    Register_t& GetUCSRB();
    Register_t& GetUBRRL();
    Register_t& GetUBRRH();
    Register_t& GetUCSRC();
private:
    Register_t udr_;
    Register_t ucsra_;
    Register_t ucsrb_;
    Register_t ubrrl_;
    Register_t ubrrh_;
    Register_t ucsrc_;
};

class Usart {
public:
    using UCSRA = UsartRegisters::UCSRA;
    using UCSRB = UsartRegisters::UCSRB;
    using UCSRC = UsartRegisters::UCSRC;
    using Mask  = UsartRegisters::Mask;
    using BaudRate_t = uint32_t;
    Usart();
    template <
              BaudRate_t    BR   = 9600,
              TX_RX_Mode    TR   = TX_RX_Mode::kEnableRX_EnableTX,
              DataSize      DS   = DataSize::kEightBits,
              ParityMode    PM   = ParityMode::kDisabled,
              StopBits      SP   = StopBits::kOneBit,
              TransferMode  TM   = TransferMode::kAsynchronous_1x,
              ClockPolarity CP   = ClockPolarity::kTxRising_RxFalling
             >
    void Init() {
        SetDataSize<DS>();
        SetParityMode<PM>();
        SetNumberOfStopBits<SP>();
        SelectTransferMode<TM>();
        SetBaudRate<BR>();
        SetTxRxMode<TR>();
        if (TM == TransferMode::kSynchronous) {
            SetClockPolarity<CP>();
        }
    }
    template<typename T = uint8_t>
    void Send(T data);
    template<typename T = uint8_t>
    T Receive();
private:
    UsartRegisters registers_;
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
    TransferMode GetTransferMode();
    template <TX_RX_Mode M>
    void SetTxRxMode();
    // This function should be called after configuring TransferMode as the 
    // calculations are depending on mode of data transfer
    template <BaudRate_t BR>
    void SetBaudRate();
};

}}} // avr::mcal::usart

#endif // _USART_H_H
