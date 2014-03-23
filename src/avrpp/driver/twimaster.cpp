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

#include <avrpp/driver/twimaster.h>
using namespace avrpp;
using namespace avrpp::driver;
using namespace avrpp::io;
using namespace avrpp::util;


Buffer<uint8_t, TWI_TRANSMIT_BUFFER_SIZE> TwiMaster::transmitBuffer = Buffer<uint8_t, TWI_TRANSMIT_BUFFER_SIZE>();

volatile bool TwiMaster::transmissionFinished = true;

ISR(TWI_vect)
{

	static uint8_t frameSize = 0;
	static uint8_t pos = 0;
	static uint8_t currentByte = 0;

	uint8_t state = Twi::getStatus();

	switch( state)
	{
	case 0x08: // start condition has been transmitted
		// -> send address

		// pop the frame size so the address can be accessed
		frameSize = TwiMaster::transmitBuffer.pop();

		currentByte = TwiMaster::transmitBuffer.pop();
		TwiMaster::writeByte( currentByte);
		break;
	case 0x10: // repeated start condition has been transmitted
		// -> send last byte again
		TwiMaster::writeByte( currentByte);
		break;
	case 0x18: // address has been transmitted and ACK has been received
		// -> send data

		currentByte = TwiMaster::transmitBuffer.pop();

		TwiMaster::writeByte( currentByte);
		pos = 1;
		break;
	case 0x28: // data byte has been transmitted and ACK has been received
		// -> send more data or a stop condition;

		if( pos < frameSize) // is there data to be send
		{
			currentByte = TwiMaster::transmitBuffer.pop();

			TwiMaster::writeByte( currentByte);
			pos++;
		}
		else // send stop condition or restart if there is a new frame to be send
		{
			if( TwiMaster::transmitBuffer.isEmpty())
			{
				// there is not another frame to be send -> send stop condition
				TwiMaster::stop();
				TwiMaster::transmissionFinished = true;
			}
			// check if a whole frame is in the buffer
			else if (TwiMaster::transmitBuffer.peek() + 2 <= TwiMaster::transmitBuffer.count() )
			{
				TwiMaster::restart();
			}
			else
			{
				// there is not a whole frame in buffer -> send stop condition, restart after frame completed
				TwiMaster::stop();
				TwiMaster::transmissionFinished = true;
			}
		}

		break;
	default: // There was an error -> send last byte again
		TwiMaster::start();
		break;
	}
}




