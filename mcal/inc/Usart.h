#ifndef _USART_H_H
#define _USART_H_H

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
    X(FiveBits,  0b00)\
    X(SixBits,   0b01)\
    X(SevenBits, 0b10)\
    X(EightBits, 0b11)\
    X(NineBits,  0b11)

#define USART_CLK_POLARITY\
    X(TxFalling_RxRising, 0)\
    X(TxRising_RxFalling, 1)

#define USART_ERROR_TYPE\
    X(FrameError)\
    X(DataOverRun)\
    X(ParityError)\
    X(Success)

#define USART_TRANSFER_MODE\
    X(Asynchronous_1x, 0b00)\
    X(Asynchronous_2x, 0b10)\
    X(Synchronous,     0b01)
namespace avr {
namespace mcal {
namespace usart {
class UsartRegisters {
public:
    enum UCSRC {
        kUCPOL = 0, kUCSZ0, kUCSZ1, kUSBS, kUPM0, kUPM1, kUMSEL, kURSEL,      
    };
    enum UCSRB {
        kTXB8 = 0, kRXB8, kUCSZ2, kTXEN, kRXEN, kUDRIE, kTXCIE, kRXCIE,
    };
    enum UCSRA {
        kMPCM = 0, kU2X, kPE, kDOR, kFE, kUDRE, kTXC, kRXC,
    };
    using Register_t = utils::Register<avr::types::AvrRegWidth>;
    UsartRegisters(avr::types::AvrRegWidth baseAddr);
    Register_t& GetUDR();
    // NOTE: We need this parameter with this register because if we are going
    // to write then we MUST clear certain bits first, otherwise we shouldn't 
    // modify register before reading.
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
    using BaudRate_t = uint32_t;
    using PFunction_t  = void(*)();
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
        #define X(name_, val_)  k##name_ = val_,
            USART_TRANSFER_MODE
        #undef X
    };
    enum TX_RX_Mode {
        kDisableRX_DisableTX = 0x00,
        kDisableRX_EnableTX  = 0x01,
        kEnableRX_DisableTX  = 0x10,
        kEnableRX_EnableTX   = 0x11,
    };
    struct UsartConfigurations {
        BaudRate_t      baudRate;
        TX_RX_Mode      tx_rx_mode;
        DataSize        dataSize;
        ParityMode      parityMode;
        StopBits        stopBitsNumber;
        TransferMode    transferMode;
        ClockPolarity   clkPolarity;
    };
    Usart();
    void Init(const UsartConfigurations& cnf = {9600, kEnableRX_EnableTX, kEightBits, kDisabled, kOneBit, kAsynchronous_1x, kTxRising_RxFalling}); //IGNORE-STYLE-CHECK[L004]
    void Send(uint16_t data);
    void Send(uint16_t data, PFunction_t pFun);
    PFunction_t GetTransmitterCallBack();
    PFunction_t GetReceiverCallBack();
    void WriteDataRegister(uint16_t data);
    uint16_t ReadDataRegister();
    uint16_t GetTransmittedData();
    void SetReceivedData(uint16_t data);
    uint16_t GetReceivedData();
    uint16_t Receive();
    uint16_t Receive(PFunction_t pFun);
    ErrorType GetErrorType();
private:
    UsartRegisters registers_;
    PFunction_t transmitterCallBack_;
    PFunction_t receiverCallBack_;
    uint16_t tx_data_;
    uint16_t rx_data_;
    uint8_t config_; // THIS VARIABLE IS TO WRITE UCSRC IN ONE INSTRUCTION
    void SetParityMode(ParityMode pm);
    void SetNumberOfStopBits(StopBits sp);
    void SetDataSize(DataSize ds);
    DataSize GetDataSize();
    void SetClockPolarity(ClockPolarity cp);
    void SelectTransferMode(TransferMode tm);
    TransferMode GetTransferMode();
    void SetTxRxMode(TX_RX_Mode mode);
    // This function should be called after configuring TransferMode as the 
    // calculations are depending on mode of data transfer
    void SetBaudRate(BaudRate_t baudRate);
};

}}} // avr::mcal::usart

#undef USART_PARITY_MODE
#undef USART_STOP_BITS
#undef USART_DATA_SIZE
#undef USART_CLK_POLARITY
#undef USART_ERROR_TYPE
#undef USART_TRANSFER_MODE

#endif // _USART_H_H
