cmake_minimum_required (VERSION 2.6)
project (04-Fractal-Dimension)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

get_filename_component(SHARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../share"
                       ABSOLUTE  "${CMAKE_BINARY_DIR}" )

get_filename_component(EX02_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../02-Percolation"
                       ABSOLUTE  "${CMAKE_BINARY_DIR}" )
get_filename_component(EX03_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../03-Cluster-Size-Distribution"
                       ABSOLUTE  "${CMAKE_BINARY_DIR}" )
MESSAGE("${SHARE_DIR}")
MESSAGE("${EX02_DIR}")

link_directories("/usr/lib")

include_directories( include )
include_directories( "${SHARE_DIR}/include" )
include_directories( "${EX02_DIR}/include" )
include_directories( "${EX03_DIR}/include" )


add_subdirectory( src )
add_subdirectory( "${SHARE_DIR}/src" "${SHARE_DIR}/src" )
add_subdirectory( "${EX02_DIR}/src" "${EX02_DIR}/src" )
add_subdirectory( "${EX03_DIR}/src" "${EX03_DIR}/src" )


set( LIB ${LIB} fractal csd Percolation squarelattice save )

add_executable( main.out bin/main.cpp )
target_link_libraries( main.out ${LIB} )
