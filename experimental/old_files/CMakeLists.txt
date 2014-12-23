cmake_minimum_required(VERSION 2.8)
project(RuleSSL_Python)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Threads
find_package(Threads REQUIRED)

# Python
set(Python_ADDITIONAL_VERSIONS 3.4)
FIND_PACKAGE(PythonLibs 3 REQUIRED)
FIND_PATH(PYTHON_INCLUDE_PATH Python.h
  /usr/include
  /usr/local/include)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})
SET(PYTHON_BINARIES /usr/bin/python3)

#boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK ON)

find_package(Boost COMPONENTS filesystem system program_options thread log log_setup python3 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

#Options
option(BUILD_TESTS "Build unit tests." TRUE)

#Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Strategie/include
		    ${RuleMain_SOURCE_DIR}/include/)

add_subdirectory(RuleSSL)
add_subdirectory(Strategie)
add_subdirectory(Python)

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(Tests)
endif()
