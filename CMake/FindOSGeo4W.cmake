
set(OSGEO4W_FOUND FALSE)
if(WIN32)

  find_path(OSGEO4W_ROOT NAMES OSGeo4W.bat PATHS $ENV{OSGEO4W_ROOT} )

  if(OSGEO4W_ROOT)
		set(CMAKE_INCLUDE_PATH ${OSGEO4W_ROOT}/include;${CMAKE_INCLUDE_PATH})
    set(CMAKE_LIBRARY_PATH ${OSGEO4W_ROOT}/lib;${CMAKE_LIBRARY_PATH})
    set(OSGEO4W_FOUND TRUE)
		message(STATUS "Found OSGeo4W (${OSGEO4W_ROOT})")
	else()
		message(STATUS "Could not find OSGeo4W")
	endif()

endif()
