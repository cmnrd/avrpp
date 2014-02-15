/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Christian Menard, Hannes Ellinger
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

#ifndef _AVRPP_IO_MXXX4_ADC_H_
#define _AVRPP_IO_MXXX4_ADC_H_

#ifndef _AVRPP_IO_H_
#  error "Include <avrpp/io.h> instead of this file."
#endif

#include <avr/io.h>
#include <util/atomic.h>

#define AVRPP_IO_ADC_REFERENCE_BITS ((1 << REFS0) | (1 << REFS1))
#define AVRPP_IO_ADC_CHANNEL_BITS   ((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4))
#define AVRPP_IO_ADC_PRESCALER_BITS ((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2))
#define AVRPP_IO_ADC_AUTOTRIGGER_SOURCE_BITS ((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0))

namespace avrpp
{
namespace io
{

	enum class AdcReference : uint8_t
	{
		AREF  = 0,
		AVCC  = (1 << REFS0),
		_1_1V = (1 << REFS1),
		_2_56V = (1 << REFS0) | (1 << REFS1)
	};

	enum class AdcChannel : uint8_t
	{
		ADC0,
		ADC1,
		ADC2,
		ADC3,
		ADC4,
		ADC5,
		ADC6,
		ADC7,
		ADC0_0_10X,
		ADC1_0_10X,
		ADC0_0_200X,
		ADC1_0_200X,
		ADC2_2_10X,
		ADC3_2_10X,
		ADC2_2_200X,
		ADC3_2_200X,
		ADC0_1_1X,
		ADC1_1_1X,
		ADC2_1_1X,
		ADC3_1_1X,
		ADC4_1_1X,
		ADC5_1_1X,
		ADC6_1_1X,
		ADC7_1_1X,
		ADC0_2_1X,
		ADC1_2_1X,
		ADC2_2_1X,
		ADC3_2_1X,
		ADC4_2_1X,
		ADC5_2_1X,
		_1_1V,
		GND
	};

	enum class AdcPrescaler : uint8_t
	{
		PRESCALER_2    = 0,
		PRESCALER_4	   = (1 << ADPS1),
		PRESCALER_8	   = (1 << ADPS1) | (1 << ADPS0),
		PRESCALER_16   = (1 << ADPS2),
		PRESCALER_32   = (1 << ADPS2) | (1 << ADPS0),
		PRESCALER_64   = (1 << ADPS2) | (1 << ADPS1),
		PRESCALER_128  = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)
	};

	enum class AdcAutoTriggerSource : uint8_t
	{
		FREE_RUNNING_MODE = 0,
		ANALOG_COMPERATOR = (1 << ADTS0),
		EXTERNAL_INTERRUPT_REQUEST0 = (1 << ADTS1),
		TIMER0_COMPARE_MATCH_A = (1 << ADTS1) | (1 << ADTS0),
		TIMER0_OVERFLOW = (1 << ADTS2),
		TIMER1_COMPARE_MATCH_B = (1 << ADTS2) | (1 << ADTS0),
		TIMER1_OVERFLOW = (1 << ADTS2) | (1 << ADTS1),
		TIMER1_CAPTURE_EVENT = (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0)
	};

class ADConverter
{
  public:


	static AdcReference getReference()
	{
		return (AdcReference) (ADMUX & AVRPP_IO_ADC_REFERENCE_BITS);
	}

	static void setReference( AdcReference ref)
	{
		ADMUX = (ADMUX & ~AVRPP_IO_ADC_REFERENCE_BITS) | (uint8_t) ref;
	}

	static void leftAdjust()
	{
		ADMUX |= (1 << ADLAR);
	}

	static void rightAdjust()
	{
		ADMUX &= ~(1 << ADLAR);
	}

	static bool isLeftAdjusted()
	{
		return ADMUX & (1 << ADLAR);
	}

	static void setChannel( AdcChannel channel)
	{
		ADMUX = (ADMUX & ~AVRPP_IO_ADC_CHANNEL_BITS) | (uint8_t) channel;
	}

	static AdcChannel getChannel()
	{
		return (AdcChannel) (ADMUX & AVRPP_IO_ADC_CHANNEL_BITS);
	}

	static void enable()
	{
		ADCSRA |= (1 << ADEN);
	}

	static void disable()
	{
		ADCSRA &= ~(1 << ADEN);
	}

	static bool isEnabled()
	{
		return ADCSRA & (1 << ADEN);
	}

	static void startConversion()
	{
		ADCSRA |= (1 << ADSC);
	}

	static void enableAutoTrigger() { ADCSRA |= (1 << ADATE); }

	static void disableAutoTrigger() { ADCSRA &= ~(1 << ADATE); }

	static bool isAutoTriggerEnabled()
	{
		return ADCSRA & (1 << ADATE);
	}

	static void clearInterruptFlag()
	{
		ADCSRA |= (1 << ADIF);
	}

	static bool getInterruptFlag()
	{
		return ADCSRA & (1 << ADIF);
	}

	static bool isInterruptEnabled()
	{
		return ADCSRA & (1 << ADIE);
	}

	static void enableInterrupt()
	{
		ADCSRA |= (1 << ADIE);
	}

	static void disableInterrupt()
	{
		ADCSRA &= ~(1 << ADIE);
	}

	static void setPrescaler( AdcPrescaler prescaler)
	{
		ADCSRA = (ADCSRA & ~AVRPP_IO_ADC_PRESCALER_BITS) | (uint8_t) prescaler;
	}

	static AdcPrescaler getPrescaler()
	{
		return (AdcPrescaler) (ADCSRA & AVRPP_IO_ADC_PRESCALER_BITS);
	}

	static uint16_t readValue()
	{
		uint16_t tmp;

		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // accessing 16 bit registers is not atomic
		{
			tmp = ADC;
		}

		return tmp;
	}

	static void setAutoTriggerSource( AdcAutoTriggerSource src)
	{
		ADCSRB = (ADCSRB & ~AVRPP_IO_ADC_AUTOTRIGGER_SOURCE_BITS) | (uint8_t) src;
	}

	static AdcAutoTriggerSource getAutoTriggerSource()
	{
		return ((AdcAutoTriggerSource) (ADCSRB & AVRPP_IO_ADC_AUTOTRIGGER_SOURCE_BITS)) ;
	}
};

}
}


#endif /* _AVRPP_IO_MXXX4_ADC_H_ */
