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

#ifndef _AVRPP_CONFIG_H_
#define _AVRPP_CONFIG_H_

#ifndef F_CPU
#define F_CPU 20000000L
#endif

#define BAUD 57600
#define BAUD1 38400
#define SCL_CLOCK  200000L

#define STREAM_TEMP_STRING_SIZE 16
#define UART1_RECEIVER_BUFFER_SIZE 64
#define UART1_TRANSMITTER_BUFFER_SIZE 64
#define UART0_RECEIVER_BUFFER_SIZE 64
#define UART0_TRANSMITTER_BUFFER_SIZE 64

#define TWI_TRANSMIT_BUFFER_SIZE 64
#define TWI_TRANSMIT_MAX_FRAME_SIZE 4

#endif /* _AVRPP_CONFIG_H_ */
