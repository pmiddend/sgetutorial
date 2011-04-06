#ifndef SGEROIDS_STATES_INGAME_PAUSED_HPP_INCLUDED
#define SGEROIDS_STATES_INGAME_PAUSED_HPP_INCLUDED

#include "superstate.hpp"
#include <boost/statechart/state.hpp>

namespace sgeroids
{
namespace states
{
namespace ingame
{
class paused
:
	// ingame now has to be complete
	public boost::statechart::state<paused,superstate>
{
public:
	// Wtf, my_context? See below
	explicit
	paused(
		my_context);
};
}
}
}

#endif
