# COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
# 
# @author Leyuan Pan
# @date Jun 01, 2018
# 
cmake_minimum_required(VERSION 3.15.3)
project(cage VERSION 0.0.0 LANGUAGES CXX)

# Options
option(BUILD_TESTS        "Enable building testing codes"    OFF)
option(BUILD_DOCS         "Build documentation with doxygen" OFF)
option(DEBUG              "Build in debug mode"              OFF)

# Set cmake build type
if(NOT CMAKE_BUILD_TYPE)
	if(DEBUG)
		set(CMAKE_BUILD_TYPE Debug)
	else(DEBUG)
		set(CMAKE_BUILD_TYPE Release)
	endif(DEBUG)
endif()

# Compile options and linker flags
set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS}   -Wall -Wextra -Wno-sign-compare -fsigned-char -ffast-math")
set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-sign-compare -fsigned-char -ffast-math")

# Inclusion
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Target properties default values
set(CMAKE_CXX_STANDARD               17)
set(CMAKE_CXX_STANDARD_REQUIRED      ON)
set(CMAKE_CXX_EXTENSIONS             OFF)
set(CMAKE_SKIP_BUILD_RPATH           ON)
if(BUILD_SHARED_LIBS)
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()
if(DEBUG)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
else()
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()

# Find boost libraries
if(BUILD_SHARED_LIBS)
	set(Boost_USE_STATIC_LIBS OFF)
else()
	set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(Boost "1.71.0" REQUIRED COMPONENTS headers filesystem)

# Set sources
set(SRCS
    src/cage/controller.cpp
    src/cage/http_session.cpp
    src/cage/http_view.cpp
    src/cage/listener.cpp
    src/cage/server.cpp
    src/cage/websock_session.cpp
    src/cage/websock_view.cpp
    )
################ Build LIBRARY ################
add_library(cage ${SRCS})
target_link_libraries(cage PUBLIC pthread)
target_include_directories(cage PUBLIC "include")
target_include_directories(cage PRIVATE "src")
target_include_directories(cage PUBLIC "include/jthread")
if(BUILD_SHARED_LIBS)
	set_target_properties(cage PROPERTIES VERSION ${PROJECT_VERSION})
endif()

################ Build TEST ################
if(BUILD_TESTS)
	include(test/test.cmake)
endif()

################ Build DOCS ################
if(BUILD_DOCS)
	include(docs/docs.cmake)
endif()
