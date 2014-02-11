/**
 * @file mxxx4.h
 *
 * @date 11.02.2014
 * @author Christian Menard
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
