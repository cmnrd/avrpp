/**
 * @file uarttransmitter.cpp
 *
 * @date 17.11.2012
 * @author Christian Menard
 */

#include <avrpp/driver/uarttransmitter.h>
using namespace avrpp;
using namespace avrpp::driver;

util::Buffer<uint8_t,UART0_TRANSMITTER_BUFFER_SIZE> Uart0Transmitter::buffer;

void Uart0Transmitter::write(uint8_t byte)
{
	buffer.push(byte);
	io::Usart0::enableInterrupts(io::Usart0InterruptEnable::DATA_REGISTER_EMPTY);
}

ISR(USART0_UDRE_vect)
{
	uint8_t tmp = Uart0Transmitter::buffer.pop();
	io::Usart0::writeByte(tmp);
	if( Uart0Transmitter::buffer.isEmpty())
		io::Usart0::disableInterrupts(io::Usart0InterruptEnable::DATA_REGISTER_EMPTY);
}

util::Buffer<uint8_t,UART1_TRANSMITTER_BUFFER_SIZE> Uart1Transmitter::buffer;

void Uart1Transmitter::write(uint8_t byte)
{
	buffer.push(byte);
	io::Usart0::enableInterrupts(io::Usart0InterruptEnable::DATA_REGISTER_EMPTY);
}

ISR(USART1_UDRE_vect)
{
	uint8_t tmp = Uart1Transmitter::buffer.pop();
	io::Usart1::writeByte(tmp);
	if( Uart1Transmitter::buffer.isEmpty())
		io::Usart1::disableInterrupts(io::Usart1InterruptEnable::DATA_REGISTER_EMPTY);
}
