#ifndef _MATH_H_
#define _MATH_H_

namespace utils {
namespace math  {

struct FloatingNumber {
    size_t integerPart;
    size_t fractionPart;
};

constexpr FloatingNumber SeparateFloatingNumber(float number, uint8_t prec = 3) { //IGNORE-STYLE-CHECK[L004]
    // --- Get integer part
    size_t integerPart = static_cast<size_t>(number);
    
    // --- Get fraction part
    size_t multiplierFactor = 1;
    for (uint8_t i = 0; i < prec ; ++i) {
        multiplierFactor *= 10;
    }
    float  fractionPart = number - integerPart;
    size_t decimalPrec  =  fractionPart * multiplierFactor;
    return {.integerPart  = integerPart, 
            .fractionPart = decimalPrec};
}  

}} // namespace utils::math


#endif // _MATH_H_
