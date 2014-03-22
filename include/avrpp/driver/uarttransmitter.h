/**
 * @file uarttransmitter.h
 *
 * @date 17.11.2012
 * @author Christian Menard
 */

#ifndef _AVRPP_DRIVER_UARTTRANSMITTER_H_
#define _AVRPP_DRIVER_UARTTRANSMITTER_H_

#include <avrpp/io.h>
#include <avrpp/config.h>
#include <avrpp/util/buffer.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

ISR(USART0_UDRE_vect);
ISR(USART1_UDRE_vect);

// TODO split Uart0 and Uart1 into separate headers
// TODO do not use macros to calculate baud values
// TODO use template parameters for buffer size

namespace avrpp
{
namespace driver
{
	class Uart0Transmitter
	{
		friend void (::USART0_UDRE_vect) ();

	  private:
		static util::Buffer<uint8_t, UART0_TRANSMITTER_BUFFER_SIZE> buffer;
	  public:
		static void init()
		{
			DDRD |= (1 << PD1);

			io::Usart0::writeBaud(UBRR_VALUE);

			if( USE_2X)
				io::Usart0::enableDoubleSpeed();

			io::Usart0::enableTransmitter();
		}

		static void write( uint8_t byte);
	};

	class Uart1Transmitter
	{
		friend void (::USART1_UDRE_vect) ();

	  private:
		static util::Buffer<uint8_t, UART1_TRANSMITTER_BUFFER_SIZE> buffer;
	  public:
		static void init()
		{
			DDRD |= (1 << PD3);

			io::Usart1::writeBaud(UBRR_VALUE);

			if( USE_2X)
				io::Usart1::enableDoubleSpeed();

			io::Usart1::enableTransmitter();
		}

		static void write( uint8_t byte);
	};
}
}

#endif /* _AVRPP_DRIVER_UARTTRANSMITTER_H_ */
