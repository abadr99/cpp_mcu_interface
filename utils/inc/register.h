#ifndef _REGISTER_H_
#define _REGISTER_H_

namespace utils {
// Wrapper class for register 
// All register modification should be handled in 
// this class
template<typename RegWidth_t>
class Register {
public:
    Register(const RegWidth_t address);
    
    template<uint8_t address>
    void SetAddress() {
        _pReg = reinterpret_cast<volatile RegWidth_t *>(address);
    }
    
    template<uint8_t bitNumber>
    void SetBit() const {
        *_pReg |=  (1 << bitNumber);
    }
    
    template<uint8_t bitNumber>
    void ClearBit() const{
        *_pReg  &= ~(1 << bitNumber);
    }

    template<uint8_t bitNumber>
    uint8_t GetBit() const {
        return ((*_pReg & (1 << bitNumber)) >> bitNumber);
    }

    template<uint8_t bitNumber>
    void ToggleBit() const {
        *_pReg ^=  (1 << bitNumber);
    }

    void Set() const;
    void Clear() const;
    RegWidth_t Get() const;
private:
    volatile RegWidth_t* _pReg;
};

}

#endif // _REGISTER_H_
