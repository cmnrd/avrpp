/**
 * @file timer2.h
 *
 * @date 22.03.2012
 * @author Stefan Engert
 */

#ifndef __AVRPP_IO_MXXX4TIMER2_H_
#define __AVRPP_IO_MXXX4TIMER2_H_

#include <avr/io.h>

#define AVRPP_IO_TIMER2_CS2BITS ((1 << CS20 ) | (1 << CS21) | (1 << CS22))
#define AVRPP_IO_TIMER2_OM2ABITS ((1 << COM2A1) | (1 << COM2A0))
#define AVRPP_IO_TIMER2_OM2BBITS ((1 << COM2B1) | (1 << COM2B0))
#define AVRPP_IO_TIMER2_WGM2ABITS ((1 << WGM21) | (1 << WGM20))
#define AVRPP_IO_TIMER2_WGM2BBITS (1 << WGM22)

namespace avrpp
{
namespace io
{

enum class OutputMode2A : uint8_t
{
	NORMAL 		= 0,
	TOGGLE		= (1 << COM2A0),
	CLEAR 		= (1<< COM2A1),
	SET 		= (1<< COM2A1 ) | (1<< COM2A0)
};

enum class OutputMode2B : uint8_t
{
	NORMAL		= 0,
	TOGGLE 		= (1 << COM2B0),
	CLEAR 		= (1<< COM2B1),
	SET 		= (1<< COM2B1 ) | (1<< COM2B0)
};

enum class Waveform2 :uint8_t
{
	NORMAL 							= 0,
	PHASE_CORRECT_PWM 				= (1 << WGM20),
	CLEAR_TIMER_ON_COMPARE_MATCH 	= (1 << WGM21),
	FAST_PWM 						= (1 << WGM21 ) | (1 << WGM20),
	PHASE_CORRECT_PWM_OCR2A			= (1 << WGM22) | (1 << WGM20),
	FAST_PWM_OCR2A					= (1 << WGM22) | (1 << WGM20) | (1 << WGM21)
};

enum class ClockSource2 : uint8_t
{
	PRESCALER_1 				= (1 << CS20),
	PRECSALER_8					= (1 << CS21),
	PRECSALER_32 				= (1 << CS21) | (1 << CS20),
	PRESCALER_64				= (1 << CS22),
	PRESCALER_128				= (1 << CS22) | (1 << CS20),
	PRESCALER_256 				= (1 << CS22) | (1 << CS21),
	PRESCALER_1024 				= (1 << CS22) | (1 << CS21) | (1 << CS20)
};

enum class Timer2InterruptFlag : uint8_t
{
	COMPARE_MATCH_B			= (1 << OCF2B),
	COMPARE_MATCH_A			= (1 << OCF2A),
	OVERFLOW 				= (1 << TOV2)
};

enum class Timer2InterruptEnable : uint8_t
{
	COMPARE_MATCH_B 			= (1<< OCIE2B),
	COMPARE_MATCH_A				= (1<< OCIE2A),
	OVERFLOW 					= (1<< TOIE2)
};

class Timer2
{
	public:
		static void disable()
		{
			TCCR2B &= ~AVRPP_IO_TIMER2_CS2BITS;
		}

		static void enable(ClockSource2 cs)
		{
			TCCR2B = (TCCR2B & ~AVRPP_IO_TIMER2_CS2BITS) | (uint8_t) cs;
		}

		static bool isEnabled()
		{
			return TCCR2B & AVRPP_IO_TIMER2_CS2BITS;
		}

		static ClockSource2 getClockSource()
		{
			return (ClockSource2) (TCCR2B & AVRPP_IO_TIMER2_CS2BITS);
		}

		static void clearInterruptFlags(
				Timer2InterruptFlag flag1,
				Timer2InterruptFlag flag2 = (Timer2InterruptFlag) 0,
				Timer2InterruptFlag flag3 = (Timer2InterruptFlag) 0)
		{
			TIFR2 |= ((uint8_t) flag1) | ((uint8_t) flag2 ) | ((uint8_t) flag3 );
		}

		static bool isInerruptFlagSet (Timer2InterruptFlag flag )
		{
			return TIFR2 &((uint8_t) flag );
		}

		static void enableInterrupts(
			Timer2InterruptEnable int1,
			Timer2InterruptEnable int2 = (Timer2InterruptEnable) 0,
			Timer2InterruptEnable int3 = (Timer2InterruptEnable) 0)
		{
			TIMSK2 |= ((uint8_t) int1) | ((uint8_t) int2) |
					  ((uint8_t) int3);
		}

		static void disableInterrupts(
			Timer2InterruptEnable int1,
			Timer2InterruptEnable int2 = (Timer2InterruptEnable) 0,
			Timer2InterruptEnable int3 = (Timer2InterruptEnable) 0)
		{
			TIMSK2 &= ~(((uint8_t) int1) | ((uint8_t) int2) |
							   ((uint8_t) int3));
		}

		static bool isInterruptEnabled (Timer2InterruptEnable i)
		{
			return TIMSK2 & ((uint8_t) i);
		}

		static void setOutputModeA( OutputMode2A mode)
		{
			TCCR2A = (TCCR2A & ~AVRPP_IO_TIMER2_OM2ABITS) & ~((uint8_t) mode );
		}

		static void setOutputModeB( OutputMode2B mode)
		{
			TCCR2B = (TCCR2B & ~AVRPP_IO_TIMER2_OM2BBITS) & ~((uint8_t) mode );
		}

		static OutputMode2A getOutputModeA()
		{
			return (OutputMode2A) (TCCR2A & AVRPP_IO_TIMER2_OM2ABITS);
		}

		static OutputMode2B getOutputModeB()
		{
			return (OutputMode2B) (TCCR2B & AVRPP_IO_TIMER2_OM2BBITS);
		}

		static void setWaveform (Waveform2 wf)
		{
			TCCR2A = (TCCR2A & ~AVRPP_IO_TIMER2_WGM2ABITS) | (((uint8_t) wf) & AVRPP_IO_TIMER2_WGM2ABITS);
			TCCR2B = (TCCR2B & ~AVRPP_IO_TIMER2_WGM2BBITS) | (((uint8_t) wf) & AVRPP_IO_TIMER2_WGM2BBITS);
		}

		static Waveform2 getWaveform ()
		{
			return (Waveform2)((TCCR2A & AVRPP_IO_TIMER2_WGM2ABITS) | (TCCR2B & AVRPP_IO_TIMER2_WGM2BBITS));
		}

		static void writeCounter( uint8_t v)
		{
			TCNT2 = v;
		}

		static uint8_t readCounter()
		{
			return TCNT2;
		}

		static void writeCompareA( uint8_t v)
		{
			OCR2A = v;
		}

		static void writeCompareB( uint8_t v)
		{
			OCR2B = v;
		}

		static uint8_t readCompareA()
		{
			return OCR2A;
		}

		static uint8_t readCompareB()
		{
			return OCR2B;
		}

};

}
}

#endif /* __AVRPP_IO_MXXX4_TIMER2_H_ */
