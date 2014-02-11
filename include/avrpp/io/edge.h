/**
 * @file edge.h
 *
 * @date 11.02.2014
 * @author Christian Menard
 */

#ifndef _AVRPP_IO_EDGE_H_
#define _AVRPP_IO_EDGE_H_

namespace avrpp
{
namespace io
{

	enum class Edge : uint8_t
	{
		FALLING_EDGE,
		RISING_EDGE
	};

}
}

#endif /* _AVRPP_IO_EDGE_H_ */
