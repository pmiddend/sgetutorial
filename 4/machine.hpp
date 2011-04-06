#ifndef SGEROIDS_MACHINE_HPP_INCLUDED
#define SGEROIDS_MACHINE_HPP_INCLUDED

#include "states/ingame/superstate_fwd.hpp"
#include <sge/systems/instance.hpp>
#include <boost/statechart/state_machine.hpp>

namespace sgeroids
{
class machine
:
	public boost::statechart::state_machine<machine,states::ingame::superstate>
{
public:
	machine();

	sge::systems::instance const &
	systems() const;

	void
	run();
private:
	sge::systems::instance systems_;
	bool running_;
};
}

#endif
