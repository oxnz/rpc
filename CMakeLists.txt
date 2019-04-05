cmake_minimum_required(VERSION 2.8)

project(calc)

set(CMAKE_CXX_STANDARD 14)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/gen-cpp")
include_directories("/usr/local/include")
SET(CMAKE_CXX_FLAGS "-DHAVE_CONFIG_H")
set(calc_SOURCES
	gen-cpp/Calculator.cpp
	gen-cpp/SharedService.cpp
	gen-cpp/shared_constants.cpp
	gen-cpp/shared_types.cpp
	gen-cpp/calc_constants.cpp
	gen-cpp/calc_types.cpp
)
add_library(calc STATIC ${calc_SOURCES})
target_link_libraries(calc thrift)
add_custom_command(OUTPUT ${calc_SOURCES}
	COMMAND thrift --gen cpp -r ${PROJECT_SOURCE_DIR}/calc.thrift
)
add_executable(server server.cpp)
target_link_libraries(server calc)
target_link_libraries(server thrift)
if (ZLIB_FOUND)
	target_link_libraries(server ${ZLIB_LIBRARIES})
endif()

add_executable(client client.cpp)
target_link_libraries(client calc)
target_link_libraries(client thrift)
if (ZLIB_FOUND)
	target_link_libraries(client ${ZLIB_LIBRARIES})
endif()

