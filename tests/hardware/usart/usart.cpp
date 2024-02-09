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

int main()
{
USART.Init();
USART.Send('4');
USART.Send(' ');
uint16_t data;
while (1)
{
   
    data=USART.Receive();
    USART.Send(data);
    _delay_ms(500);

}




    return 0;
}