#ifndef SGEROIDS_STATES_INGAME_RUNNING_HPP_INCLUDED
#define SGEROIDS_STATES_INGAME_RUNNING_HPP_INCLUDED

#include "superstate.hpp"
#include "../../events/pause_toggle.hpp"
#include "../../events/render.hpp"
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace sgeroids
{
namespace states
{
namespace ingame
{
class running
:
	public boost::statechart::state<running,superstate>
{
public:
	typedef
	boost::mpl::list
	<
		boost::statechart::custom_reaction<events::pause_toggle>,
		boost::statechart::custom_reaction<events::render>
	>
	reactions;

	explicit
	running(
		my_context);

	boost::statechart::result
	react(
		events::pause_toggle const &);

	boost::statechart::result
	react(
		events::render const &);

	~running();
};
}
}
}


#endif
