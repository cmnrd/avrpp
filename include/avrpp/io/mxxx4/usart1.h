/**
 * @file usart1.h
 *
 * @date 08.05.2012
 * @author Christian Menard
 */

#ifndef _AVRPP_IO_MXXX4_USART_H_
#define _AVRPP_IO_MXXX4_USART_H_

#include <avr/io.h>
#include <util/atomic.h>
#include <avrpp/io/edge.h>

// Interrupt enable bits
#define AVRPP_IO_USART1_IE_BITS    ((1 << RXCIE1) | (1 << TXCIE1) | (1 << UDRIE1))
// interrupt flags
#define AVRPP_IO_USART1_IF_BITS    ((1 << RXC1)   | (1 << TXC1)   | (1 << UDRE1))
#define AVRPP_IO_USART1_STATE_BITS ((1 << DOR1)   | (1 << FE1)    | (1 << UPE1))
#define AVRPP_IO_USART1_MODE_BITS  ((1 << UMSEL10)| (1 << UMSEL11))
#define AVRPP_IO_USART1_PARITY_BITS ((1 << UPM10)   | (1 << UPM11))

// character size bits of register B and register C
#define AVRPP_IO_USART1_CS_B_BITS  ((1 << (UCSZ12+1)))
#define AVRPP_IO_USART1_CS_C_BITS  ((1 << UCSZ11) | (1 << UCSZ10))

namespace avrpp
{
namespace io
{

enum class Usart1InterruptFlag : uint8_t
{
	RECEIVE_COMPLETE = (1 << RXC1),
	TRANSMIT_COMPLETE = (1 << TXC1),
	DATA_REGISTER_EMPTY = (1 << UDRE1)
};

enum class Usart1InterruptEnable : uint8_t
{
	RECEIVE_COMPLETE = (1 << RXCIE1),
	TRANSMIT_COMPLETE = (1 << TXCIE1),
	DATA_REGISTER_EMPTY = (1 << UDRIE1)
};

enum class Usart1StateFlag : uint8_t
{
	FRAME_ERROR =  (1 << FE1),
	DATA_OVERRUN = (1 << DOR1),
	PARITY_ERROR = (1 << UPE1)
};

enum class Usart1Mode : uint8_t
{
	ASYNCHRONOUS = 0,
	SYNCHRONOUS = (1 << UMSEL10),
	MASTER_SPI = ( 1 << UMSEL11) | (1 << UMSEL10)
};

enum class Usart1Parity : uint8_t
{
	DISABLED = 0,
	EVEN_PARITY = (1 << UPM11),
	ODD_PARITY = (1 << UPM10) | (1 << UPM11)
};

enum class Usart1StopBit : uint8_t
{
	_1_BIT = 0,
	_2_BIT = (1 << USBS1)
};

enum class Usart1CharacterSize : uint8_t
{
	_5_BIT = 0,
	_6_BIT = (1 << UCSZ10),
	_7_BIT = (1 << UCSZ11),
	_8_BIT = (1 << UCSZ11) | (1 << UCSZ10),
	_9_BIT = (1 << (UCSZ12 + 1)) | (1 << UCSZ11) | (1 << UCSZ10)
	// UCSZ12 + 1 is used because UCSZ12 has the same bit number as UCSZ11
};

class Usart1
{
  public:
	static void enableReceiver()
	{
		UCSR1B |= (1 << RXEN1);
	}

	static void disableReceiver()
	{
		UCSR1B &= ~(1 << RXEN1);
	}

	static bool isReceiverEnabled()
	{
		return UCSR1B & (1 << RXEN1);
	}

	static void enableTransmitter()
	{
		UCSR1B |= (1 << TXEN1);
	}

	static void disableTransmitter()
	{
		UCSR1B &= ~(1 << TXEN1);
	}

	static bool isTransmitterEnabled()
	{
		return UCSR1B & (1 << TXEN1);
	}

	static void enableInterrupts(
			Usart1InterruptEnable int1,
			Usart1InterruptEnable int2 = (Usart1InterruptEnable) 0,
			Usart1InterruptEnable int3 = (Usart1InterruptEnable) 0)
	{
		UCSR1B |= ((uint8_t) int1) | ((uint8_t) int2) | ((uint8_t) int3);
	}

	static void disableInterrupts(
			Usart1InterruptEnable int1,
			Usart1InterruptEnable int2 = (Usart1InterruptEnable) 0,
			Usart1InterruptEnable int3 = (Usart1InterruptEnable) 0)
	{
		UCSR1B &= ~(((uint8_t) int1) | ((uint8_t) int2) | ((uint8_t) int3));
	}

	static bool isInterruptEnabled( Usart1InterruptEnable i)
	{
		return UCSR1B & ((uint8_t) i);
	}

	static void clearInterruptFlags(
			Usart1InterruptFlag int1,
			Usart1InterruptFlag int2 = (Usart1InterruptFlag) 0,
			Usart1InterruptFlag int3 = (Usart1InterruptFlag) 0)
	{
		UCSR1A = ((UCSR1A & ~AVRPP_IO_USART1_STATE_BITS) | // USART1_STATE_BITS must always be set to zero
				(((uint8_t) int1) | ((uint8_t) int2) | ((uint8_t) int3)));
	}

	static bool isInterruptFlagSet( Usart1InterruptFlag i)
	{
		return UCSR1A & ((uint8_t) i);
	}

	static bool isStateFlagSet( Usart1StateFlag flag)
	{
		return UCSR1A |= ((uint8_t) flag);
	}

	static void enableDoubleSpeed()
	{
		UCSR1A = ((UCSR1A & ~AVRPP_IO_USART1_STATE_BITS) | (1 << U2X1)); // USART1_STATE_BITS must always be set to zero
	}

	static void disableDoubleSpeed()
	{
		UCSR1A = ((UCSR1A & ~AVRPP_IO_USART1_STATE_BITS) & ~(1 << U2X1)); // USART1_STATE_BITS must always be set to zero
	}

	static bool isDoubleSpeedEnabled()
	{
		return UCSR1A & (1 << U2X1);
	}

	static void enableMultiProcessor()
	{
		UCSR1A = ((UCSR1A & ~AVRPP_IO_USART1_STATE_BITS) | (1 << MPCM1)); // USART1_STATE_BITS must always be set to zero
	}

	static void disableMultiProcessor()
	{
		UCSR1A = ((UCSR1A & ~AVRPP_IO_USART1_STATE_BITS) & ~(1 << MPCM1)); // USART1_STATE_BITS must always be set to zero
	}

	static bool isMultiProcessorEnabled()
	{
		return UCSR1A & (1 << MPCM1);
	}

	static void setMode( Usart1Mode mode)
	{
		UCSR1C = (UCSR1C & ~AVRPP_IO_USART1_MODE_BITS) | (uint8_t) mode;
	}

	static Usart1Mode getMode()
	{
		return (Usart1Mode) (UCSR1C & AVRPP_IO_USART1_MODE_BITS);
	}

	static void setParity( Usart1Parity parity)
	{
		UCSR1C = (UCSR1C &= ~AVRPP_IO_USART1_PARITY_BITS) |= (uint8_t) parity;
	}

	static Usart1Parity getParity()
	{
		return (Usart1Parity) (UCSR1C & AVRPP_IO_USART1_PARITY_BITS);
	}

	static void setStopBit( Usart1StopBit bit)
	{
		UCSR1C = (bit == Usart1StopBit::_2_BIT ?
						(UCSR1C | (1 << USBS1)) :
						(UCSR1C & ~(1 << USBS1)));
	}

	static Usart1StopBit getStopBit()
	{
		return (Usart1StopBit) (UCSR1C & (1 << USBS1));
	}

	static void setCharacterSize( Usart1CharacterSize size)
	{
		UCSR1C = (UCSR1C & ~AVRPP_IO_USART1_CS_C_BITS) | (uint8_t) size;

		UCSR1B = ( size == Usart1CharacterSize::_9_BIT)
				? (UCSR1B | (1 << UCSZ12))
				: (UCSR1B & ~(1 << UCSZ12));
	}

	static void setClockPolarity( Edge edge)
	{
		UCSR1C = edge == Edge::RISING_EDGE ?
				(UCSR1C | (1 << UCPOL1)) :
				(UCSR1C & ~(1 << UCPOL1));
	}

	static Edge getClockPolarity()
	{
		return (UCSR1C & (1 << UCPOL1)) ?
				Edge::RISING_EDGE :
				Edge::FALLING_EDGE;
	}

	static void writeByte( uint8_t c)
	{
		UDR1 = c;
	}

	static uint8_t readByte()
	{
		return UDR1;
	}

	static void writeBaud( uint16_t baud)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // accessing 16 bit registers is not atomic
		{
			UBRR1 = baud;
		}
	}


};

}
}


#endif /* _AVRPP_IO_MXXX4_USART_H_ */
