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

#ifndef _AVRPP_MATH_MATH_H_
#define _AVRPP_MATH_MATH_H_

#include <inttypes.h>

namespace avrpp
{
namespace math
{

uint64_t extended_multiply(uint32_t x, uint32_t y)
{
	return ((uint64_t) x) * ((uint64_t) y);
}

int64_t extended_multiply(int32_t x, int32_t y)
{
	return ((int64_t) x) * ((int64_t) y);
}

int64_t extended_multiply(int32_t x, uint32_t y)
{
	return ((int64_t) x) * ((uint64_t) y);
}

int64_t extended_multiply(uint32_t x, int32_t y)
{
	return ((uint64_t) x) * ((int64_t) y);
}

uint32_t extended_multiply(uint16_t x, uint16_t y)
{
	return ((uint32_t) x) * ((uint32_t) y);
}

int32_t extended_multiply(int16_t x, int16_t y)
{
	return ((int32_t) x) * ((int32_t) y);
}

int32_t extended_multiply(int16_t x, uint16_t y)
{
	return ((int32_t) x) * ((uint32_t) y);
}

int32_t extended_multiply(uint16_t x, int16_t y)
{
	return ((uint32_t) x) * ((int32_t) y);
}

uint16_t extended_multiply(uint8_t x, uint8_t y)
{
	return ((uint16_t) x) * ((uint16_t) y);
}

int16_t extended_multiply(int8_t x, int8_t y)
{
	return ((int16_t) x) * ((int16_t) y);
}

int16_t extended_multiply(int8_t x, uint8_t y)
{
	return ((int16_t) x) * ((uint16_t) y);
}

int16_t extended_multiply(uint8_t x, int8_t y)
{
	return ((uint16_t) x) * ((int16_t) y);
}

template<typename T>
void lowPassFilter_mul(T& mem, T x, float f)
{
	mem = mem * (1-f) + x * f;
}

template<typename T>
void lowPassFilter_shiftLeft(T& mem, T x, uint8_t shift)
{
	mem = ((mem << shift) - mem + x) >> shift;
}

template<typename T>
void lowPassFilter_shiftRight(T& mem, T x, uint8_t shift)
{
	mem = mem - ((mem + x) >> shift);
}


}
}


#endif /* _AVRPP_MATH_MATH_H_ */
