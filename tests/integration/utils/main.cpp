#include <stdint.h>
#include "../../../utils/inc/Register.h"
#include "../../../utils/inc/Helpers.h"
#include "../../../utils/inc/Test.h"
 
#define TESTED_REGISTER (0x3B)
#define EECR       *((volatile uint8_t *)TESTED_REGISTER)

int main () {
    {
        print_str("--------- EXTRACT_BITS_TEST ---------\n"); 
        const uint32_t VALUE = 0xAABBCCDD;
        uint8_t RESULT = utils::ExtractBits<uint32_t, 0, 3>(VALUE); //0b1101
        print_num_binary(RESULT);
        RESULT = utils::ExtractBits<uint32_t, 3, 5>(VALUE); //0b11
        print_num_binary(RESULT);
        RESULT = utils::ExtractBits<uint32_t, 13, 20>(VALUE); //0b11011110
        print_num_binary(RESULT);
        RESULT = utils::ExtractBits<uint32_t, 28, 31>(VALUE); //0b1010
        print_num_binary(RESULT);
        RESULT = utils::ExtractBits<uint32_t, 0>(VALUE); //0b1
        print_num_binary(RESULT);
    }
}
