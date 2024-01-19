#ifndef _AVRTEST_H_
#define _AVRTEST_H_

namespace avr {
namespace test {

class AVRTest {
public:
    AVRTest(const char* testName);
    ~AVRTest();
    template <typename T>
    void Expected_Eq(T actual, T expected);
    template <typename T>
    void Expected_Neq(T actual, T expected);
    template <typename T>
    void Expected_True(T expected);
    template <typename T>
    void Expected_False(T expected);
private:
    enum NumberMode {kBin, kDec};
    volatile char* print_;
    const char* testName_;
    void Print(const char *str);
    template<NumberMode M>
    void Print(int num);
};

}} // avr::test

#endif /* _AVRTEST_H_ */
