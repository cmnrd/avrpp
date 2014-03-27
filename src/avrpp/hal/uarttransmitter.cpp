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
 *
 */

#include <avrpp/hal/uarttransmitter.h>
using namespace avrpp;

Buffer<uint8_t,UART0_TRANSMITTER_BUFFER_SIZE> Uart0Transmitter::buffer;

void Uart0Transmitter::write(uint8_t byte)
{
	buffer.push(byte);
	Usart0::enableInterrupts(Usart0InterruptEnable::DATA_REGISTER_EMPTY);
}

ISR(USART0_UDRE_vect)
{
	uint8_t tmp = Uart0Transmitter::buffer.pop();
	Usart0::writeByte(tmp);
	if( Uart0Transmitter::buffer.isEmpty())
		Usart0::disableInterrupts(Usart0InterruptEnable::DATA_REGISTER_EMPTY);
}

Buffer<uint8_t,UART1_TRANSMITTER_BUFFER_SIZE> Uart1Transmitter::buffer;

void Uart1Transmitter::write(uint8_t byte)
{
	buffer.push(byte);
	Usart0::enableInterrupts(Usart0InterruptEnable::DATA_REGISTER_EMPTY);
}

ISR(USART1_UDRE_vect)
{
	uint8_t tmp = Uart1Transmitter::buffer.pop();
	Usart1::writeByte(tmp);
	if( Uart1Transmitter::buffer.isEmpty())
		Usart1::disableInterrupts(Usart1InterruptEnable::DATA_REGISTER_EMPTY);
}
