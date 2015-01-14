cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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

find_package(Boost COMPONENTS system python3 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

#Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB ALL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_target(copy_assets)
add_custom_command(TARGET copy_assets POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E
                         copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)

add_subdirectory(tinyobjloader)

file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_executable(experiment ${SRC_FILES})
target_link_libraries(experiment tinyobjloader ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
add_dependencies(experiment copy_assets)


add_custom_target(run
    COMMAND experiment
    DEPENDS experiment
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
