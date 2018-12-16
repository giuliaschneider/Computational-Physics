cmake_minimum_required (VERSION 2.6)
project (12-Conjugate-Gradient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Armadillo REQUIRED)
if ( ARMADILLO_FOUND )
  MESSAGE( "DID FIND IT!")
endif()

get_filename_component(SHARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../11-Relaxation-Methods"
                       ABSOLUTE  "${CMAKE_BINARY_DIR}")

link_directories("/usr/lib")

include_directories( include )
include_directories( "${SHARE_DIR}/include" )
include_directories(${ARMADILLO_INCLUDE_DIRS})
set(LIB ${LIB} ${ARMADILLO_LIBRARIES})

add_subdirectory( src )
add_subdirectory( "${SHARE_DIR}/src" "${SHARE_DIR}/src" )
set( LIB ${LIB} cg fd)

add_executable( main.out bin/main.cpp )
target_link_libraries( main.out ${LIB}  ${ARMADILLO_LIBRARIES} )
