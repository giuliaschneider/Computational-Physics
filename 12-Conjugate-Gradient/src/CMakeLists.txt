set ( SOURCES poisson2d.cpp PDEintegrator.cpp)

add_library( fd STATIC ${SOURCES} )