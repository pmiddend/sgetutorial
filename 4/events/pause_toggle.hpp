#ifndef SGEROIDS_EVENTS_PAUSE_TOGGLE_HPP_INCLUDED
#define SGEROIDS_EVENTS_PAUSE_TOGGLE_HPP_INCLUDED

#include <boost/statechart/event.hpp>

namespace sgeroids
{
namespace events
{
class pause_toggle
:
	public boost::statechart::event<pause_toggle>
{
};
}
}

#endif
