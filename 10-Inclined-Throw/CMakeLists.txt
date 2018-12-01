cmake_minimum_required (VERSION 2.6)
project (10-Inclinded-Throw)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

get_filename_component(SHARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../share"
                       ABSOLUTE  "${CMAKE_BINARY_DIR}" )
MESSAGE("${SHARE_DIR}")

find_package(Armadillo REQUIRED)
if ( ARMADILLO_FOUND )
  MESSAGE( "DID FIND IT!")
endif()

link_directories("/usr/lib")

include_directories( include )
include_directories( "${SHARE_DIR}/include" )
include_directories(${ARMADILLO_INCLUDE_DIRS})
set(LIB ${LIB} ${ARMADILLO_LIBRARIES})

add_subdirectory( src )
add_subdirectory( "${SHARE_DIR}/src" "${SHARE_DIR}/src" )

set( LIB ${LIB} rk save)

add_executable( main.out bin/main.cpp )
target_link_libraries( main.out ${LIB}  ${ARMADILLO_LIBRARIES})
