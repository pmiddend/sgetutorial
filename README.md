What is this?
=============

This repository accompanies the "Game development in sge/C++" article
series, available at:

http://pimiddy.wordpress.com

The folders correspond to the parts of the tutorial.

General Linux build instructions
==========================

Introduction
------------

To build the programs from the articles, you need a few dependent
libraries. The core dependencies are:

* fcppt (Freundlich's C++ Toolkit)
* awl (Abstract Window Library, to create windows and receive events from them)
* sge (the graphics engine, containing the renderer, image loader, sprite abstractions etc.)
* mizuiro (an "abstract image library")

Those I will cover in this document. But you need other libraries as well:

* boost (one of the latest versions)
* OpenGL
* libXi (at least 1.4.1, else input is broken)

Those I will _not_ cover. The installation is highly
distribution-dependant, so I cannot possibly give an
installation guide satisfying everybody.

Also, you need tools to build the libraries:

* gcc (at least 4.4) or clang
* cmake (at least 2.6)
* make

Procedure
---------

The libraries can all be installed in the same manner:

* Clone the git repository
* Create a build directory inside the cloned repository
* Run `cmake`
* Run `make install`

I _highly_ recommend cmake's curses based UI, ccmake to do the
cmake configuration.

I also assume you want to install all the libraries to a directory
which I refer to as `$myprefix`. This could be `/usr/` or `/usr/local`
or even `/home/foobar/local`. First, we need to tell the compiler that
these directories are to be searched for libraries and headers. Open a
terminal (I assume you're using bash) and type:

	# Just an example
	export myprefix="$HOME/local"
	export CPLUS_INCLUDE_PATH="${CPLUS_INCLUDE_PATH}:$myprefix"
	export LIBRARY_PATH="${LIBRARY_PATH}:$myprefix"
	export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:$myprefix"

fcppt
-----

Open a terminal, type:

	git clone git://github.com/freundlich/fcppt.git
	cd fcppt
	mkdir build
	cd build
	cmake -D CMAKE_INSTALL_PREFIX=$myprefix ..

This will hopefully output something like:

	-- The C compiler identification is GNU
	-- The CXX compiler identification is GNU
	-- Check for working C compiler: /usr/bin/gcc
	-- Check for working C compiler: /usr/bin/gcc -- works
	-- Detecting C compiler ABI info
	-- Detecting C compiler ABI info - done
	-- Check for working CXX compiler: /usr/bin/c++
	-- Check for working CXX compiler: /usr/bin/c++ -- works
	-- Detecting CXX compiler ABI info
	-- Detecting CXX compiler ABI info - done
	-- Performing Test COMPILER_IS_CLANGPP
	-- Performing Test COMPILER_IS_CLANGPP - Failed
	-- Performing Test FCPPT_HAVE_GCC_VISIBILITY
	-- Performing Test FCPPT_HAVE_GCC_VISIBILITY - Success
	-- Performing Test FCPPT_HAS_GNU_DEMANGLE
	-- Performing Test FCPPT_HAS_GNU_DEMANGLE - Success
	-- Performing Test FCPPT_HAVE_GCC_PRAGMA_MESSAGE
	-- Performing Test FCPPT_HAVE_GCC_PRAGMA_MESSAGE - Success
	-- Performing Test FCPPT_HAVE_GCC_DIAGNOSTIC
	-- Performing Test FCPPT_HAVE_GCC_DIAGNOSTIC - Failed
	-- Performing Test FCPPT_HAVE_MISSING_DECLARATIONS_FLAG
	-- Performing Test FCPPT_HAVE_MISSING_DECLARATIONS_FLAG - Success
	-- Boost version: 1.45.0
	-- Found the following Boost libraries:
	--   filesystem
	--   system
	--   thread
	-- Performing Test FCPPT_HAVE_ATLEAST_UINT64
	-- Performing Test FCPPT_HAVE_ATLEAST_UINT64 - Success
	-- Performing Test FCPPT_HAVE_LONG_LONG
	-- Performing Test FCPPT_HAVE_LONG_LONG - Success
	-- Performing Test FCPPT_HAVE_POSIX
	-- Performing Test FCPPT_HAVE_POSIX - Success
	-- Performing Test FCPPT_ALIGN_TEMPLATE_PARAMETER
	-- Performing Test FCPPT_ALIGN_TEMPLATE_PARAMETER - Success
	-- Looking for mach/mach_time.h
	-- Looking for mach/mach_time.h - not found
	-- Performing Test FCPPT_HAVE_CLOCK_GETTIME
	-- Performing Test FCPPT_HAVE_CLOCK_GETTIME - Success
	-- Boost version: 1.45.0
	-- Found the following Boost libraries:
	--   unit_test_framework
	-- Configuring done
	-- Generating done
	-- Build files have been written to: /home/cpptest/test/fcppt/build

Then you can run:

  $ make install

This might take a few minutes. The last few lines of output should
look something like:

	-- Installing: /home/cpptest/local/include/fcppt/algorithm/impl/element_not_found.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/impl/exception.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/join_strings.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/compare_with.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/find_exn.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/ptr_container_erase_if.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/shortest_levenshtein.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/element_not_found.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/levenshtein.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/remove_if.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/contains_if.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/remove.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/set_intersection.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/contains.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/map.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/shift_compare.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/exception.hpp
	-- Installing: /home/cpptest/local/include/fcppt/algorithm/append.hpp
	-- Installing: /home/cpptest/local/include/fcppt/nonassignable.hpp
	-- Installing: /home/cpptest/local/include/fcppt/exception.hpp
	-- Installing: /home/cpptest/local/include/fcppt/stub_function.hpp
	-- Installing: /home/cpptest/local/include/fcppt/make_shared_ptr.hpp
	-- Installing: /home/cpptest/local/include/fcppt/lexical_cast.hpp
	-- Installing: /home/cpptest/local/include/fcppt/minmax_pair.hpp
	-- Installing: /home/cpptest/local/include/fcppt/move.hpp
	-- Installing: /home/cpptest/local/include/fcppt/config.hpp
	-- Installing: /home/cpptest/local/include/fcppt/version.hpp
	-- Installing: /home/cpptest/local/share/cmake/Modules/FindFcppt.cmake

mizuiro
-------

	git clone git://github.com/freundlich/mizuiro.git
	cd mizuiro
	mkdir build
	cd build
	cmake -D CMAKE_INSTALL_PREFIX:=$myprefix -D ENABLE_FCPPT:=ON -D EXTRA_CMAKE_MODULE_PATH:=$myprefix/share/cmake/Modules ..

The expected output looks something like this:

	-- The C compiler identification is GNU
	-- The CXX compiler identification is GNU
	-- Check for working C compiler: /usr/bin/gcc
	-- Check for working C compiler: /usr/bin/gcc -- works
	-- Detecting C compiler ABI info
	-- Detecting C compiler ABI info - done
	-- Check for working CXX compiler: /usr/bin/c++
	-- Check for working CXX compiler: /usr/bin/c++ -- works
	-- Detecting CXX compiler ABI info
	-- Detecting CXX compiler ABI info - done
	-- Boost version: 1.45.0
	-- Found FCPPT: /home/cpptest/local/lib/libfcppt.so 
	-- Performing Test COMPILER_IS_CLANGPP
	-- Performing Test COMPILER_IS_CLANGPP - Failed
	-- Performing Test MIZUIRO_HAVE_BUILTIN_EXPECT
	-- Performing Test MIZUIRO_HAVE_BUILTIN_EXPECT - Success
	-- Boost version: 1.45.0
	-- Found the following Boost libraries:
	--   unit_test_framework
	-- Configuring done
	-- Generating done
	-- Build files have been written to: /home/cpptest/test/mizuiro/build

Then type:

	make install

awl
---

	git clone git://github.com/Phillemann/libawl.git
	cd libawl
	mkdir build
	cd build
	cmake -D CMAKE_INSTALL_PREFIX:=$myprefix -D EXTRA_CMAKE_MODULE_PATH:=$myprefix/share/cmake/Modules ..

Expected output, again:

	-- The C compiler identification is GNU
	-- The CXX compiler identification is GNU
	-- Check for working C compiler: /usr/bin/gcc
	-- Check for working C compiler: /usr/bin/gcc -- works
	-- Detecting C compiler ABI info
	-- Detecting C compiler ABI info - done
	-- Check for working CXX compiler: /usr/bin/c++
	-- Check for working CXX compiler: /usr/bin/c++ -- works
	-- Detecting CXX compiler ABI info
	-- Detecting CXX compiler ABI info - done
	-- Performing Test COMPILER_IS_CLANGPP
	-- Performing Test COMPILER_IS_CLANGPP - Failed
	-- Boost version: 1.45.0
	-- Found the following Boost libraries:
	--   system
	--   thread
	-- Found FCPPT: /home/cpptest/local/lib/libfcppt.so 
	-- Looking for XOpenDisplay in /usr/lib64/libX11.so;/usr/lib64/libXext.so
	-- Looking for XOpenDisplay in /usr/lib64/libX11.so;/usr/lib64/libXext.so - found
	-- Looking for gethostbyname
	-- Looking for gethostbyname - found
	-- Looking for connect
	-- Looking for connect - found
	-- Looking for remove
	-- Looking for remove - found
	-- Looking for shmat
	-- Looking for shmat - found
	-- Looking for IceConnectionNumber in ICE
	-- Looking for IceConnectionNumber in ICE - found
	-- Found X11: /usr/lib64/libX11.so
	-- Configuring done
	-- Generating done
	-- Build files have been written to: /home/cpptest/test/libawl/build

Then, again:

	make install

spacegameengine
---------------

	git clone git://github.com/freundlich/spacegameengine.git

Note that this could take a while this time...

	cd spacegameengine
	mkdir build
	cd build
	cmake -D CMAKE_INSTALL_PREFIX:=$myprefix -D EXTRA_CMAKE_MODULE_PATH:=$myprefix/share/cmake/Modules ..

Note that this will build sge in its default configuration. If you
want certain plugins and modules or the examples, use `ccmake ..` in
the `build` directory to configure sge further.

Expected:

	-- The C compiler identification is GNU
	-- The CXX compiler identification is GNU
	-- Check for working C compiler: /usr/bin/gcc
	-- Check for working C compiler: /usr/bin/gcc -- works
	-- Detecting C compiler ABI info
	-- Detecting C compiler ABI info - done
	-- Check for working CXX compiler: /usr/bin/c++
	-- Check for working CXX compiler: /usr/bin/c++ -- works
	-- Detecting CXX compiler ABI info
	-- Detecting CXX compiler ABI info - done
	-- Performing Test COMPILER_IS_CLANGPP
	-- Performing Test COMPILER_IS_CLANGPP - Failed
	-- Performing Test SGE_HAVE_GCC_VISIBILITY
	-- Performing Test SGE_HAVE_GCC_VISIBILITY - Success
	-- Boost version: 1.45.0
	-- Found the following Boost libraries:
	--   filesystem
	--   system
	-- Found FCPPT: /home/cpptest/local/lib/libfcppt.so 
	-- Found MIZUIRO: /home/cpptest/local/include 
	-- Looking for MIZUIRO_HAVE_FCPPT
	-- Looking for MIZUIRO_HAVE_FCPPT - found
	-- Found AWL: /home/cpptest/local/include 
	-- Could NOT find Bullet (missing:  BULLET_INCLUDE_DIR) 
	-- Found IL: /usr/lib64/libIL.so 
	-- Could NOT find DINPUT (missing:  DINPUT_INCLUDE_DIR DINPUT_LIBRARY DXGUID_LIBRARY) 
	-- Found Freetype: /usr/lib64/libfreetype.so 
	-- Performing Test ICONV_HAVE_POSIX
	-- Performing Test ICONV_HAVE_POSIX - Success
	-- Found ICONV: /usr/include 
	-- Found GLEW: /usr/include 
	-- Looking for XOpenDisplay in /usr/lib64/libX11.so;/usr/lib64/libXext.so
	-- Looking for XOpenDisplay in /usr/lib64/libX11.so;/usr/lib64/libXext.so - found
	-- Looking for gethostbyname
	-- Looking for gethostbyname - found
	-- Looking for connect
	-- Looking for connect - found
	-- Looking for remove
	-- Looking for remove - found
	-- Looking for shmat
	-- Looking for shmat - found
	-- Looking for IceConnectionNumber in ICE
	-- Looking for IceConnectionNumber in ICE - found
	-- Found X11: /usr/lib64/libX11.so
	-- Found OpenAL: /usr/lib64/libopenal.so 
	-- Found ZLIB: /usr/include (found version "1.2.5")
	-- Found PNG: /usr/lib64/libpng.so (Required is at least version "1.4.1")
	-- Found VORBIS: /usr/include 
	-- Configuring done
	-- Generating done
	-- Build files have been written to: /home/cpptest/test/spacegameengine/build

This is technically not the "expected" output. It's the expected
output if you have all of sge's optional components installed. For
example, if you don't have OpenAL installed, then the check for OpenAL
will, of course, fail. If you try to use sound anyway, the application
will crash (unless you enable the null audio plugin).

Anyway, then

	make install

This could also take a while. And then you're done. The tutorial files
can be built in exactly the same way and with the same commands as the
libraries. The bin files will then reside in
`build/bin/<number>/main<number>`.

Hope this helps.
