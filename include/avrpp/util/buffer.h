/**
 * @file buffer.h
 *
 * @date 22.03.2014
 * @author Christian Menard
 */

#ifndef _AVRPP_OS_BUFFER_H_
#define _AVRPP_OS_BUFFER_H_

#include <inttypes.h>
#include <util/atomic.h>

namespace avrpp
{
namespace util
{

/*
 * TODO: Think about an implementation based on start and end pointer.
 * This will reduce address calculating in push function.
 */

template<typename T, uint8_t size>
class Buffer
{
  private:
	volatile uint8_t start;
	volatile uint8_t n;
	volatile T buffer[size];
  public:
	Buffer() : start(0), n(0) {}

	void push(T c);

	T pop();

	T peek() { while(isEmpty()); return buffer[start]; }

	uint8_t count() { return n; }

	bool isEmpty() { return n == 0; }

	bool full() { return n == size; }

	void flush() { n = 0; }
};

template<typename T, uint8_t size>
void Buffer<T, size>::push(T c)
{
	while( full()) // Wait until there is free space in buffer
		;

	// TODO check if full needs to be done inside the atomic block;

	// Operation is not atomic (producer-consumer problem)
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		// Store the item and calculate its place.
		buffer[ (start + n) > (size - 1) ? (n - (size - start)) : (start + n)] = c;
		n++;
	}
}

template<typename T, uint8_t size>
T Buffer<T, size>::pop()
{
	while( isEmpty()) // Wait until there is data in buffer
		;

	T c;

	// Operation is not atomic (producer-consumer problem)
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		c = buffer[start];
		// increment start pointer, set it to 0 if the end of buffer is reached
		start = (start >= size - 1) ? 0 : start + 1;
		n--;
	}

	return c;
}
}
}




#endif /* _AVRPP_OS_BUFFER_H_ */
