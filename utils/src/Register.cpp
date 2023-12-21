#include <stdint.h>
#include "Helpers.h"
#include "Register.h"

using namespace utils;

template<typename RegWidth_t>
Register<RegWidth_t>::Register(const RegWidth_t address) 
: _pReg (reinterpret_cast<volatile RegWidth_t *>(address))
{
    /* EMPTY */    
}

template<typename RegWidth_t>
void Register<RegWidth_t>::Set() const {
    *_pReg = utils::GetAllOnes<RegWidth_t>();
}

template<typename RegWidth_t>
void Register<RegWidth_t>::Clear() const {
    *_pReg  = 0x00;
}

template<typename RegWidth_t>
RegWidth_t Register<RegWidth_t>::Get() const {
    return *_pReg;
}
template<typename RegWidth_t>
void Register<RegWidth_t>::SetRegisterValue(RegWidth_t R) {
    *_pReg  = R;
}
template<typename RegWidth_t>
RegWidth_t Register<RegWidth_t>::GetRegisterValue() {
    return *_pReg;
}
template class Register<uint8_t>;
template class Register<uint32_t>;
template class Register<uint64_t>;
