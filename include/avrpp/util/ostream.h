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

#ifndef _AVRPP_UTIL_OSTREAM_H_
#define _AVRPP_UTIL_OSTREAM_H_

#include <avrpp/util/stream.h>
#include <stdlib.h>

namespace avrpp
{
	template<void (transmitByte)(uint8_t)>
	class OStream : public Stream
	{
	  private:
	  public:

		OStream& put( char c) { transmitByte(c); return *this; }
		OStream& write( const char str[])
		{
			for(int i = 0; str[i] != '\0'; i++)
				put(str[i]);
			return *this;
		}

		OStream& operator<<(char c) { return put(c); }
		OStream& operator<<(const char str[]) { return write(str); }
		OStream& operator<<( uint8_t i)
		{
			return write( utoa(i, Stream::tempStr, 10));
		}
		OStream& operator<<( int8_t i)
		{
			return write( itoa(i, Stream::tempStr, 10));
		}
		OStream& operator<<( uint16_t i)
		{
			return write( utoa(i, Stream::tempStr, 10));
		}
		OStream& operator<<( int16_t i)
		{
			return write( itoa(i, Stream::tempStr, 10));
		}
		OStream& operator<<( uint32_t i)
		{
			return write( utoa(i, Stream::tempStr, 10));
		}
		OStream& operator<<( int32_t i)
		{
			return write( itoa(i, Stream::tempStr, 10));
		}

		OStream& operator<<( float f)
		{
			return write( dtostrf(f,1,6,Stream::tempStr));
		}
		OStream& operator<<( double d)
		{
			return write( dtostrf(d,1,6,Stream::tempStr));
		}
	};

}

#endif /* _AVRPP_UTIL_OSTREAM_H_ */
