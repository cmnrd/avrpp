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

#ifndef _AVRPP_MATH_FIXPOINT_H_
#define _AVRPP_MATH_FIXPOINT_H_

#include <inttypes.h>
#include <avrpp/util/type_traits.h>

namespace avrpp
{
namespace math
{
	template<typename T,		// base type
			 uint8_t magnitudeDigits,
			 uint8_t fractionDigits>
	class Fixpoint
	{
	  private:
		typedef typename util::make_unsigned<T>::type uT;

		union
		{
			T fixpoint : (fractionDigits+magnitudeDigits);
			struct
			{
				uT fraction  : fractionDigits;
				T  magnitude : magnitudeDigits;
			};
		};

	  public:
		Fixpoint() : fixpoint(0) {}
		Fixpoint(T _magnitude, uT _fraction) : fraction(_fraction), magnitude(_magnitude) {}
		Fixpoint(T _magnitude) : fraction(0), magnitude(_magnitude) {}
		Fixpoint(double d)
		{
			fixpoint = (T) (d * (((T) 1) << fractionDigits));
		}

		template<typename T2,
				 uint8_t magnitudeDigits2,
				 uint8_t fractionDigits2>
		Fixpoint(const Fixpoint<T2, magnitudeDigits2, fractionDigits2>& f)
		{
			if( sizeof(T2) > sizeof(T))
			{
				if( fractionDigits2 > fractionDigits)
					this->fixpoint = (T) (f.getFixpoint() >> (fractionDigits2 - fractionDigits));
				else
					this->fixpoint = (T) (f.getFixpoint() << (fractionDigits - fractionDigits2));
			}
			else
			{
				if( fractionDigits2 > fractionDigits)
					this->fixpoint = ( ((T) f.getFixpoint()) >> (fractionDigits2 - fractionDigits));
				else
					this->fixpoint = ( ((T) f.getFixpoint()) << (fractionDigits - fractionDigits2));
			}
		}

		static Fixpoint createByDivision(T x, T y)
		{
			Fixpoint result;
			result.fixpoint = (((typename util::make_double_size<T>::type) x) << fractionDigits) / y;
			return result;
		}

		T  getFixpoint()  const { return fixpoint; }
		T  getMagnitude() const { return magnitude; }
		uT getFraction()  const { return fraction; }

		Fixpoint& operator+=( const Fixpoint& f)
		{
			fixpoint += f.fixpoint;
			return *this;
		}

		Fixpoint& operator+=( uint8_t i)
		{
			magnitude += i;
			return *this;
		}

		Fixpoint& operator+=( int8_t i)
		{
			magnitude += i;
			return *this;
		}

		Fixpoint& operator+=( uint16_t i)
		{
			magnitude += i;
			return *this;
		}

		Fixpoint& operator+=( int16_t i)
		{
			magnitude += i;
			return *this;
		}

		Fixpoint& operator+=( uint32_t i)
		{
			magnitude += i;
			return *this;
		}

		Fixpoint& operator+=( int32_t i)
		{
			magnitude += i;
			return *this;
		}

		Fixpoint& operator-=( const Fixpoint& f)
		{
			fixpoint -= f.fixpoint;
			return *this;
		}

		Fixpoint& operator-=( uint8_t i)
		{
			magnitude -= i;
			return *this;
		}

		Fixpoint& operator-=( int8_t i)
		{
			magnitude -= i;
			return *this;
		}

		Fixpoint& operator-=( uint16_t i)
		{
			magnitude -= i;
			return *this;
		}

		Fixpoint& operator-=( int16_t i)
		{
			magnitude -= i;
			return *this;
		}

		Fixpoint& operator-=( uint32_t i)
		{
			magnitude -= i;
			return *this;
		}

		Fixpoint& operator-=( int32_t i)
		{
			magnitude -= i;
			return *this;
		}

		Fixpoint operator+( const Fixpoint& f) const
		{
			Fixpoint tmp;
			tmp.fixpoint = fixpoint + f.fixpoint;
			return tmp;
		}

		Fixpoint operator+( uint8_t i) const
		{
			Fixpoint tmp = *this;
			tmp += i;
			return tmp;
		}

		Fixpoint operator+( int8_t i) const
		{
			Fixpoint tmp = *this;
			tmp += i;
			return tmp;
		}

		Fixpoint operator+( uint16_t i) const
		{
			Fixpoint tmp = *this;
			tmp += i;
			return tmp;
		}

		Fixpoint operator+( int16_t i) const
		{
			Fixpoint tmp = *this;
			tmp += i;
			return tmp;
		}

		Fixpoint operator+( uint32_t i) const
		{
			Fixpoint tmp = *this;
			tmp += i;
			return tmp;
		}

		Fixpoint operator+( int32_t i) const
		{
			Fixpoint tmp = *this;
			tmp += i;
			return tmp;
		}

		Fixpoint operator-( const Fixpoint& f) const
		{
			Fixpoint tmp;
			tmp.fixpoint = fixpoint - f.fixpoint;
			return tmp;
		}

		Fixpoint operator-( uint8_t i) const
		{
			Fixpoint tmp = *this;
			tmp -= i;
			return tmp;
		};

		Fixpoint operator-( int8_t i) const
		{
			Fixpoint tmp = *this;
			tmp -= i;
			return tmp;
		}

		Fixpoint operator-( uint16_t i) const
		{
			Fixpoint tmp = *this;
			tmp -= i;
			return tmp;
		}

		Fixpoint operator-( int16_t i) const
		{
			Fixpoint tmp = *this;
			tmp -= i;
			return tmp;
		}

		Fixpoint operator-( uint32_t i) const
		{
			Fixpoint tmp = *this;
			tmp -= i;
			return tmp;
		}

		Fixpoint operator-( int32_t i) const
		{
			Fixpoint tmp = *this;
			tmp -= i;
			return tmp;
		}

		bool operator==( const Fixpoint& f) const
		{
			return this->fixpoint == f.fixpoint;
		}

		bool operator!=( const Fixpoint& f) const
		{
			return this->fixpoint != f.fixpoint;
		}

		bool operator>=( const Fixpoint& f) const
		{
			return this->fixpoint >= f.fixpoint;
		}

		bool operator<=( const Fixpoint& f) const
		{
			return this->fixpoint <= f.fixpoint;
		}

		bool operator<( const Fixpoint& f) const
		{
			return this->fixpoint < f.fixpoint;
		}

		bool operator>( const Fixpoint& f) const
		{
			return this->fixpoint > f.fixpoint;
		}

		Fixpoint& operator=(const Fixpoint& f)
		{
			this->fixpoint = f.fixpoint;
			return *this;
		}

		Fixpoint& operator=(uint8_t i)
		{
			this->magnitude = i;
			this->fraction = 0;
			return *this;
		}

		Fixpoint& operator=(int8_t i)
		{
			this->magnitude = i;
			this->fraction = 0;
			return *this;
		}

		Fixpoint& operator=(uint16_t i)
		{
			this->magnitude = i;
			this->fraction = 0;
			return *this;
		}

		Fixpoint& operator=(int16_t i)
		{
			this->magnitude = i;
			this->fraction = 0;
			return *this;
		}

		Fixpoint& operator=(uint32_t i)
		{
			this->magnitude = i;
			this->fraction = 0;
			return *this;
		}

		Fixpoint& operator=(int32_t i)
		{
			this->magnitude = i;
			this->fraction = 0;
			return *this;
		}

		Fixpoint& operator=(double d)
		{
			this->fixpoint = (T) (d * (((T) 1) << fractionDigits));
			return *this;
		}

		Fixpoint operator-() const
		{
			Fixpoint tmp;
			tmp.fixpoint = -this->fixpoint;
			return tmp;
		}

		Fixpoint operator*(const Fixpoint& f) const
		{
			Fixpoint result;

			result.fixpoint = extended_multiply(this->fixpoint, f.fixpoint) >> fractionDigits;

			return result;
		}

		Fixpoint& operator*=(const Fixpoint& f)
		{
			return ((*this) = (*this) * f);
		}

		Fixpoint operator>>(uint8_t i)
		{
			Fixpoint tmp;
			tmp.fixpoint = this->fixpoint >> i;
			return tmp;
		}

		Fixpoint operator<<(uint8_t i)
		{
			Fixpoint tmp;
			tmp.fixpoint = this->fixpoint << i;
			return tmp;
		}

		Fixpoint& operator>>=(uint8_t i)
		{
			this->fixpoint = this->fixpoint >> i;
			return *this;
		}

		Fixpoint& operator<<=(uint8_t i)
		{
			this->fixpoint = this->fixpoint << i;
			return *this;
		}

		T roundToInteger() const
		{
			if( fixpoint < 0)
			{
				if( fraction & (1 << fractionDigits))
					return magnitude;
				else
					return magnitude - 1;
			}
			else
			{
				if( fraction & (1 << fractionDigits))
					return magnitude + 1;
				else
					return magnitude;
			}
		}
		
		operator double() { return ((double) (this->fixpoint)) / ( ( (T) 1) << fractionDigits); }

	};

	typedef Fixpoint<int32_t, 16, 16> FixpointS16_16;
	typedef Fixpoint<int16_t, 4, 12>  FixpointS4_12;
	typedef Fixpoint<int16_t, 8, 8>   FixpointS8_8;
}
}

/* FIXME
#include "../io/iostream.h"


template<typename T,
		     typename U,
		     typename V,
			 uint8_t magnitudeDigits,
			 uint8_t fractionDigits>
io::OStreamUart& operator<<( io::OStreamUart& stream, const math::Fixpoint<T,U,V,magnitudeDigits,fractionDigits>& f)
{
	double x = 0.0;

	x = ((double) f.getFixpoint()) / ( ( (T) 1) << fractionDigits);

	stream << x;

	return stream;
}*/

#endif /* __AVRPP_MATH_FIXPOINT_H_ */
