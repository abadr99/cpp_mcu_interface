// sh scripts/testing/run-regressions.sh -d tests/integration/utils/
#include <stdint.h>
#include "../../../utils/inc/Register.h"
#include "../../../utils/inc/Helpers.h"
#include "../../../tests/impl/AVRTest.h"
 
#define TESTED_REGISTER (0x3B)
#define REG       *((volatile uint8_t *)TESTED_REGISTER)

int main () {
    {
        avr::test::AVRTest TESTER("Set-Bit");
        utils::Register<uint8_t> R(TESTED_REGISTER);
        REG = 0xF0;
        R.SetBit<0>();  R.SetBit<1>(); R.SetBit<2>(); R.SetBit<3>();
        R.SetBit<4>();  R.SetBit<5>(); R.SetBit<6>(); R.SetBit<7>();
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0xFF));
    }
    {
        avr::test::AVRTest TESTER("Clear-Bit");
        utils::Register<uint8_t> R(TESTED_REGISTER);
        REG = 0xF0;
        R.ClearBit<0>();  R.ClearBit<1>(); R.ClearBit<2>(); R.ClearBit<3>();
        R.ClearBit<4>();  R.ClearBit<5>(); R.ClearBit<6>(); R.ClearBit<7>();
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0));
    }
    {
        avr::test::AVRTest TESTER("Read-Bit");
        utils::Register<uint8_t> R(TESTED_REGISTER);
        REG = 0xAA;
        TESTER.Expect_Eq(R.ReadBit<0>(), static_cast<uint8_t>(0));
        TESTER.Expect_Eq(R.ReadBit<1>(), static_cast<uint8_t>(1));
        TESTER.Expect_Eq(R.ReadBit<2>(), static_cast<uint8_t>(0));
        TESTER.Expect_Eq(R.ReadBit<3>(), static_cast<uint8_t>(1));
        TESTER.Expect_Eq(R.ReadBit<4>(), static_cast<uint8_t>(0));
        TESTER.Expect_Eq(R.ReadBit<5>(), static_cast<uint8_t>(1));
        TESTER.Expect_Eq(R.ReadBit<6>(), static_cast<uint8_t>(0));
        TESTER.Expect_Eq(R.ReadBit<7>(), static_cast<uint8_t>(1));
        
    }
    {
        avr::test::AVRTest TESTER("Toggle-Bit");
        utils::Register<uint8_t> R(TESTED_REGISTER);
        REG = 0xF0;
        R.ToggleBit<0>(); R.ToggleBit<1>(); R.ToggleBit<2>(); R.ToggleBit<3>();
        R.ToggleBit<4>(); R.ToggleBit<5>(); R.ToggleBit<6>(); R.ToggleBit<7>();
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0x0F));
    }
    {
        avr::test::AVRTest TESTER("Templated Write-Bits");
        utils::Register<uint8_t> R(TESTED_REGISTER);
        REG = 0b11001100;
        R.WriteBits<0b101, 2, 4>();
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0b11010100));
        
        REG = 0b11001100;
        R.WriteBits<0b101, 0, 3>();
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0b11000101));
        
        REG = 0b11001100;
        R.WriteBits<0b101, 5, 7>();
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0b10101100));

        REG = 0b11001100;
        R.WriteBits<1, 1>();
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0b11001110));
    }
    {
        avr::test::AVRTest TESTER("Non Templated Write-Bits");
        utils::Register<uint8_t> R(TESTED_REGISTER);
        REG = 0b11001100;
        R.WriteBits<2, 4>(0b101);
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0b11010100));
        
        REG = 0b11001100;
        R.WriteBits<0, 3>(0b101);
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0b11000101));
        
        REG = 0b11001100;
        R.WriteBits<5, 7>(0b101);
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0b10101100));

        REG = 0b11001100;
        R.WriteBits<1>(1);
        TESTER.Expect_Eq(REG, static_cast<uint8_t>(0b11001110));
    }
    {
        avr::test::AVRTest TESTER("Read-Bits");
        utils::Register<uint8_t> R(TESTED_REGISTER);
        REG = 0b11001100;

        TESTER.Expect_Eq(R.ReadBits<2, 5>(), static_cast<uint8_t>(0b0011));
        TESTER.Expect_Eq(R.ReadBits<2, 7>(), static_cast<uint8_t>(0b110011));
        TESTER.Expect_Eq(R.ReadBits<0, 7>(), static_cast<uint8_t>(0b11001100));
        TESTER.Expect_Eq(R.ReadBits<0>(), static_cast<uint8_t>(0));
    }
}
