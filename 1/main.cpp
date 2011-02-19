#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/viewport/center_on_resize.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/window_parameters.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/depth_buffer.hpp>
#include <sge/renderer/stencil_buffer.hpp>
#include <sge/renderer/window_mode.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
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
        sge::renderer::window_parameters(
          FCPPT_TEXT("the_game"))))
    (sge::systems::renderer(
        sge::renderer::parameters(
          sge::renderer::display_mode(
            sge::renderer::screen_size(
              1024,
              768),
            sge::renderer::bit_depth::depth32,
            sge::renderer::refresh_rate_dont_care),
          sge::renderer::depth_buffer::off,
          sge::renderer::stencil_buffer::off,
          sge::renderer::window_mode::windowed,
          sge::renderer::vsync::on,
          sge::renderer::no_multi_sampling),
        sge::systems::viewport::center_on_resize()))
    (sge::systems::input(
      sge::systems::input_helper_field(
        sge::systems::input_helper::keyboard_collector),
        sge::systems::cursor_option_field::null())));

	running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			&exit_program));

	while(running)
	{
		sys.window()->dispatch();
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
