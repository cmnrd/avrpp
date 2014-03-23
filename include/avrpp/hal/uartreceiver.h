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

#ifndef _AVRPP_HAL_UARTRECEIVER_H_
#define _AVRPP_HAL_UARTRECEIVER_H_

#include <avrpp/config.h>
#include <avrpp/util/buffer.h>
#include <avrpp/io.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>

ISR(USART0_RX_vect);
ISR(USART1_RX_vect);

// TODO see uarttransmitter todo list

namespace avrpp
{
namespace hal
{
	class Uart0Receiver
	{
	  private:
		static util::Buffer<uint8_t, UART0_RECEIVER_BUFFER_SIZE> buffer;
	  public:
		static void init()
		{
			DDRD &= ~(1 << PD0);
			io::Usart0::writeBaud(UBRR_VALUE);

			if( USE_2X)
				io::Usart0::enableDoubleSpeed();

			io::Usart0::enableReceiver();
			io::Usart0::enableInterrupts(io::Usart0InterruptEnable::RECEIVE_COMPLETE);
		}

		static void flushBuffer()
		{
			buffer.flush();
		}

		static bool dataReceived()
		{
			return !buffer.isEmpty();
		}

		static uint8_t read()
		{
			return buffer.pop();
		}

		friend void (::USART0_RX_vect) ();
	};

	class Uart1Receiver
	{
	  private:
		static util::Buffer<uint8_t, UART1_RECEIVER_BUFFER_SIZE> buffer;
	  public:
		static void init()
		{
			DDRD &= ~(1 << PD2);
			io::Usart1::writeBaud(UBRR_VALUE);

			if( USE_2X)
				io::Usart1::enableDoubleSpeed();

			io::Usart1::enableReceiver();
			io::Usart1::enableInterrupts(io::Usart1InterruptEnable::RECEIVE_COMPLETE);
		}

		static void flushBuffer()
		{
			buffer.flush();
		}

		static bool dataReceived()
		{
			return !buffer.isEmpty();
		}

		static uint8_t read()
		{
			return buffer.pop();
		}

		friend void (::USART1_RX_vect) ();
	};
}
}


#endif /* _AVRPP_HAL_UARTRECEIVER_H_ */
