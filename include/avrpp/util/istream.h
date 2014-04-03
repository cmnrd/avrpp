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

#ifndef _AVRPP_UTIL_ISTREAM_H_
#define _AVRPP_UTIL_ISTREAM_H_

#include <avrpp/util/stream.h>
#include <stdlib.h>

namespace avrpp
{

	template<uint8_t (receiveByte)()>
	class IStream : public Stream
	{
	  public:
		void get(char& c)
		{
			c = receiveByte();
		}

		void read( char c[])
		{
			char* ptr = c;

			get(*ptr);
			while(*ptr != '\n')
			{
				ptr++;
				get(*ptr);
			}
			*ptr = '\0';
		}

		IStream& operator>>(char& c)
		{
			get(c);
			return *this;
		}

		IStream& operator>>(char c[])
		{
			read(c);
			return *this;
		}

		IStream& operator>>(uint8_t& i)
		{
			read(Stream::tempStr);
			i = atoi(Stream::tempStr);
			return *this;
		}
		IStream& operator>>(int8_t& i)
		{
			read(Stream::tempStr);
			i = atoi(Stream::tempStr);
			return *this;
		}

		IStream& operator>>(uint16_t& i)
		{
			read(Stream::tempStr);
			i = atoi(Stream::tempStr);
			return *this;
		}

		IStream& operator>>(int16_t& i)
		{
			read(Stream::tempStr);
			i = atoi(Stream::tempStr);
			return *this;
		}

		IStream& operator>>(uint32_t& i)
		{
			read(Stream::tempStr);
			i = atol(Stream::tempStr);
			return *this;
		}

		IStream& operator>>(int32_t& i )
		{
			read(Stream::tempStr);
			i = atol(Stream::tempStr);
			return *this;
		}

		IStream& operator>>(float& f)
		{
			read(Stream::tempStr);
			f = atof(Stream::tempStr);
			return *this;
		}

		IStream& operator>>(double& d)
		{
			read(Stream::tempStr);
			d = atof(Stream::tempStr);
			return *this;

		}
	};
}


#endif /* _AVRPP_UTIL_ISTREAM_H_ */
