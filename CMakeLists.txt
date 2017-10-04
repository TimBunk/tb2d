#CMake entry point
cmake_minimum_required (VERSION 3.5.1)
project (TB2D)

# delete CMakeCache.txt from the build directory when you edit these options
####################################################################
OPTION(MAKE_START "Make TB2D start applications" ON)
OPTION(MAKE_THERESTLESSTOMBS "Make TheRestlessTombs" ON)
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

# Find sdl2 pkg
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/external/SDL2/")
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR})

include_directories(
  ${CMAKE_SOURCE_DIR}/external/glew-2.1.0/include
  ${CMAKE_SOURCE_DIR}/external/SOIL2/src
  ${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/tb2d
)

link_directories(
  ${CMAKE_SOURCE_DIR}/external/glew-2.1.0
  ${CMAKE_SOURCE_DIR}/external/glm-0.9.8.4
  ${CMAKE_SOURCE_DIR}/external/SDL2_TTF
  ${CMAKE_SOURCE_DIR}/external
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
  GLEW
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
  tb2d/text.h
  tb2d/text.cpp
  tb2d/resourceManager.h
  tb2d/resourceManager.cpp
  tb2d/shape.h
  tb2d/shape.cpp
  tb2d/configure.h
  tb2d/configure.cpp
  tb2d/input.h
  tb2d/input.cpp
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
# TheRestlessTombs                                                 #
####################################################################
IF(MAKE_THERESTLESSTOMBS)
add_executable(trt
  ${SOILSOURCE}
  ${TB2DSOURCE}
  TheRestlessTombs/main.cpp
  TheRestlessTombs/armoredOrc.cpp 
  TheRestlessTombs/armoredOrc.h 
  TheRestlessTombs/babyOrc.cpp 
  TheRestlessTombs/babyOrc.h 
  TheRestlessTombs/bomb.cpp 
  TheRestlessTombs/bomb.h 
  TheRestlessTombs/bomberOrc.cpp 
  TheRestlessTombs/bomberOrc.h 
  TheRestlessTombs/boss.cpp 
  TheRestlessTombs/boss.h 
  TheRestlessTombs/bossOrc.cpp 
  TheRestlessTombs/bossOrc.h 
  TheRestlessTombs/crate.cpp 
  TheRestlessTombs/crate.h 
  TheRestlessTombs/damagePotion.cpp 
  TheRestlessTombs/damagePotion.h 
  TheRestlessTombs/destructable.cpp 
  TheRestlessTombs/destructable.h
  TheRestlessTombs/door.cpp 
  TheRestlessTombs/door.h 
  TheRestlessTombs/enemy.cpp 
  TheRestlessTombs/enemy.h 
  TheRestlessTombs/gold.cpp 
  TheRestlessTombs/gold.h 
  TheRestlessTombs/healthPotion.cpp 
  TheRestlessTombs/healthPotion.h 
  TheRestlessTombs/level1.cpp 
  TheRestlessTombs/level1.h 
  TheRestlessTombs/lootChest.cpp 
  TheRestlessTombs/lootChest.h 
  TheRestlessTombs/necromancerOrc.cpp 
  TheRestlessTombs/necromancerOrc.h 
  TheRestlessTombs/orc.cpp 
  TheRestlessTombs/orc.h 
  TheRestlessTombs/person.cpp 
  TheRestlessTombs/person.h 
  TheRestlessTombs/player.cpp 
  TheRestlessTombs/player.h 
  TheRestlessTombs/potion.cpp  
  TheRestlessTombs/potion.h 
  TheRestlessTombs/psychoOrc.cpp 
  TheRestlessTombs/psychoOrc.h 
  TheRestlessTombs/room.cpp 
  TheRestlessTombs/room.h 
  TheRestlessTombs/shop.cpp 
  TheRestlessTombs/shop.h 
  TheRestlessTombs/speedPotion.cpp 
  TheRestlessTombs/speedPotion.h 
  TheRestlessTombs/wall.cpp 
  TheRestlessTombs/wall.h
  TheRestlessTombs/b2entity.cpp 
  TheRestlessTombs/b2entity.h 
)
target_link_libraries(trt
  ${BOX2D_LIB}
  ${ALL_GRAPHICS_LIBS}
  ${SDL2_LIBRARIES} 
  ${SDL2IMAGE_LIBRARIES}
  ${SDL2_MIXER_LIBRARIES}
  ${SDL2_TTF_LIBRARY}
)
# Copy shaders to the build directory
file(
  COPY tb2d/shaders
  DESTINATION ${CMAKE_BINARY_DIR}
)
file(
  COPY TheRestlessTombs/textures
  DESTINATION ${CMAKE_BINARY_DIR}
)
ENDIF()

####################################################################
# start                                                            #
####################################################################
IF(MAKE_START)
  add_executable(start
    ${SOILSOURCE}
    ${TB2DSOURCE}
    start/main.cpp
    start/game.h
    start/game.cpp
    start/player.h
    start/player.cpp
  )
	target_link_libraries(start
    ${BOX2D_LIB}
    ${ALL_GRAPHICS_LIBS}
    ${SDL2_LIBRARIES} 
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARY}
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
  file(
		COPY tb2d/fonts
		DESTINATION ${CMAKE_BINARY_DIR}
	)
ENDIF()
