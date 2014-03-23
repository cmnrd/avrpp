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

#ifndef _AVRPP_IO_MXXX4_USART0_H_
#define _AVRPP_IO_MXXX4_USART0_H_

#ifndef _AVRPP_IO_H_
#  error "Include <avrpp/io.h> instead of this file."
#endif

#include <avr/io.h>
#include <util/atomic.h>
#include <avrpp/io/edge.h>

// Interrupt enable bits
#define AVRPP_IO_USART0_IE_BITS    ((1 << RXCIE0) | (1 << TXCIE0) | (1 << UDRIE0))
// interrupt flags
#define AVRPP_IO_USART0_IF_BITS    ((1 << RXC0)   | (1 << TXC0)   | (1 << UDRE0))
#define AVRPP_IO_USART0_STATE_BITS ((1 << DOR0)   | (1 << FE0)    | (1 << UPE0))
#define AVRPP_IO_USART0_MODE_BITS  ((1 << UMSEL00)| (1 << UMSEL01))
#define AVRPP_IO_USART0_PARITY_BITS ((1 << UPM00)   | (1 << UPM01))

// character size bits of register B and register C
#define AVRPP_IO_USART0_CS_B_BITS  ((1 << (UCSZ02+1)))
#define AVRPP_IO_USART0_CS_C_BITS  ((1 << UCSZ01) | (1 << UCSZ00))

namespace avrpp
{

enum class Usart0InterruptFlag : uint8_t
{
	RECEIVE_COMPLETE = (1 << RXC0),
	TRANSMIT_COMPLETE = (1 << TXC0),
	DATA_REGISTER_EMPTY = (1 << UDRE0)
};

enum class Usart0InterruptEnable : uint8_t
{
	RECEIVE_COMPLETE = (1 << RXCIE0),
	TRANSMIT_COMPLETE = (1 << TXCIE0),
	DATA_REGISTER_EMPTY = (1 << UDRIE0)
};

enum class Usart0StateFlag : uint8_t
{
	FRAME_ERROR =  (1 << FE0),
	DATA_OVERRUN = (1 << DOR0),
	PARITY_ERROR = (1 << UPE0)
};

enum class Usart0Mode : uint8_t
{
	ASYNCHRONOUS = 0,
	SYNCHRONOUS = (1 << UMSEL00),
	MASTER_SPI = ( 1 << UMSEL01) | (1 << UMSEL00)
};

enum class Usart0Parity : uint8_t
{
	DISABLED = 0,
	EVEN_PARITY = (1 << UPM01),
	ODD_PARITY = (1 << UPM00) | (1 << UPM01)
};

enum class Usart0StopBit : uint8_t
{
	_1_BIT = 0,
	_2_BIT = (1 << USBS0)
};

enum class Usart0CharacterSize : uint8_t
{
	_5_BIT = 0,
	_6_BIT = (1 << UCSZ00),
	_7_BIT = (1 << UCSZ01),
	_8_BIT = (1 << UCSZ01) | (1 << UCSZ00),
	_9_BIT = (1 << (UCSZ02 + 1)) | (1 << UCSZ01) | (1 << UCSZ00)
	// UCSZ02 + 1 is used because UCSZ02 has the same bit number as UCSZ01
};

class Usart0
{
  public:
	static void enableReceiver()
	{
		UCSR0B |= (1 << RXEN0);
	}

	static void disableReceiver()
	{
		UCSR0B &= ~(1 << RXEN0);
	}

	static bool isReceiverEnabled()
	{
		return UCSR0B & (1 << RXEN0);
	}

	static void enableTransmitter()
	{
		UCSR0B |= (1 << TXEN0);
	}

	static void disableTransmitter()
	{
		UCSR0B &= ~(1 << TXEN0);
	}

	static bool isTransmitterEnabled()
	{
		return UCSR0B & (1 << TXEN0);
	}

	static void enableInterrupts(
			Usart0InterruptEnable int1,
			Usart0InterruptEnable int2 = (Usart0InterruptEnable) 0,
			Usart0InterruptEnable int3 = (Usart0InterruptEnable) 0)
	{
		UCSR0B |= ((uint8_t) int1) | ((uint8_t) int2) | ((uint8_t) int3);
	}

	static void disableInterrupts(
			Usart0InterruptEnable int1,
			Usart0InterruptEnable int2 = (Usart0InterruptEnable) 0,
			Usart0InterruptEnable int3 = (Usart0InterruptEnable) 0)
	{
		UCSR0B &= ~(((uint8_t) int1) | ((uint8_t) int2) | ((uint8_t) int3));
	}

	static bool isInterruptEnabled( Usart0InterruptEnable i)
	{
		return UCSR0B & ((uint8_t) i);
	}

	static void clearInterruptFlags(
			Usart0InterruptFlag int1,
			Usart0InterruptFlag int2 = (Usart0InterruptFlag) 0,
			Usart0InterruptFlag int3 = (Usart0InterruptFlag) 0)
	{
		UCSR0A = ((UCSR0A & ~AVRPP_IO_USART0_STATE_BITS) | // state must always been set to zero
				(((uint8_t) int1) | ((uint8_t) int2) | ((uint8_t) int3)));
	}

	static bool isInterruptFlagSet( Usart0InterruptFlag i)
	{
		return UCSR0A & ((uint8_t) i);
	}

	static bool isStateFlagSet( Usart0StateFlag flag)
	{
		return UCSR0A |= ((uint8_t) flag);
	}

	static void enableDoubleSpeed()
	{
		UCSR0A = ((UCSR0A & ~AVRPP_IO_USART0_STATE_BITS) | (1 << U2X0)); // state must always been set to zero
	}

	static void disableDoubleSpeed()
	{
		UCSR0A = ((UCSR0A & ~AVRPP_IO_USART0_STATE_BITS) & ~(1 << U2X0)); // state must always been set to zero
	}

	static bool isDoubleSpeedEnabled()
	{
		return UCSR0A & (1 << U2X0);
	}

	static void enableMultiProcessor()
	{
		UCSR0A = ((UCSR0A & ~AVRPP_IO_USART0_STATE_BITS) | (1 << MPCM0)); // state must always been set to zero
	}

	static void disableMultiProcessor()
	{
		UCSR0A = ((UCSR0A & ~AVRPP_IO_USART0_STATE_BITS) & ~(1 << MPCM0)); // state must always been set to zero
	}

	static bool isMultiProcessorEnabled()
	{
		return UCSR0A & (1 << MPCM0);
	}

	static void setMode( Usart0Mode mode)
	{
		UCSR0C = (UCSR0C & ~ AVRPP_IO_USART0_MODE_BITS) | ((uint8_t) mode);
	}

	static Usart0Mode getMode()
	{
		return (Usart0Mode) (UCSR0C & AVRPP_IO_USART0_MODE_BITS);
	}

	static void setParity( Usart0Parity parity)
	{
		UCSR0C = (UCSR0C & ~AVRPP_IO_USART0_PARITY_BITS) | ((uint8_t) parity);
	}

	static Usart0Parity getParity()
	{
		return (Usart0Parity) (UCSR0C & AVRPP_IO_USART0_PARITY_BITS);
	}

	static void setStopBit( Usart0StopBit bit)
	{
		UCSR0C = (bit == Usart0StopBit::_2_BIT ?
						(UCSR0C | (1 << USBS0)) :
						(UCSR0C & ~(1 << USBS0)));
	}

	static Usart0StopBit getStopBit()
	{
		return (Usart0StopBit) (UCSR0C & (1 << USBS0));
	}

	static void setCharacterSize( Usart0CharacterSize size)
	{
		UCSR0C = (UCSR0C & ~AVRPP_IO_USART0_CS_C_BITS) | (uint8_t) size;

		UCSR0B = ( size == Usart0CharacterSize::_9_BIT)
				? (UCSR0B | (1 << UCSZ02))
				: (UCSR0B & ~(1 << UCSZ02));
	}

	static void setClockPolarity( Edge edge)
	{
		UCSR0C = edge == Edge::RISING_EDGE ?
				(UCSR0C | (1 << UCPOL0)) :
				(UCSR0C & ~(1 << UCPOL0));
	}

	static Edge getClockPolarity()
	{
		return (UCSR0C & (1 << UCPOL0)) ?
				Edge::RISING_EDGE :
				Edge::FALLING_EDGE;
	}

	static void writeByte( uint8_t c)
	{
		UDR0 = c;
	}

	static uint8_t readByte()
	{
		return UDR0;
	}


	static void writeBaud( uint16_t x)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			UBRR0 = x;
		}
	}
};

}

#endif /* _AVRPP_IO_MXXX4_USART0_H_ */
