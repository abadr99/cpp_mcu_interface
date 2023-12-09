#include <stdint.h>
#include "register.hpp"

using namespace utils;

template<typename RegWidth_t>
Register<RegWidth_t>::Register(const RegWidth_t address) 
: _pReg (reinterpret_cast<volatile RegWidth_t *>(address))
{
    /* EMPTY */    
}

template<typename RegWidth_t>
template<uint8_t bitNumber>
constexpr void Register<RegWidth_t>::SetBit() const {
    *_pReg |=  (1 << bitNumber);
}

template<typename RegWidth_t>
template<uint8_t bitNumber>
constexpr void Register<RegWidth_t>::ClearBit() const {
    *_pReg  &= ~(1 << bitNumber);
}

template<typename RegWidth_t>
template<uint8_t bitNumber>
constexpr uint8_t Register<RegWidth_t>::GetBit() const {
    return ((*_pReg & (1 << bitNumber)) >> bitNumber);
}

template<typename RegWidth_t>
template<uint8_t bitNumber>
constexpr void Register<RegWidth_t>::ToggleBit() const {
    *_pReg ^=  (1 << bitNumber);
}

template<typename RegWidth_t>
constexpr void Register<RegWidth_t>::Set() const {
    *_pReg = utils::GetAllOnes<RegWidth_t>();
}

template<typename RegWidth_t>
constexpr void Register<RegWidth_t>::Clear() const {
    *_pReg  = 0x00;
}

template<typename RegWidth_t>
constexpr RegWidth_t Register<RegWidth_t>::Get() const {
    return *_pReg;
}
