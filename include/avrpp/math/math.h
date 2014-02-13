/**
 * @file math.h
 *
 * @date 13.02.2014
 * @author Christian Menard
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





}
}


#endif /* _AVRPP_MATH_MATH_H_ */
