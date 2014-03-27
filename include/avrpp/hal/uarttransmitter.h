/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Christian Menard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _AVRPP_HAL_UARTTRANSMITTER_H_
#define _AVRPP_HAL_UARTTRANSMITTER_H_

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
// TODO find a way to implement the ISRs inside the header

namespace avrpp
{
	class Uart0Transmitter
	{
		friend void (::USART0_UDRE_vect) ();

	  private:
		static Buffer<uint8_t, UART0_TRANSMITTER_BUFFER_SIZE> buffer;
	  public:
		static void init()
		{
			DDRD |= (1 << PD1); // TODO generalize this

			Usart0::writeBaud(UBRR_VALUE);

			if( USE_2X)
				Usart0::enableDoubleSpeed();

			Usart0::enableTransmitter();
		}

		static void write( uint8_t byte);
	};

	class Uart1Transmitter
	{
		friend void (::USART1_UDRE_vect) ();

	  private:
		static Buffer<uint8_t, UART1_TRANSMITTER_BUFFER_SIZE> buffer;
	  public:
		static void init()
		{
			DDRD |= (1 << PD3);

			Usart1::writeBaud(UBRR_VALUE);

			if( USE_2X)
				Usart1::enableDoubleSpeed();

			Usart1::enableTransmitter();
		}

		static void write( uint8_t byte);
	};
}

#endif /* _AVRPP_HAL_UARTTRANSMITTER_H_ */
