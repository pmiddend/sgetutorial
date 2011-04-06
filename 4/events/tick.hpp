#ifndef SGEROIDS_EVENTS_TICK_HPP_INCLUDED
#define SGEROIDS_EVENTS_TICK_HPP_INCLUDED

#include <boost/statechart/event.hpp>

namespace sgeroids
{
namespace events
{
class tick
:
	public boost::statechart::event<tick>
{
};
}
}

#endif
