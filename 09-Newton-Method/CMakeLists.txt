cmake_minimum_required (VERSION 2.6)
project (code)

link_directories("/usr/lib64")


find_package(Armadillo REQUIRED) 

set (cmake -DCMAKE_BUILD_TYPE=RELEASE ..)

if ( ARMADILLO_FOUND )
  MESSAGE( "DID FIND IT!")
endif()

include_directories(${ARMADILLO_INCLUDE_DIRS})
set(LIB ${ARMADILLO_LIBRARIES})

include_directories( include )
add_subdirectory( src )
set( LIB ${LIB} Nullstelle )

add_executable( main.out main.cpp )
target_link_libraries( main.out ${LIB} )
