cmake_minimum_required (VERSION 2.6)
project (code)


link_directories("/usr/lib64")
#link_directories("/opt/local/var/macports/sources/rsync.macports.org/macports/release/tarballs/ports/science")


set (cmake -DCMAKE_BUILD_TYPE=RELEASE ..)

set(BUILD_SHARED_LIBS true)

#include_directories(${ARMADILLO_INCLUDE_DIRS})
#set(LIB ${ARMADILLO_LIBRARIES})

include_directories( include )
include_directories( "/home/giu/polybox/Introduction_to_CompPhys/share/include" )
include_directories( "/home/giu/polybox/Introduction_to_CompPhys/share/src" )

add_subdirectory( src )
add_subdirectory( /home/giu/polybox/Introduction_to_CompPhys/share/src /home/giu/polybox/Introduction_to_CompPhys/share/src )

set( LIB ${LIB} randomwalk save )



add_executable( main.out main.cpp )
target_link_libraries( main.out ${LIB} )
