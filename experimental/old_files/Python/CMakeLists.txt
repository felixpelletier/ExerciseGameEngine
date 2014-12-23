project(Python)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

#boost (non static)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK ON)

find_package(Boost COMPONENTS system python3 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})


add_library(rule_python SHARED ${SOURCE_FILES})
set_target_properties(rule_python PROPERTIES PREFIX "")
target_link_libraries(rule_python rule-strategie ${Boost_LIBRARIES})
