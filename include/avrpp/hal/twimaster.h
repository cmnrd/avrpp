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

#ifndef _AVRPP_HAL_TWISTREAM_H_
#define _AVRPP_HAL_TWISTREAM_H_

#include <avrpp/util/buffer.h>
#include <avrpp/config.h>
#include <avrpp/io.h>
#include <avr/interrupt.h>

ISR(TWI_vect);

namespace avrpp
{

class TwiMaster
{
	friend void (::TWI_vect) (); // Allow ISR to access private elements

private:
	static volatile bool transmissionFinished;
	static Buffer<uint8_t, TWI_TRANSMIT_BUFFER_SIZE> transmitBuffer;

	static void start()
	{
		Twi::writeControlRegister(
			(1 << TWEN)    // enable TWI
		  | (1 << TWINT)   // clear TWI interrupt flag
		  | (1 << TWIE)    // enable TWI interrupt
		  | (1 << TWSTA)); // Send start condition
	}

	static void stop()
	{
		Twi::writeControlRegister(
			(1 << TWEN) 	// enable TWI
		  | (1 << TWINT)	// clear TWI interrupt flag and disable TWI interrupt
		  | (1 << TWSTO));	// send stop condition
	}

	static void restart()
	{
		Twi::writeControlRegister(
		    (1 << TWEN)   // enable TWI
		  | (1 << TWINT)  // clear TWI interrupt flag
		  | (1 << TWIE)   // enable TWI interrupt
		  | (1 << TWSTA)  // Send start condition
		  | (1 << TWSTO)); // Send stop condition
	}

	static void writeByte( uint8_t byte)
	{
		Twi::writeByte(byte);
		Twi::writeControlRegister(
		    (1 << TWEN)	// enable TWI
		  | (1 << TWINT)	// clear TWI interrupt flag
		  | (1 << TWIE));  // enable TWI interrupt
	}

public:

	static void init()
	{
		// SDL and SDA are outputs
		DDRC |= (1 << PC0) | (1 << PC1); // TODO replace by some global macros

		Twi::setStatus(0);
		Twi::setBitRate(((F_CPU / SCL_CLOCK) - 16) / 2); // TODO replace by some global macros // see the Datasheet for an explanation of the equation
	}

	static void sendByte( uint8_t address, uint8_t byte)
	{
		// push frame size
		transmitBuffer.push(1); // just one byte is send

		// push address
		transmitBuffer.push( (address << 1)); // Address has to be shifted by 1 (bit 0 is the read/write flag)

		// push data
		transmitBuffer.push(byte);

		if( transmissionFinished)  // send a start condition to start twi operation
		{
			transmissionFinished = false;
			start();
		}
	}

	static void sendFrame( uint8_t address, uint8_t byte[], uint8_t frameSize)
	{
		// push frame size
		transmitBuffer.push(frameSize);

		// push address
		transmitBuffer.push( (address << 1)); // Address has to be shifted by 1 (bit 0 is the read/write flag)

		// push data
		for( int i = 0; i < frameSize; i++)
			transmitBuffer.push(byte[i]);

		if( transmissionFinished)  // send a start condition to start twi operation
		{
			transmissionFinished = false;
			start();
		}
	}

};
}


#endif /* _AVRPP_HAL_TWISTREAM_H_ */
