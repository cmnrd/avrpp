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

#ifndef _AVRPP_IO_MXXX4_TWI_H_
#define _AVRPP_IO_MXXX4_TWI_H_

#ifndef _AVRPP_IO_H_
#  error "Include <avrpp/io.h> instead of this file."
#endif

#include <avr/io.h>

#define AVRPP_IO_TWI_PRESCALER_BITS ((1 << TWPS1) | (1 << TWPS0))
#define AVRPP_IO_TWI_STATUS_BITS    ((1 << TWS7) | (1 << TWS6) | (1 << TWS5) | \
							(1 << TWS4) | (1 << TWS3))

namespace avrpp
{

enum class TwiPrescaler : uint8_t
{
	PRESCALER_1 = 0,
	PRESCALER_4 = (1 << TWPS0),
	PRESCALER_16 = (1 << TWPS1),
	PRESCALER_64 = (1 << TWPS1) | (1 << TWPS0),
};

class Twi
{
  public:

	static void setBitRate( uint8_t rate)
	{
		TWBR = rate;
	}

	static uint8_t getBitRate()
	{
		return TWBR;
	}

	static void setPrescaler( TwiPrescaler prescaler)
	{
		TWSR = (TWSR & ~AVRPP_IO_TWI_PRESCALER_BITS) | (uint8_t) prescaler;
	}

	static TwiPrescaler getPrescaler()
	{
		return (TwiPrescaler) (TWSR & AVRPP_IO_TWI_PRESCALER_BITS);
	}

	static uint8_t getStatus()
	{
		return TWSR & AVRPP_IO_TWI_STATUS_BITS;
	}

	static void setStatus( uint8_t status)
	{
		TWSR = status & AVRPP_IO_TWI_STATUS_BITS;
	}

	static uint8_t readByte()
	{
		return TWDR;
	}

	static void writeByte(uint8_t byte)
	{
		TWDR = byte;
	}

	static void writeControlRegister( uint8_t byte)
	{
		TWCR = byte;
	}

};

}

#endif /* _AVRPP_IO_MXXX4_TWI_H_ */
