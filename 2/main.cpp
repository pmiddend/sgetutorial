#include <sge/all_extensions.hpp>
#include <sge/image2d/image2d.hpp>
#include <sge/image/image.hpp>
#include <sge/input/keyboard/keyboard.hpp>
#include <sge/renderer/renderer.hpp>
#include <sge/sprite/sprite.hpp>
#include <sge/systems/systems.hpp>
#include <sge/texture/texture.hpp>
#include <sge/viewport/viewport.hpp>
#include <sge/window/window.hpp>
#include <fcppt/math/dim/dim.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <boost/mpl/vector.hpp>
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
		(sge::systems::image_loader(
			sge::image::capabilities_field::null(),
			sge::all_extensions))
    (sge::systems::input(
      sge::systems::input_helper_field(
        sge::systems::input_helper::keyboard_collector),
        sge::systems::cursor_option_field::null())));

	running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
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
				sprite_object::vector(
					512,
					384))
			.elements());

	sprite_system sprite_sys(
		sys.renderer());

	while(running)
	{
		sys.window().dispatch();

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
