#CMake entry point
cmake_minimum_required (VERSION 3.8)
project (TB2D)

# delete CMakeCache.txt from the build directory when you edit these options
####################################################################
OPTION(MAKE_START "Make TB2D start applications" ON)
OPTION(MAKE_DEMO_SCENES "Make TB2D demo applications" ON)
OPTION(USE_BOX2D "Use Box2D" ON)
OPTION(MAKE_BOX2DSTART "Make Box2D/RT2D box2dstart" ON)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# Compile external dependencies
find_package(OpenGL REQUIRED)

add_subdirectory (external)

include_directories(
  ${CMAKE_SOURCE_DIR}/external/glfw-3.2.1/include/GLFW
  ${CMAKE_SOURCE_DIR}/external/glew-2.1.0/include
  ${CMAKE_SOURCE_DIR}/external/SOIL2/src
  ${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/tb2d
)

link_directories(
  ${CMAKE_SOURCE_DIR}/external/glfw-3.2.1/src
  ${CMAKE_SOURCE_DIR}/external/glew-2.1.0
  ${CMAKE_SOURCE_DIR}/external/glm-0.9.8.4
  ${CMAKE_SOURCE_DIR}/external
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

set(TB2DSOURCE
  tb2d/mesh.cpp
  tb2d/mesh.h
  tb2d/texture.cpp
  tb2d/texture.h
  tb2d/shader.cpp
  tb2d/shader.h
  tb2d/box.cpp
  tb2d/box.h
  tb2d/circle.cpp
  tb2d/circle.h
  tb2d/entity.h
  tb2d/entity.cpp
  tb2d/scene.h
  tb2d/scene.cpp
  tb2d/camera.h
  tb2d/camera.cpp
  tb2d/debugRenderer.h
  tb2d/debugRenderer.cpp
)

set(SOILSOURCE
  ##SOIL IMAGE LOADER
  external/SOIL2/src/SOIL2/etc1_utils.c
  external/SOIL2/src/SOIL2/etc1_utils.h
  external/SOIL2/src/SOIL2/image_DXT.c
  external/SOIL2/src/SOIL2/image_DXT.h
  external/SOIL2/src/SOIL2/image_helper.c
  external/SOIL2/src/SOIL2/image_helper.h
  external/SOIL2/src/SOIL2/jo_jpeg.h
  external/SOIL2/src/SOIL2/pkm_helper.h
  external/SOIL2/src/SOIL2/pvr_helper.h
  external/SOIL2/src/SOIL2/SOIL2.c
  external/SOIL2/src/SOIL2/SOIL2.h
  external/SOIL2/src/SOIL2/stb_image_write.h
  external/SOIL2/src/SOIL2/stb_image.h
  external/SOIL2/src/SOIL2/stbi_DDS_c.h
  external/SOIL2/src/SOIL2/stbi_DDS.h
  external/SOIL2/src/SOIL2/stbi_ext_c.h
  external/SOIL2/src/SOIL2/stbi_ext.h
  external/SOIL2/src/SOIL2/stbi_pkm_c.h
  external/SOIL2/src/SOIL2/stbi_pkm.h
  external/SOIL2/src/SOIL2/stbi_pvr_c.h
  external/SOIL2/src/SOIL2/stbi_pvr.h
  ##END SOIL IMAGE LOADER
)

####################################################################
# box2d.a                                                          #
####################################################################
IF(USE_BOX2D)
	option(BOX2D_INSTALL "Install Box2D libs, includes, and CMake scripts" ON)
	option(BOX2D_INSTALL_DOC "Install Box2D documentation" ON)
	option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" ON)
	option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
	option(BOX2D_BUILD_EXAMPLES "Build Box2D examples" ON)

	set(BOX2D_VERSION 2.3.2)
	set(LIB_INSTALL_DIR lib${LIB_SUFFIX})

	# The Box2D library.
	add_subdirectory(external/Box2D)

	include_directories(
		${CMAKE_SOURCE_DIR}/external/Box2D
	)
	link_directories(
		${CMAKE_SOURCE_DIR}/external/Box2D
	)
	add_definitions(
	    -DBOX2D_BUILD_STATIC
	)
	set(BOX2D_LIB
	    Box2D
	)
ENDIF()

####################################################################
# Box2D/RT2D box2dstart                                            #
####################################################################
IF(MAKE_BOX2DSTART AND USE_BOX2D)
	add_executable(box2dstart
		external/Box2D/Box2D/HelloWorld/HelloWorld.cpp
	)
	target_link_libraries (box2dstart
		${BOX2D_LIB}
		${ALL_GRAPHICS_LIBS}
	)
ENDIF()

####################################################################
# DEMO_SCENES                                                      #
####################################################################
IF(MAKE_DEMO_SCENES)

ENDIF()

####################################################################
# start                                                            #
####################################################################
IF(MAKE_START)
  add_executable(start
    ${SOILSOURCE}
    ${TB2DSOURCE}
    start/main.cpp
	)
	target_link_libraries(start
    ${BOX2D_LIB}
		${ALL_GRAPHICS_LIBS}
	)
	# Copy assets/shaders/textures to the build directory
  file(
		COPY tb2d/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
  file(
		COPY tb2d/shaders
		DESTINATION ${CMAKE_BINARY_DIR}
	)
  file(
		COPY tb2d/textures
		DESTINATION ${CMAKE_BINARY_DIR}
	)
ENDIF()
