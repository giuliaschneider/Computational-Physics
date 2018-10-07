cmake_minimum_required (VERSION 2.6)
project (code)

link_directories("/usr/lib64")
link_directories("/opt/local/var/macports/sources/rsync.macports.org/macports/release/tarballs/ports/science")

find_package(Armadillo REQUIRED) 

set (cmake -DCMAKE_BUILD_TYPE=RELEASE ..)

if ( ARMADILLO_FOUND )
  MESSAGE( "DID FIND IT!")
endif()

include_directories(${ARMADILLO_INCLUDE_DIRS})
set(LIB ${ARMADILLO_LIBRARIES})

include_directories( include )

add_subdirectory( src )
set( LIB ${LIB} Percolation )

add_executable( main.out main.cpp )
target_link_libraries( main.out ${LIB} )
