/**
 * @file timer0.h
 *
 * @date 15.05.2012
 * @author Hannes Ellinger
 */

#ifndef _AVRPP_IO_MXXX4_TIMER0_H_
#define _AVRPP_IO_MXXX4_TIMER0_H_

#ifndef _AVRPP_IO_H_
#  error "Include <avrpp/io.h> instead of this file."
#endif

#include <avr/io.h>

#define AVRPP_IO_TIMER0_CS0BITS ((1 << CS00) | (1 << CS01) | (1 << CS02))
#define AVRPP_IO_TIMER0_TIF0BITS ((1 << ICF0) | (1 << OCF0A) | (1 << OCF0B) | (1 << TOV0))
#define AVRPP_IO_TIMER0_TIE0BITS ((1 << ICIE0) | (1 << OCIE0A) | (1 << OCIE0B) | (1 << TOIE0))
#define AVRPP_IO_TIMER0_OM0ABITS ((1 << COM0A1) | (1 << COM0A0))
#define AVRPP_IO_TIMER0_OM0BBITS ((1 << COM0B1) | (1 << COM0B0))
#define AVRPP_IO_TIMER0_WGM0ABITS ((1 << WGM00) | (1 << WGM01))
#define AVRPP_IO_TIMER0_WGM0BBITS (1 << WGM02)
#define AVRPP_IO_TIMER0_WGM0BITS (WGM1ABITS | WGM1BBITS)

namespace avrpp
{
namespace io
{

enum class Timer0InterruptFlag : uint8_t
{
	COMPARE_MATCH_A = (1 << OCF0A),
	COMPARE_MATCH_B	= (1 << OCF0B),
	OVERFLOW		= (1 << TOV0)
};

enum class Timer0InterruptEnable : uint8_t
{
	COMPARE_MATCH_A = (1 << OCIE0A),
	COMPARE_MATCH_B	= (1 << OCIE0B),
	OVERFLOW		= (1 << TOIE0)
};

enum class ClockSource0 : uint8_t
{
	PRESCALER_1				= (1 << CS00),
	PRESCALER_8				= (1 << CS01),
	PRESCALER_64			= (1 << CS01) | (1 << CS00),
	PRESCALER_256 			= (1 << CS02),
	PRESCALER_1024			= (1 << CS02) | (1 << CS00),
	EXTERNAL_FALLING_EDGE	= (1 << CS02) | (1 << CS01),
	EXTERNAL_RISING_EDGE	= (1 << CS02) | (1 << CS01) | (1 << CS00)
};

enum class OutputMode0A : uint8_t
{
	NORMAL = 0,
	TOGGLE = (1 << COM0A0),
	CLEAR  = (1 << COM0A1),
	SET    = (1 << COM0A1) | (1 << COM0A0)
};

enum class OutputMode0B : uint8_t
{
	NORMAL = 0,
	TOGGLE = (1 << COM0B0),
	CLEAR  = (1 << COM0B1),
	SET    = (1 << COM0B1) | (1 << COM0B0)
};

enum class Waveform0 : uint8_t
{
	NORMAl									= 0,
	PHASE_CORRECT_PWM						= (1 << WGM00),
	CLEAR_TIMER_ON_COMPARE_MATCH			= (1 << WGM01),
	FAST_PWM								= (1 << WGM00) | (1 << WGM01),
	PHASE_CORRECT_PWM_OCR0A					= (1 << WGM02) | (1 << WGM00),
	FAST_PWM_OCR0A 							= (1 << WGM02) | (1 << WGM01) | (1 << WGM00)
};

class Timer0
{
  public:
	static void disable()
	{
		TCCR0B &= ~AVRPP_IO_TIMER0_CS0BITS;
	}

	static void enable( ClockSource0 cs)
	{
		TCCR0B = (TCCR0B &= ~AVRPP_IO_TIMER0_CS0BITS) | (uint8_t) cs;
	}

	static bool isEnabled()
	{
		return TCCR0B & AVRPP_IO_TIMER0_CS0BITS;
	}

	static ClockSource0 getClockSource()
	{
		return (ClockSource0) (TCCR0B  & (AVRPP_IO_TIMER0_CS0BITS));
	}

	static void clearInterruptFlags(
			Timer0InterruptFlag flag1,
			Timer0InterruptFlag flag2 = (Timer0InterruptFlag) 0,
			Timer0InterruptFlag flag3 = (Timer0InterruptFlag) 0,
			Timer0InterruptFlag flag4 = (Timer0InterruptFlag) 0)
	{
		TIFR0 |= ((uint8_t) flag1) | ((uint8_t) flag2) |
						  ((uint8_t) flag3) | ((uint8_t) flag3);
	}

	static bool isInterruptFlagSet( Timer0InterruptFlag flag)
	{
		return TIFR0 & ((uint8_t) flag);
	}

	static void enableInterrupts(
			Timer0InterruptEnable int1,
			Timer0InterruptEnable int2 = (Timer0InterruptEnable) 0,
			Timer0InterruptEnable int3 = (Timer0InterruptEnable) 0)
	{
		TIMSK1 |= ((uint8_t) int1) | ((uint8_t) int2) |
				  ((uint8_t) int3);
	}

	static void disableInterrupts(
			Timer0InterruptEnable int1,
			Timer0InterruptEnable int2 = (Timer0InterruptEnable) 0,
			Timer0InterruptEnable int3 = (Timer0InterruptEnable) 0)
	{
		TIMSK0 &= ~(((uint8_t) int1) | ((uint8_t) int2) |
				   ((uint8_t) int3));
	}

	static bool isInterruptEnabled( Timer0InterruptEnable i)
	{
		return TIMSK0 & ((uint8_t) i);
	}

	static void setOutputModeA( OutputMode0A mode)
	{
		TCCR0A = (TCCR0A & ~AVRPP_IO_TIMER0_OM0ABITS) | (uint8_t) mode;
	}

	static void setOutputModeB( OutputMode0B mode)
	{
		TCCR0A = (TCCR0A & ~AVRPP_IO_TIMER0_OM0BBITS) | (uint8_t) mode;
	}

	static OutputMode0A getOutputModeA()
	{
		return (OutputMode0A) (TCCR0A & AVRPP_IO_TIMER0_OM0ABITS);
	}

	static OutputMode0B getOutputModeB()
	{
		return (OutputMode0B) (TCCR0A & AVRPP_IO_TIMER0_OM0BBITS);
	}

	static void setWaveform( Waveform0 wf)
	{
		TCCR0A = (TCCR0A & ~AVRPP_IO_TIMER0_WGM0ABITS) | (((uint8_t) wf) & AVRPP_IO_TIMER0_WGM0ABITS);
		TCCR0B = (TCCR0B & ~AVRPP_IO_TIMER0_WGM0BBITS) | (((uint8_t) wf) & AVRPP_IO_TIMER0_WGM0BBITS);
	}

	static Waveform0 getWaveform()
	{
		return (Waveform0) ((TCCR0A & AVRPP_IO_TIMER0_WGM0ABITS) | (TCCR0B & AVRPP_IO_TIMER0_WGM0BBITS));
	}

	static void writeCounter( uint8_t v)
	{
		TCNT0 = v;
	}

	static uint8_t readCounter()
	{
		return TCNT0;
	}

	static void writeCompareA( uint8_t v)
	{
		OCR0A = v;
	}

	static void writeCompareB( uint8_t v)
	{
		OCR0B = v;
	}

	static uint8_t readCompareA()
	{
		return OCR0A;
	}

	static uint8_t readCompareB()
	{
		return OCR0B;
	}

};

}
}

#endif
