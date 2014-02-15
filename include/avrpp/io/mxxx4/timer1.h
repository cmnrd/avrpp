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

#ifndef _AVRPP_IO_MXXX4_TIMER1_H_
#define _AVRPP_IO_MXXX4_TIMER1_H_

#ifndef _AVRPP_IO_H_
#  error "Include <avrpp/io.h> instead of this file."
#endif

#include <avr/io.h>
#include <util/atomic.h>
#include <avrpp/io/edge.h>

#define AVRPP_IO_TIMER1_CS1BITS ((1 << CS10) | (1 << CS11) | (1 << CS12))
#define AVRPP_IO_TIMER1_TIF1BITS ((1 << ICF1) | (1 << OCF1A) | (1 << OCF1B) | (1 << TOV1))
#define AVRPP_IO_TIMER1_TIE1BITS ((1 << ICIE1) | (1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1))
#define AVRPP_IO_TIMER1_OM1ABITS ((1 << COM1A1) | (1 << COM1A0))
#define AVRPP_IO_TIMER1_OM1BBITS ((1 << COM1B1) | (1 << COM1B0))
#define AVRPP_IO_TIMER1_WGM1ABITS ((1 << WGM10) | (1 << WGM11))
#define AVRPP_IO_TIMER1_WGM1BBITS ((1 << WGM12) | (1 << WGM13))
#define AVRPP_IO_TIMER1_WGM1BITS (WGM1ABITS | WGM1BBITS)

namespace avrpp
{
namespace io
{
enum class Timer1InterruptFlag : uint8_t
{
	INPUT_CAPTURE 	= (1 << ICF1),
	COMPARE_MATCH_A = (1 << OCF1A),
	COMPARE_MATCH_B	= (1 << OCF1B),
	OVERFLOW		= (1 << TOV1)
};

enum class Timer1InterruptEnable : uint8_t
{
	INPUT_CAPTURE 	= (1 << ICIE1),
	COMPARE_MATCH_A = (1 << OCIE1A),
	COMPARE_MATCH_B	= (1 << OCIE1B),
	OVERFLOW		= (1 << TOIE1)
};

enum class ClockSource1 : uint8_t
{
	PRESCALER_1				= (1 << CS10),
	PRESCALER_8				= (1 << CS11),
	PRESCALER_64			= (1 << CS11) | (1 << CS10),
	PRESCALER_256 			= (1 << CS12),
	PRESCALER_1024			= (1 << CS12) | (1 << CS10),
	EXTERNAL_FALLING_EDGE	= (1 << CS12) | (1 << CS11),
	EXTERNAL_RISING_EDGE	= (1 << CS12) | (1 << CS11) | (1 << CS10)
};

enum class OutputMode1A : uint8_t
{
	NORMAL = 0,
	TOGGLE = (1 << COM1A0),
	CLEAR  = (1 << COM1A1),
	SET    = (1 << COM1A1) | (1 << COM1A0)
};

enum class OutputMode1B : uint8_t
{
	NORMAL = 0,
	TOGGLE = (1 << COM1B0),
	CLEAR  = (1 << COM1B1),
	SET    = (1 << COM1B1) | (1 << COM1B0)
};

enum class Waveform1 : uint8_t
{
	NORMAl									= 0,
	PHASE_CORRECT_PWM_8BIT					= (1 << WGM10),
	PHASE_CORRECT_PWM_9BIT					= (1 << WGM11),
	PHASE_CORRECT_PWM_10BIT					= (1 << WGM11) | (1 << WGM10),
	CLEAR_TIMER_ON_COMPARE_MATCH_OCR1A		= (1 << WGM12),
	FAST_PWM_8BIT							= (1 << WGM12) | (1 << WGM10),
	FAST_PWM_9BIT							= (1 << WGM12) | (1 << WGM11),
	FAST_PWM_10BIT							= (1 << WGM12) | (1 << WGM11) |
											  (1 << WGM10),
	PHASE_AND_FREQUENCY_CORRECT_PWM_ICR1	= (1 << WGM13),
	PHASE_AND_FREQUENCY_CORRECT_PWM_OCR1A	= (1 << WGM13) | (1 << WGM10),
	PHASE_CORRECT_PWM_ICR1					= (1 << WGM13) | (1 << WGM11),
	PHASE_CORRECT_PWM_OCR1A					= (1 << WGM13) | (1 << WGM11) |
											  (1 << WGM10),
	CLEAR_TIMER_ON_COMPARE_MATCH_ICR1		= (1 << WGM13) | (1 << WGM12),
	FAST_PWM_ICR1 							= (1 << WGM13) | (1 << WGM12) |
											  (1 << WGM11),
	FAST_PWM_OCR1A 							= (1 << WGM13) | (1 << WGM12) |
											  (1 << WGM11) | (1 << WGM10)
};

class Timer1
{
  public:
	static void disable()
	{
		TCCR1B &= ~AVRPP_IO_TIMER1_CS1BITS;
	}

	static void enable( ClockSource1 cs)
	{
		TCCR1B = (TCCR1B & ~AVRPP_IO_TIMER1_CS1BITS) | (uint8_t) cs;
	}

	static bool isEnabled()
	{
		return TCCR1B & AVRPP_IO_TIMER1_CS1BITS;
	}

	static ClockSource1 getClockSource()
	{
		return (ClockSource1) (TCCR1B  & (AVRPP_IO_TIMER1_CS1BITS));
	}

	static void clearInterruptFlags(
			Timer1InterruptFlag flag1,
			Timer1InterruptFlag flag2 = (Timer1InterruptFlag) 0,
			Timer1InterruptFlag flag3 = (Timer1InterruptFlag) 0,
			Timer1InterruptFlag flag4 = (Timer1InterruptFlag) 0)
	{
		TIFR1 |= ((uint8_t) flag1) | ((uint8_t) flag2) |
						  ((uint8_t) flag3) | ((uint8_t) flag3);
	}

	static bool isInterruptFlagSet( Timer1InterruptFlag flag)
	{
		return TIFR1 & ((uint8_t) flag);
	}

	static void enableInterrupts(
			Timer1InterruptEnable int1,
			Timer1InterruptEnable int2 = (Timer1InterruptEnable) 0,
			Timer1InterruptEnable int3 = (Timer1InterruptEnable) 0,
			Timer1InterruptEnable int4 = (Timer1InterruptEnable) 0)
	{
		TIMSK1 |= ((uint8_t) int1) | ((uint8_t) int2) |
				  ((uint8_t) int3) | ((uint8_t) int4);
	}

	static void disableInterrupts(
			Timer1InterruptEnable int1,
			Timer1InterruptEnable int2 = (Timer1InterruptEnable) 0,
			Timer1InterruptEnable int3 = (Timer1InterruptEnable) 0,
			Timer1InterruptEnable int4 = (Timer1InterruptEnable) 0)
	{
		TIMSK1 &= ~(((uint8_t) int1) | ((uint8_t) int2) |
				   ((uint8_t) int3) | ((uint8_t) int4));
	}

	static bool isInterruptEnabled( Timer1InterruptEnable i)
	{
		return TIMSK1 & ((uint8_t) i);
	}

	static void setOutputModeA( OutputMode1A mode)
	{
		TCCR1A = (TCCR1A & ~AVRPP_IO_TIMER1_OM1ABITS) | (uint8_t) mode;
	}

	static void setOutputModeB( OutputMode1B mode)
	{
		TCCR1A = (TCCR1A & ~AVRPP_IO_TIMER1_OM1BBITS) | ((uint8_t) mode);
	}

	static OutputMode1A getOutputModeA()
	{
		return (OutputMode1A) (TCCR1A & AVRPP_IO_TIMER1_OM1ABITS);
	}

	static OutputMode1B getOutputModeB()
	{
		return (OutputMode1B) (TCCR1A & AVRPP_IO_TIMER1_OM1BBITS);
	}

	static void setWaveform( Waveform1 wf)
	{
		TCCR1A = (TCCR1A & ~AVRPP_IO_TIMER1_WGM1ABITS) | (((uint8_t) wf) & AVRPP_IO_TIMER1_WGM1ABITS);
		TCCR1B = (TCCR1B & ~AVRPP_IO_TIMER1_WGM1BBITS) | (((uint8_t) wf) & AVRPP_IO_TIMER1_WGM1BBITS);
	}

	static Waveform1 getWaveform()
	{
		return (Waveform1) ((TCCR1A & AVRPP_IO_TIMER1_WGM1ABITS) | (TCCR1B & AVRPP_IO_TIMER1_WGM1BBITS));
	}

	static void enableNoiseCanceler()
	{
		TCCR1B |= (1 << ICNC1);
	}

	static void disableNoiseCanceler()
	{
		TCCR1B &= ~(1 << ICNC1);
	}

	static bool isNoiseCancelerEnabled()
	{
		return TCCR1B & (1 << ICNC1);
	}

	static void setInputCaptureEdge( Edge e)
	{
		TCCR1B = (e == Edge::FALLING_EDGE) ?
					(TCCR1B & ~(1 << ICES1)) :
					(TCCR1B) | (1 << ICES1);
	}

	static Edge getInputCaptureEdge()
	{
		return (TCCR1B & (1 << ICES1)) ? Edge::RISING_EDGE : Edge::FALLING_EDGE;
	}

	static void writeCounter( uint16_t v)
	{
		ATOMIC_BLOCK(ATOMIC_FORCEON) // accessing 16 bit registers is not atomic
		{
			TCNT1 = v;
		}
	}

	static uint16_t readCounter()
	{
		uint16_t tmp;

		ATOMIC_BLOCK(ATOMIC_FORCEON) // accessing 16 bit registers is not atomic
		{
			tmp = TCNT1;
		}

		return tmp;
	}

	static void writeCompareA( uint16_t v)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // accessing 16 bit registers is not atomic
		{
			OCR1A = v;
		}
	}

	static void writeCompareB( uint16_t v)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // accessing 16 bit registers is not atomic
		{
			OCR1B = v;
		}
	}

	static uint16_t readCompareA()
	{
		uint16_t tmp;

		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // accessing 16 bit registers is not atomic
		{
			tmp = OCR1A;
		}

		return tmp;
	}

	static uint16_t readCompareB()
	{
		uint16_t tmp;

		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // accessing 16 bit registers is not atomic
		{
			tmp = OCR1B;
		}

		return tmp;
	}

	static uint16_t readCapture()
	{
		uint16_t tmp;

		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // accessing 16 bit registers is not atomic
		{
			tmp = ICR1;
		}

		return tmp;
	}

	static void writeCapture(uint16_t v)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) // accessing 16 bit registers is not atomic
		{
			ICR1 = v;
		}
	}

};

}
}

#endif // _AVRPP_IO_MXXX4_TIMER1_H
