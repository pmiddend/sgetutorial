#include <sge/systems/systems.hpp>
#include <sge/viewport/viewport.hpp>
#include <sge/renderer/renderer.hpp>
#include <sge/input/keyboard/keyboard.hpp>
#include <sge/window/window.hpp>
#include <fcppt/math/dim/dim.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <iostream>
#include <ostream>
#include <exception>
#include <cstdlib>

namespace
{
bool running;

void
exit_program(
	sge::input::keyboard::key_event const &e)
{
	if (e.pressed() && e.key_code() == sge::input::keyboard::key_code::escape)
		running = false;
}
}

int main()
try
{
  sge::systems::instance sys(
    sge::systems::list()
    (sge::systems::window(
        sge::window::simple_parameters(
          FCPPT_TEXT("the_game"),
					sge::window::dim(
						1024,768))))
    (sge::systems::renderer(
        sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
          sge::renderer::depth_stencil_buffer::off,
          sge::renderer::vsync::on,
          sge::renderer::no_multi_sampling),
        sge::viewport::center_on_resize(
					sge::window::dim(
						1024,768))))
    (sge::systems::input(
      sge::systems::input_helper_field(
        sge::systems::input_helper::keyboard_collector),
        sge::systems::cursor_option_field::null())));

	running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			&exit_program));

	while(running)
	{
		sys.window().dispatch();
	}

	return EXIT_SUCCESS;
}
catch (fcppt::exception const &e)
{
	fcppt::io::cerr << FCPPT_TEXT("Exception caught: ") << e.string() << FCPPT_TEXT("\n");
	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr << "Exception caught: " << e.what() << "\n";
	return EXIT_FAILURE;
}
