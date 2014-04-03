/**
 * @file buffer.h
 *
 * @date 22.03.2014
 * @author Christian Menard
 */

#ifndef _AVRPP_UTIL_BUFFER_H_
#define _AVRPP_UTIL_BUFFER_H_

#include <inttypes.h>
#include <util/atomic.h>
#include <avrpp/os/scheduler.h>

namespace avrpp
{

/*
 * TODO: Think about an implementation based on start and end pointer.
 * This will reduce address calculating in push function.
 */

/**
 * @tparam T base type
 * @tparam size total number of entries of type T
 * @tparam U Scheduler, void if no Scheduler is used
 */
template<typename T, uint8_t size, typename U=void>
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

	T peek();

	uint8_t count() { return n; }

	bool isEmpty() { return n == 0; }

	bool full() { return n == size; }

	void flush() { n = 0; }
};

template<typename T, uint8_t size>
class Buffer<T, size, void>
{
  private:
	volatile uint8_t start;
	volatile uint8_t n;
	volatile T buffer[size];
  public:
	Buffer() : start(0), n(0) {}

	void push(T c);

	T pop();

	T peek();

	uint8_t count() { return n; }

	bool isEmpty() { return n == 0; }

	bool full() { return n == size; }

	void flush() { n = 0; }
};

template<typename T, uint8_t size, typename U>
T Buffer<T, size, U>::peek()
{
	while(true)
	{
		// Operation is not atomic (producer-consumer problem)
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if(!isEmpty())
				return buffer[start];
		}

		U::yield();
	}
}

template<typename T, uint8_t size>
T Buffer<T, size, void>::peek()
{
	while(true)
	{
		// Operation is not atomic (producer-consumer problem)
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if(!isEmpty())
				return buffer[start];
		}
	}
}

template<typename T, uint8_t size>
void Buffer<T, size, void>::push(T c)
{
	while(true)
	{
		// Operation is not atomic (producer-consumer problem)
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if(!full()) // Wait until there is free space in buffer
			{
				// Store the item and calculate its place.
				buffer[ (start + n) > (size - 1) ? (n - (size - start)) : (start + n)] = c;
				n++;
				return;
			}

		}
	}
}

template<typename T, uint8_t size, typename U>
void Buffer<T, size, U>::push(T c)
{
	while(true)
	{
		// Operation is not atomic (producer-consumer problem)
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if(!full()) // Wait until there is free space in buffer
			{
				// Store the item and calculate its place.
				buffer[ (start + n) > (size - 1) ? (n - (size - start)) : (start + n)] = c;
				n++;
				return;
			}

		}

		U::yield();
	}
}

template<typename T, uint8_t size>
T Buffer<T, size, void>::pop()
{
	while(true)
	{
		// Operation is not atomic (producer-consumer problem)
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if(!isEmpty()) // Wait until there is data in buffer
			{
				T c = buffer[start];
				// increment start pointer, set it to 0 if the end of buffer is reached
				start = (start >= size - 1) ? 0 : start + 1;
				n--;
				return c;
			}
		}
	}
}

template<typename T, uint8_t size, typename U>
T Buffer<T, size, U>::pop()
{
	while(true)
	{
		// Operation is not atomic (producer-consumer problem)
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if(!isEmpty()) // Wait until there is data in buffer
			{
				T c = buffer[start];
				// increment start pointer, set it to 0 if the end of buffer is reached
				start = (start >= size - 1) ? 0 : start + 1;
				n--;
				return c;
			}
		}

		U::yield();
	}
}

}

#endif /* _AVRPP_UTIL_BUFFER_H_ */
