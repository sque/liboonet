cmake_minimum_required (VERSION 2.8)
project (liboonet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC" )

add_subdirectory(oonet)
add_subdirectory(oonet-tests)

