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

#ifndef _AVRPP_IO_H_
#define _AVRPP_IO_H_

#if defined (__AVR_ATmega1284P__) || defined (__AVR_ATmega644__)   || defined (__AVR_ATmega644A__) || \
	defined (__AVR_ATmega644P__)  || defined (__AVR_ATmega644PA__) || defined (__AVR_ATmega324P__) || \
	defined (__AVR_ATmega324A__)  || defined (__AVR_ATmega324PA__) || defined (__AVR_ATmega324PA__)|| \
	defined (__AVR_ATmega164P__)  || defined (__AVR_ATmega164A__)
#include <avrpp/io/mxxx4/io.h>
#else
#error "Your target device is not supported by avrpp"
#endif


#endif /* AVRPP_IO_H_ */
