#ifndef SGEROIDS_EVENTS_RENDER_HPP_INCLUDED
#define SGEROIDS_EVENTS_RENDER_HPP_INCLUDED

#include <boost/statechart/event.hpp>

namespace sgeroids
{
namespace events
{
class render
:
	public boost::statechart::event<render>
{
};
}
}

#endif
