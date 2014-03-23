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

#ifndef _AVRPP_UTIL_TYPE_TRAITS_H_
#define _AVRPP_UTIL_TYPE_TRAITS_H_

#include <inttypes.h>

namespace avrpp
{

template<typename T>
struct make_unsigned
{ typedef T type; };

template<>
struct make_unsigned<uint8_t>
{ typedef uint8_t type; };

template<>
struct make_unsigned<int8_t>
{ typedef uint8_t type; };

template<>
struct make_unsigned<uint16_t>
{ typedef uint16_t type; };

template<>
struct make_unsigned<int16_t>
{ typedef uint16_t type; };

template<>
struct make_unsigned<uint32_t>
{ typedef uint32_t type; };

template<>
struct make_unsigned<int32_t>
{ typedef uint32_t type; };

template<>
struct make_unsigned<uint64_t>
{ typedef uint64_t type; };

template<>
struct make_unsigned<int64_t>
{ typedef uint64_t type; };

template<typename T>
struct make_signed
{ typedef T type; };

template<>
struct make_signed<uint8_t>
{ typedef int8_t type; };

template<>
struct make_signed<int8_t>
{ typedef int8_t type; };

template<>
struct make_signed<uint16_t>
{ typedef int16_t type; };

template<>
struct make_signed<int16_t>
{ typedef int16_t type; };

template<>
struct make_signed<uint32_t>
{ typedef int32_t type; };

template<>
struct make_signed<int32_t>
{ typedef int32_t type; };

template<>
struct make_signed<uint64_t>
{ typedef int64_t type; };

template<typename T>
struct make_double_size
{ typedef T type; };

template<>
struct make_double_size<uint8_t>
{ typedef uint16_t type; };

template<>
struct make_double_size<int8_t>
{ typedef int16_t type; };

template<>
struct make_double_size<uint16_t>
{ typedef uint32_t type; };

template<>
struct make_double_size<int16_t>
{ typedef int32_t type; };

template<>
struct make_double_size<uint32_t>
{ typedef uint64_t type; };

template<>
struct make_double_size<int32_t>
{ typedef int64_t type; };

union Word16
{
	uint16_t word;

	struct
	{
		uint8_t low;
		uint8_t high;
	};
};

union Word32
{
	uint32_t word;

	struct
	{
		uint16_t low;
		uint16_t high;
	};
};

}


#endif /* TYPE_TRAITS_H_ */
