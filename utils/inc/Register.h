#ifndef _REGISTER_H_
#define _REGISTER_H_

#include "Helpers.h"
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
    // Set all bits to one
    void Set() const;
    void Clear() const;
    RegWidth_t Read() const;

    template<RegWidth_t mask, uint8_t startBit, RegWidth_t val>
    void SetRegisterWithMask()
    {
        static_assert(startBit < sizeof(RegWidth_t)*8,  
                      "Calling SetRegisterWithMask() with out of range bit");
         *_pReg = (*_pReg & mask) | ((val << startBit) & (~mask));
    }
    /**
     * @brief Read Specified bits in specific register
     * 
     * @tparam startBit 
     * @tparam endBit 
     * @return RegWidth_t 
     * @example If we want to read bits 2,3,4 from register R 
     *          where R = 0b11110000
     *          x = ReadBits<2,4>(); ==> x = 0b100 = 4
     */
    template<uint8_t startBit, uint8_t endBit>
    RegWidth_t ReadBits() {
        static_assert(startBit < endBit,  
                      "Calling ReadBits with startBit first");
        uint8_t numberOfBits = endBit - startBit + 1;
        return (*_pReg >> startBit) & (utils::GetOnes<uint8_t>(numberOfBits));
    }

    template<uint8_t startBit, uint8_t endBit>
    void SetBits() {
        static_assert(startBit < endBit,  
                      "Calling ReadBits with startBit first");
        uint8_t numberOfBits = endBit - startBit + 1;
        uint8_t mask = utils::GetOnes<uint8_t>(numberOfBits) << startBit;
        *_pReg |= mask;
    }
private:
    volatile RegWidth_t* _pReg;
};

}

#endif // _REGISTER_H_
