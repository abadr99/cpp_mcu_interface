#ifndef _REGISTER_H_
#define _REGISTER_H_

namespace utils {

template<typename T>
T GetAllOnes() {
    return static_cast<T>(-1);
}
// Wrapper class for register 
// All register modification should be handled in 
// this class
template<typename RegWidth_t>
class Register {
public:
    Register(const RegWidth_t address);
    
    template<uint8_t bitNumber>
    constexpr void SetBit() const;
    
    template<uint8_t bitNumber>
    constexpr void ClearBit() const;
    
    template<uint8_t bitNumber>
    constexpr uint8_t GetBit() const;
    
    template<uint8_t bitNumber>
    constexpr void ToggleBit() const;

    constexpr void Set() const;
    constexpr void Clear() const;
    constexpr RegWidth_t Get() const;
private:
    volatile RegWidth_t* _pReg;
};

}

#endif // _REGISTER_H_