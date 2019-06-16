cmake_minimum_required(VERSION 2.6)
set(PROJECT ccc)
project(${PROJECT})


# all source files
file(GLOB SOURCES
	libs/*.h
	libs/*.c
	libs/*.cpp
	source/*.h
	source/*.cpp)

# Specify C++11 flag for g++
if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
endif()


# Include path for additional CMake library finding scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Add directory containing FindSFML.cmake to module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}")


# Find SFML
find_package( SFML 2 COMPONENTS graphics window system )

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()


if(WIN32)
	add_executable(${PROJECT} WIN32 ${SOURCES})
else()
	add_executable(${PROJECT} ${SOURCES})
endif()

target_link_libraries(${PROJECT} ${SFML_LIBRARIES})
if(WIN32)
	target_link_libraries(${PROJECT} "-lopengl32 -lglu32 -lgdi32")
endif()
