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

#ifndef _AVRPP_IO_MXXX4_H_
#define _AVRPP_IO_MXXX4_H_

#ifndef _AVRPP_IO_H_
#  error "Include <avrpp/io.h> instead of this file."
#endif

#ifndef _AVRPP_IOXXX_
#  define _AVRPP_IOXXX_ "mxxx4"
#else
#  error "Attempt to include more than one <avrpp/io*> file."
#endif

#include <avrpp/io/mxxx4/adc.h>
#include <avrpp/io/mxxx4/timer0.h>
#include <avrpp/io/mxxx4/timer1.h>
#include <avrpp/io/mxxx4/timer2.h>
#include <avrpp/io/mxxx4/twi.h>
#include <avrpp/io/mxxx4/usart0.h>
#include <avrpp/io/mxxx4/usart1.h>

#endif /* _AVRPP_IO_MXXX4_H_ */
