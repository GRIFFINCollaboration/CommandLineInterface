# could maybe work with lower versions as well?
cmake_minimum_required(VERSION 3.10)

# set project name
project(HelperLibraries VERSION 1.1.0 DESCRIPTION "libraries for command line arguments, useful functions, and text attributes")

# add root libraries (this needs to be done after the project name has been defined!)
find_package(ROOT REQUIRED)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

string(APPEND CMAKE_CXX_FLAGS " -pedantic -Wall -Wno-long-long -g -O3")

# if the default prefix is being used (i.e. no -DCMAKE_INSTALL_PREFIX has been used), overwrite it to $HOME (so install into ~/lib)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "$ENV{HOME}" CACHE PATH "..." FORCE)
endif()

# add libraries and set version
add_library(CommandLineInterface SHARED CommandLineInterface.cc CommandLineInterface.hh)
set_target_properties(CommandLineInterface PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(CommandLineInterface ${ROOT_LIBRARIES})

add_library(Utilities SHARED Utilities.cc Utilities.hh)
set_target_properties(Utilities PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(Utilities ${ROOT_LIBRARIES})

add_library(TextAttributes SHARED TextAttributes.cc TextAttributes.hh)
set_target_properties(TextAttributes PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(TextAttributes ${ROOT_LIBRARIES})

# add local and root include dirs for all three libraries (not actually needed for TextAttributes ...)
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})

# installation instructions
install(TARGETS CommandLineInterface DESTINATION lib)
install(TARGETS Utilities DESTINATION lib)
install(TARGETS TextAttributes DESTINATION lib)

