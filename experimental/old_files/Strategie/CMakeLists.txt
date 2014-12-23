project(Strategie)

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_library(rule-strategie ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(rule-strategie rule-ssl ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
