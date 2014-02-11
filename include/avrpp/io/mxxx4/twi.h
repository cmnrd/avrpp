/**
 * @file twi.h
 *
 * @date 24.06.2012
 * @author Christian Menard
 */

#ifndef _AVRPP_IO_MXXX4_TWI_H_
#define _AVRPP_IO_MXXX4_TWI_H_

#include <avr/io.h>

#define AVRPP_IO_TWI_PRESCALER_BITS ((1 << TWPS1) | (1 << TWPS0))
#define AVRPP_IO_TWI_STATUS_BITS    ((1 << TWS7) | (1 << TWS6) | (1 << TWS5) | \
							(1 << TWS4) | (1 << TWS3))

namespace avrpp
{
namespace io
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
}

#endif /* _AVRPP_IO_MXXX4_TWI_H_ */
