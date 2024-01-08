#include <stdint.h>
#include "../../../utils/inc/Register.h"
#include "../../../utils/inc/Helpers.h"
#include "../../../utils/inc/Test.h"
 
#define TESTED_REGISTER (0x3B)
#define EECR       *((volatile uint8_t *)TESTED_REGISTER)

int main () {
    utils::Register<uint8_t> R(TESTED_REGISTER);
    R.Set();
    print_str("Test results: \n");
    print_num(R.Read()); //255
    new_line();
    int x = EECR;
    print_num(x); //255
    new_line();

    R.ClearBit<0>();
    R.ClearBit<1>();
    R.ClearBit<2>();
    R.ClearBit<3>();
    print_num(R.Read()); //240
    new_line();
    print_num(EECR); //240
    new_line();

    R.ToggleBit<4>();
    R.ToggleBit<5>();
    R.ToggleBit<6>();
    R.ToggleBit<7>();
    print_num(R.Read()); //0
    new_line();
    print_num(EECR); //0
    new_line();

    R.SetBit<0>();
    R.SetBit<1>();
    R.SetBit<2>();
    R.SetBit<3>();
    print_num(R.Read()); //15
    new_line();
    print_num(EECR); //15
    new_line();

    print_num(R.ReadBit<0>()); //1
    new_line();
    print_num(R.ReadBit<1>()); //1
    new_line();
    print_num(R.ReadBit<2>()); //1
    new_line();
    print_num(R.ReadBit<3>()); //1
    new_line();

    R.Clear();
    print_num(R.Read()); //0
    new_line();

    R.SetRegisterValue(0b11110011); 
    print_num_binary(R.Read()); // 0b11110011
    new_line();
    // suppose we want to change the third three bits i.e. Bits 2,3,4
    // to be 101
    R.WriteWithMask<0b11100011, 2, 5>();
    print_num_binary(R.Read()); // 0b11110111
    new_line();
    print_num(R.ReadBits<2, 4>()); // 5
    new_line();
    print_num(R.ReadBits<0, 1>()); // 3
    new_line();
    R.Clear();
    R.SetBits<2, 4>();
    print_num_binary(R.Read()); // 0b0001_1100
    new_line();
}
