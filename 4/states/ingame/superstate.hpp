#ifndef SGEROIDS_STATES_INGAME_SUPERSTATE_HPP_INCLUDED
#define SGEROIDS_STATES_INGAME_SUPERSTATE_HPP_INCLUDED

#include "running_fwd.hpp"
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <boost/statechart/state.hpp>

namespace sgeroids
{
namespace states
{
namespace ingame
{
class superstate
:
	// machine (the "context") must be complete, running (the initial state)
	// doesn't have to be
	public boost::statechart::state<superstate,machine,running>
{
public:
	// Wtf, my_context? See below
	explicit
	superstate(
		my_context);
private:
	fcppt::signal::scoped_connection handle_keypress_connection_;

	void
	handle_keypress(
		sge::input::keyboard::key_event const &);
};
}
}
}

#endif
