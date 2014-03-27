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

#ifndef _AVRPP_OS_SCHEDULER_H_
#define _AVRPP_OS_SCHEDULER_H_

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avrpp/os/context.h>

namespace avrpp
{

template<uint8_t maxTaskCount>
class Scheduler
{
  private:
	static uint16_t sp[maxTaskCount];
	static uint8_t current;
	static uint8_t taskCount;

	static void switchToNextStack() __attribute__((always_inline))
	{
		uint8_t x = SREG;		// We need to disable interrupts because 16-bit accesses are not atomic.
		cli();
		sp[current] = SP;
		current++;
		if(current==taskCount)
			current = 0;

		SP = sp[current];
		SREG = x;
	}
  public:
	static int8_t createThread(uint16_t stackBase, void (workload)())
	{
		if( taskCount == maxTaskCount)
			return -1;

		// initialize all register with 0
		//memset((void*) (stackBase-35), 0, 33);

		// set the PC
		*((uint8_t*) stackBase) = (uint16_t) workload;			// TODO think about address handling for huge ROMS (128KB)
		*((uint8_t*) (stackBase-1)) = ((uint16_t) workload) >> 8;

		// set the interrupt flag in SREG
		*((uint8_t*) (stackBase-3)) = (1 << 7);

		// set the task's current stack pointer
		sp[taskCount] = stackBase-35;

		return taskCount++;
	}

	static void start() __attribute__((naked))
	{
		if( taskCount > 0)
		{
			cli();
			SP = sp[current];
			sei(); // TODO do not hard allow interrupts
			Context::load();
		}
	}

	static void yield() __attribute__((naked))
	{
		Context::store();
		switchToNextStack();
		Context::load();
	}
};

template<uint8_t maxTaskCount>
uint8_t Scheduler<maxTaskCount>::current = 0;

template<uint8_t maxTaskCount>
uint8_t Scheduler<maxTaskCount>::taskCount = 0;

template<uint8_t maxTaskCount>
uint16_t Scheduler<maxTaskCount>::sp[maxTaskCount] = {};



}


#endif /* _AVRPP_OS_SCHEDULER_H_ */
