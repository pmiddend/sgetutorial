#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/all_extensions.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/viewport/manage_resize.hpp>
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
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/window/instance.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/with_rotation.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/file.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/image/colors.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <boost/mpl/vector.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
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

// Sprite stuff
typedef
sge::sprite::type_choices
<
  int,
  float,
  sge::image::color::rgba8_format
>
sprite_type_choices;

typedef
sge::sprite::choices
<
  sprite_type_choices,
  boost::mpl::vector
  <
    sge::sprite::with_dim,
    sge::sprite::with_color,
    sge::sprite::with_texture,
    sge::sprite::with_rotation
  >
>
sprite_choices;

typedef
sge::sprite::object<sprite_choices>
sprite_object;

typedef
sge::sprite::system<sprite_choices>::type
sprite_system;

typedef
sge::sprite::parameters<sprite_choices>
sprite_parameters;
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
        sge::systems::viewport::manage_resize()))
		(sge::systems::image_loader(
			sge::image::capabilities_field::null(),
			sge::all_extensions))
    (sge::systems::input(
      sge::systems::input_helper_field(
        sge::systems::input_helper::keyboard_collector),
        sge::systems::cursor_option_field::null())));

	running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			&exit_program));

	sprite_object ship(
		sprite_parameters()
			.texture(
				sge::texture::part_ptr(
					new sge::texture::part_raw(
						sge::renderer::texture::create_planar_from_view(
							sys.renderer(),
							sys.image_loader().load(
								FCPPT_TEXT("ship.png"))->view(),
							sge::renderer::texture::filter::linear,
							sge::renderer::texture::address_mode2(
								sge::renderer::texture::address_mode::clamp),
							sge::renderer::resource_flags::none))))
			.texture_size()
			.any_color(
				sge::image::colors::white())
			.center(
				fcppt::math::dim::structure_cast<sprite_object::point>(
					sys.renderer()->screen_size()/static_cast<sge::renderer::screen_unit>(2)))
			.elements());

	sprite_system sprite_sys(
		sys.renderer());

	while(running)
	{
		sys.window()->dispatch();

		sge::renderer::scoped_block block(
			sys.renderer());

		sge::sprite::render_one(
			sprite_sys,
			ship);
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
