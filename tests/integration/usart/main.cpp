#include <stdint.h>

#include "../../../mcal/inc/Atmega32.h"
#include "../../../utils/inc/Register.h"
#include "../../../mcal/inc/Gpio.h"
#include "../../../mcal/inc/Usart.h"
#include "../../../utils/inc/Test.h"
 
using namespace utils;
using namespace avr::mcal::gpio;
using namespace avr::types;
using namespace avr::mcal::usart;

int main () {
USART.Init<     9600,
              TX_RX_Mode::kEnableRX_DisableTX,
              DataSize::kNineBits,
              ParityMode::kEven,
              StopBits::kOneBit,
              TransferMode::kAsynchronous_1x,
              ClockPolarity::kTxRising_RxFalling>();
print_str("**********************k*********************************");
new_line();

/*
*((volatile uint8_t*) 0x40)=0x03;  //UBBRL
*((volatile uint8_t*) 0x40)=(1<<7)|(1<<3)|(1<<2) | (1<<6); //UCSRC
*/

print_num(*((volatile uint8_t*) 0x40));
new_line();

uint8_t val=*((volatile uint8_t*) 0x40);
val=*((volatile uint8_t*) 0x40);
print_str("UCSRC: ");
print_num(val);
new_line();
/*print_str("UCSRA: ");
print_num_binary(*((volatile uint8_t*) 0x2B));
new_line();
print_str("UCSRB: ");
print_num_binary(*((volatile uint8_t*) 0x2A));
new_line();
print_str("UBRRH: ");
print_num_binary(*((volatile uint8_t*) 0x40));
new_line();
print_str("UBRRL: ");
print_num_binary(*((volatile uint8_t*) 0x29));
new_line();
print_str("UDR: ");
print_num_binary(*((volatile uint8_t*) 0x2C));
new_line();


print_str("*******************************************************");
new_line();
USART.Init<     600,
              TX_RX_Mode::kEnableRX_DisableTX,
              DataSize::kNineBits,
              ParityMode::kEven,
              StopBits::kOneBit,
              TransferMode::kAsynchronous_1x,
              ClockPolarity::kTxRising_RxFalling>();
 val=*((volatile uint8_t*) 0x40);
val=*((volatile uint8_t*) 0x40);
val=*((volatile uint8_t*) 0x40);
val=*((volatile uint8_t*) 0x40);
print_str("UCSRC: ");
//print_num_binary(*((volatile uint8_t*) 0x40));
print_num(val);
new_line();
print_str("UCSRA: ");
print_num_binary(*((volatile uint8_t*) 0x2B));
new_line();
print_str("UCSRB: ");
print_num_binary(*((volatile uint8_t*) 0x2A));
new_line();
print_str("UBRRH: ");
print_num_binary(*((volatile uint8_t*) 0x40));
new_line();
print_str("UBRRL: ");
print_num_binary(*((volatile uint8_t*) 0x29));
new_line();
print_str("UDR: ");
print_num_binary(*((volatile uint8_t*) 0x2C));
new_line();
*/
}
