#include <stdint.h>
#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../mcal/inc/Usart.h"
 #include "../../../tests/impl/AVRTest.h"
 #include <util/delay.h>

using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;
using namespace avr::mcal::usart;
void send()
{
USART.Send('8');
}
int main()
{
//enable global interrupt
SEI();
USART.Init();
while (1)
{
   
    USART.Receive(send);
    _delay_ms(500);

}
    return 0;
}
