#CMake entry point
cmake_minimum_required (VERSION 2.8.0)
project (TB2D)

# delete CMakeCache.txt from the build directory when you edit these options
####################################################################
OPTION(USE_TEST_PROJECT "Use project for testing purposes" ON)
OPTION(USE_BOX2D "Use Box2D" ON)

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

add_subdirectory(external)

# Set c++11 as main language
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O2")

# Create library from soil2 source
set (SOIL2_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/external/SOIL2/src
)

add_subdirectory(
  external/SOIL2/src
)

# Create library from freetype2 source
set (FREETYPE2_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype-2.8.1
)

add_subdirectory(
  external/freetype-2.8.1
)

include_directories(
  ${SOIL2_INCLUDE_DIR}
  ${FREETYPE2_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/external/glfw-3.2.1/include/GLFW
  ${CMAKE_SOURCE_DIR}/external/glew-2.1.0/include
  ${CMAKE_SOURCE_DIR}/external/SOIL2/src/SOIL2
  ${CMAKE_SOURCE_DIR}/external/SOIL2/src/include
  ${CMAKE_SOURCE_DIR}/external/freetype-2.8.1/include
  ${CMAKE_SOURCE_DIR}/external/freetype-2.8.1/src
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
  GLEW
  glfw
  ${GLEW_LIBRARIES}
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

set(TB2DSOURCE
  tb2d/texture.cpp
  tb2d/texture.h
  tb2d/shader.cpp
  tb2d/shader.h
  tb2d/entity.h
  tb2d/entity.cpp
  tb2d/scene.h
  tb2d/scene.cpp
  tb2d/camera.h
  tb2d/camera.cpp
  tb2d/debugRenderer.h
  tb2d/debugRenderer.cpp
  tb2d/text.h
  tb2d/text.cpp
  tb2d/resourceManager.h
  tb2d/resourceManager.cpp
  tb2d/input.h
  tb2d/input.cpp
  tb2d/window.h
  tb2d/window.cpp
  tb2d/hud.h
  tb2d/hud.cpp
  tb2d/button.h
  tb2d/button.cpp
  tb2d/sprite.h
  tb2d/sprite.cpp
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
# TestProject                                                 #
####################################################################
if (USE_TEST_PROJECT)
  add_executable(testProject
    tb2d/window.h
    tb2d/window.cpp
    tb2d/sprite.cpp
    tb2d/sprite.h
    tb2d/scene.cpp
    tb2d/scene.h
    tb2d/camera.cpp
    tb2d/camera.h
    tb2d/text.cpp
    tb2d/text.h
    tb2d/entity.cpp
    tb2d/entity.h
    tb2d/resourceManager.cpp
    tb2d/resourceManager.h
    tb2d/texture.cpp
    tb2d/texture.h
    tb2d/shader.cpp
    tb2d/shader.h
    testProject/main.cpp
  )
  #set_target_properties(testProject PROPERTIES LINKER_LANGUAGE C)
  target_link_libraries(testProject
    ${BOX2D_LIB}
    ${ALL_GRAPHICS_LIBS}
    freetype
    SOIL2
  )
  ADD_DEPENDENCIES(testProject
    SOIL2
  )
  # Copy shaders and textures to the build directory
  file(
    COPY tb2d/shaders
    DESTINATION ${CMAKE_BINARY_DIR}
  )
  file(
    COPY tb2d/textures
    DESTINATION ${CMAKE_BINARY_DIR}
  )
  file(
    COPY tb2d/fonts
    DESTINATION ${CMAKE_BINARY_DIR}
  )
endif()
