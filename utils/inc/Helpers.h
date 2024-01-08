#ifndef _HELPERS_H_
#define _HELPERS_H_

namespace utils {

template<typename T>
T GetAllOnes() {
    return static_cast<T>(-1);
}

constexpr uint16_t ConvertToMilli(uint8_t Val) {
    return Val * 1000;
}
}

#endif // _HELPERS_H_
