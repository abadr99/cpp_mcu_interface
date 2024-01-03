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
    
    template<RegWidth_t address>
    Register& SetAddress() {
        _pReg = reinterpret_cast<volatile RegWidth_t *>(address);
        return *this;
    }
    
    template<uint8_t bitNumber>
    Register& SetBit() {
        *_pReg |=  (1 << bitNumber);
        return *this;
    }
    
    template<uint8_t bitNumber>
    Register& ClearBit() {
        *_pReg  &= ~(1 << bitNumber);
        return *this;
    }

    template<uint8_t bitNumber>
    uint8_t ReadBit() {
        return ((*_pReg & (1 << bitNumber)) >> bitNumber);
    }

    template<uint8_t bitNumber>
    Register& ToggleBit() {
        *_pReg ^=  (1 << bitNumber);
        return *this;
    }

    void SetRegisterValue(RegWidth_t R);
    RegWidth_t GetRegisterValue();
    // Set all bits to one
    void Set() const;
    void Clear() const;
    RegWidth_t Get() const;
private:
    volatile RegWidth_t* _pReg;
};

}

#endif // _REGISTER_H_
