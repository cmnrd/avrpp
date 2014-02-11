/**
 * @file io.h
 *
 * @date 11.02.2014
 * @author Christian Menard
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
