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

#ifndef _AVRPP_DRIVER_ADCREADER_H_
#define _AVRPP_DRIVER_ADCREADER_H_

#include <avr/interrupt.h>
#include <avrpp/io.h>

ISR(ADC_vect);

namespace avrpp
{
namespace driver
{

	class AdcReader
	{
	  friend void (::ADC_vect) (); // Allow ISR to access private elements

	  private:
		static volatile uint16_t values[8];
		static volatile uint8_t updatedFlags;

	  public:
		static void init() // TODO let user choose the prescaler
		{
			// Enable and set prescaler to 16 (125kHz)
			io::ADConverter::setPrescaler(io::AdcPrescaler::PRESCALER_16);
			io::ADConverter::enable();
			io::ADConverter::enableInterrupt();

			// Start a first conversion to trigger ISR
			io::ADConverter::setChannel(io::AdcChannel::ADC0);
			io::ADConverter::startConversion();
		}

		static uint16_t getValue( uint8_t channel)
		{
			return values[channel];
		}

		static bool isUpdatedFlagSet( uint8_t channel)
		{
			return updatedFlags & (1 << channel);
		}

		static void clearUpdatedFlag( uint8_t channel)
		{
			updatedFlags &= ~(1 << channel);
		}
	};
}
}


#endif /* _AVRPP_DRIVER_ADCREADER_H_ */
