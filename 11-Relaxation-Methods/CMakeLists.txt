cmake_minimum_required (VERSION 2.6)
project (11-Relaxation-Methods)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Armadillo REQUIRED)
if ( ARMADILLO_FOUND )
  MESSAGE( "DID FIND IT!")
endif()


link_directories("/usr/lib")

include_directories( include )
include_directories(${ARMADILLO_INCLUDE_DIRS})
set(LIB ${LIB} ${ARMADILLO_LIBRARIES})

add_subdirectory( src )
set( LIB ${LIB} fd )

add_executable( main.out bin/main.cpp )
target_link_libraries( main.out ${LIB}  ${ARMADILLO_LIBRARIES})
