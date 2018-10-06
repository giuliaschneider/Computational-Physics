cmake_minimum_required (VERSION 2.6)
project (02-Percolation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (cmake -DCMAKE_BUILD_TYPE=RELEASE ..)

get_filename_component(SHARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../share"
                       ABSOLUTE  "${CMAKE_BINARY_DIR}" )
MESSAGE("${SHARE_DIR}")



link_directories("/usr/lib64")

include_directories( include )
include_directories( "${SHARE_DIR}/include" )

add_subdirectory( src )
add_subdirectory( "${SHARE_DIR}/src" "${SHARE_DIR}/src" )
set( LIB ${LIB} Percolation squarelattice)

add_executable( main.out bin/main.cpp )
target_link_libraries( main.out ${LIB} )
