CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(blog)

INCLUDE(FcpptCMakeUtils)

FIND_PACKAGE(
	Boost 1.45.0 REQUIRED COMPONENTS
	system)

INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
# boost end

# awl begin
FIND_PACKAGE(Awl REQUIRED)
INCLUDE_DIRECTORIES(${Awl_INCLUDE_DIR})
ADD_DEFINITIONS(${Awl_DEFINITIONS})
# awl end

# mizuiro begin
FIND_PACKAGE(Mizuiro REQUIRED)
INCLUDE_DIRECTORIES(${Mizuiro_INCLUDE_DIR})
ADD_DEFINITIONS(${Mizuiro_DEFINITIONS})
# mizuiro end

# fcppt begin
FIND_PACKAGE(Fcppt REQUIRED)
INCLUDE_DIRECTORIES(${Fcppt_INCLUDE_DIRS})
ADD_DEFINITIONS(${Fcppt_DEFINITIONS})
# fcppt end

# sge begin
FIND_PACKAGE(
	SGE REQUIRED COMPONENTS image2d image window renderer viewport input sprite config time texture systems projectile)
INCLUDE_DIRECTORIES(${SGE_INCLUDE_DIRS})
ADD_DEFINITIONS(${SGE_DEFINITIONS})
# sge end

ADD_SUBDIRECTORY(1)
ADD_SUBDIRECTORY(2)
#ADD_SUBDIRECTORY(whole)

