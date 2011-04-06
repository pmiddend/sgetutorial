#include "superstate.hpp"
#include "../../events/pause_toggle.hpp"
#include <boost/bind.hpp>

sgeroids::states::ingame::superstate::superstate(
	my_context _context)
:
	my_base(
		_context),
	handle_keypress_connection_(
		context<machine>().systems().keyboard_collector().key_callback(
			boost::bind(
				&handle_keypress,
				this,
				_1)))
{
}

void
sgeroids::states::ingame::superstate::handle_keypress(
	sge::input::keyboard::key_event const &)
{
	context<machine>().process_event(
		events::pause_toggle());
}
