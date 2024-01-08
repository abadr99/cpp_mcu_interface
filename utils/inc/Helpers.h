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

// Return specific number of ones
// Example: GetOnes(4) --> 0b1111
template<typename T>
constexpr T GetOnes(const T NumberOfOnes) {
    return (1 << NumberOfOnes) - 1;
}
}

#endif // _HELPERS_H_
