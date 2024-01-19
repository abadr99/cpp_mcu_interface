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
inline constexpr T GetOnes(const T NumberOfOnes) {
    return (1 << NumberOfOnes) - 1;
}

template<typename T, uint8_t startBit, uint8_t endBit = startBit>
constexpr T ExtractBits(const T value) {
    static_assert(startBit <= endBit,  
                  "Calling ExtractBits with startBit first");
    uint8_t numberOfBits = endBit - startBit + 1;
    return (value >> startBit) & (utils::GetOnes<uint8_t>(numberOfBits));
}
}

#endif // _HELPERS_H_
