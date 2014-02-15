/**
 * @file type_traits.h
 *
 * @date 11.02.2014
 * @author Christian Menard
 */

#ifndef _AVRPP_UTIL_TYPE_TRAITS_H_
#define _AVRPP_UTIL_TYPE_TRAITS_H_

#include <inttypes.h>

namespace avrpp
{
namespace util
{

template<typename T>
struct make_unsigned
{ typedef T type; };

template<>
struct make_unsigned<uint8_t>
{ typedef uint8_t type; };

template<>
struct make_unsigned<int8_t>
{ typedef uint8_t type; };

template<>
struct make_unsigned<uint16_t>
{ typedef uint16_t type; };

template<>
struct make_unsigned<int16_t>
{ typedef uint16_t type; };

template<>
struct make_unsigned<uint32_t>
{ typedef uint32_t type; };

template<>
struct make_unsigned<int32_t>
{ typedef uint32_t type; };

template<>
struct make_unsigned<uint64_t>
{ typedef uint64_t type; };

template<>
struct make_unsigned<int64_t>
{ typedef uint64_t type; };

template<typename T>
struct make_signed
{ typedef T type; };

template<>
struct make_signed<uint8_t>
{ typedef int8_t type; };

template<>
struct make_signed<int8_t>
{ typedef int8_t type; };

template<>
struct make_signed<uint16_t>
{ typedef int16_t type; };

template<>
struct make_signed<int16_t>
{ typedef int16_t type; };

template<>
struct make_signed<uint32_t>
{ typedef int32_t type; };

template<>
struct make_signed<int32_t>
{ typedef int32_t type; };

template<>
struct make_signed<uint64_t>
{ typedef int64_t type; };

template<typename T>
struct make_double_size
{ typedef T type; };

template<>
struct make_double_size<uint8_t>
{ typedef uint16_t type; };

template<>
struct make_double_size<int8_t>
{ typedef int16_t type; };

template<>
struct make_double_size<uint16_t>
{ typedef uint32_t type; };

template<>
struct make_double_size<int16_t>
{ typedef int32_t type; };

template<>
struct make_double_size<uint32_t>
{ typedef uint64_t type; };

template<>
struct make_double_size<int32_t>
{ typedef int64_t type; };

}
}




#endif /* TYPE_TRAITS_H_ */
