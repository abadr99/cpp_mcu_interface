#include <stdint.h>
#include "Register.h"
#include "Helpers.h"
#include "Test.h"
 
#define TESTED_REGISTER (0x3B)
#define EECR       *((volatile uint8_t *)TESTED_REGISTER)

int main () {
    utils::Register<uint8_t> R(TESTED_REGISTER);
    R.Set();
    print_str("Test results: \n");
    print_num(R.Get()); //255
    new_line();
    int x = EECR;
    print_num(x); //255
    new_line();

    R.ClearBit<0>();
    R.ClearBit<1>();
    R.ClearBit<2>();
    R.ClearBit<3>();
    print_num(R.Get()); //240
    new_line();
    print_num(EECR); //240
    new_line();

    R.ToggleBit<4>();
    R.ToggleBit<5>();
    R.ToggleBit<6>();
    R.ToggleBit<7>();
    print_num(R.Get()); //0
    new_line();
    print_num(EECR); //0
    new_line();

    R.SetBit<0>();
    R.SetBit<1>();
    R.SetBit<2>();
    R.SetBit<3>();
    print_num(R.Get()); //15
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
    print_num(R.Get()); //0
    new_line();
}
