#include <stdint.h>
#include "AVRTest.h"

// ============================================================================
// =============================== NAMESPACES =================================
// ============================================================================
using namespace avr::test;
#define OUT_REG     (0x20)

// ============================================================================
// ============================ PRIVATE METHODS ===============================
// ============================================================================
void AVRTest::Print(const char *str) {
    const char *c;
    for (c = str; *c != '\0' ; c++) {
        *print_ = *c;
    }
}

template<AVRTest::NumberMode M>
void AVRTest::Print(int num) {
    if (M == NumberMode::kBin) {
        int str[sizeof(int) * 8];
        int i;
        if (num == 0) {
            Print("0b");
            *print_ = '0';
            return;
        }
        for (i = 0 ; num > 0 ; i++) {
            str[i] = num % 2;
            num = num / 2;
        }
        Print("0b");
        for (i = i - 1; i >= 0; i--) {
            *print_ = str[i] + '0';
        }
        return;
    }
    char str[15];
    int i = 0;
    if (num == 0) {
        *print_ = '0';
    }
    else {
        while (num != 0) {
            str[i++] = (num % 10) + '0';
            num /= 10;
        }
        for (int j = i - 1 ; j >= 0 ; j--) {
            *print_ = str[j];
        }
    }
}
template void AVRTest::Print<AVRTest::NumberMode::kBin>(int num);
template void AVRTest::Print<AVRTest::NumberMode::kDec>(int num);
// ============================================================================
// ============================= PUBLIC METHODS ===============================
// ============================================================================

AVRTest::AVRTest(const char* testName)
    : print_(reinterpret_cast<volatile char *>(OUT_REG))
    , testName_(testName)
{ 
    Print("[ RUN      ] ");
    Print(testName_);
    Print("\n");
}

AVRTest::~AVRTest() {
    Print("--------------------------------------------------\n");
}

template <typename T>
void AVRTest::Expected_Eq(T actual, T expected) {
    if (actual == expected) {
        Print("[       OK ] ");
        Print("Two values are equal\n");
        return;
    }
    Print("[     FAIL ] ");
    Print("Expected equality of ");
    Print<kDec>(expected);
    Print(" ("); Print<kBin>(expected); Print(") ");
    Print("which is: ");
    Print<kDec>(actual);
    Print(" ("); Print<kBin>(actual); Print(") ");
    Print("\n");
}

template <typename T>
void AVRTest::Expected_Neq(T actual, T expected) {
    if (actual != expected) {
        Print("[       OK ] ");
        Print("Two values are not equal\n");
        return;
    }
    Print("[     FAIL ] ");
    Print("Expected non equality of ");
    Print<kDec>(expected);
    Print("( "); Print<kBin>(expected); Print(" ) ");
    Print("which is: ");
    Print<kDec>(actual);
    Print("( "); Print<kBin>(actual); Print(" ) ");
    Print("\n");
}

template <typename T>
void AVRTest::Expected_True(T expected) {
    if (true == expected) {
        Print("[       OK ] ");
        Print("Equal TRUE\n");
        return;
    }
    Print("[     FAIL ] ");
    Print("Expected equality of ");
    Print<kDec>(true); Print("which is: "); Print<kDec>(expected);
    Print("\n");
}

template <typename T>
void AVRTest::Expected_False(T expected) {
    if (false == expected) {
        Print("[       OK ] ");
        Print("Equal FALSE\n");
        return;
    }
    Print("[     FAIL ] ");
    Print("Expected equality of ");
    Print<kDec>(false); Print("which is: "); Print<kDec>(expected);
    Print("\n");
}

#define INSTANTIATE_METHOD(method_)\
    template void AVRTest::method_(uint8_t, uint8_t);\
    template void AVRTest::method_(uint16_t, uint16_t);

INSTANTIATE_METHOD(Expected_Eq)
INSTANTIATE_METHOD(Expected_Neq)

#undef INSTANTIATE_METHOD

#define INSTANTIATE_METHOD(method_)\
    template void AVRTest::method_(uint8_t);\
    template void AVRTest::method_(uint16_t);

INSTANTIATE_METHOD(Expected_True)
INSTANTIATE_METHOD(Expected_False)

#undef INSTANTIATE_METHOD