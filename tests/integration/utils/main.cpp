#include <stdint.h>
#include "../../../utils/inc/Register.h"
#include "../../../utils/inc/Helpers.h"
#include "../../../tests/impl/AVRTest.h"
 
int main () {
    {
        avr::test::AVRTest TEST("Extract-Bits");
        const uint32_t VALUE = 0xAABBCCDD;
        uint8_t RESULT = utils::ExtractBits<uint32_t, 0, 3>(VALUE); //0b1101
        TEST.Expected_Eq(static_cast<uint8_t>(0b1101), RESULT);
        RESULT = utils::ExtractBits<uint32_t, 3, 5>(VALUE); //0b11
        TEST.Expected_Eq(static_cast<uint8_t>(0b11), RESULT);
        RESULT = utils::ExtractBits<uint32_t, 13, 20>(VALUE); //0b11011110
        TEST.Expected_Eq(static_cast<uint8_t>(0b11011110), RESULT);
        RESULT = utils::ExtractBits<uint32_t, 28, 31>(VALUE); //0b1010
        TEST.Expected_Eq(static_cast<uint8_t>(0b1010), RESULT);
        RESULT = utils::ExtractBits<uint32_t, 0>(VALUE); //0b1
        TEST.Expected_Eq(static_cast<uint8_t>(0b1), RESULT);
    }
}
