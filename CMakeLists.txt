cmake_minimum_required( VERSION 3.9.0 )

project( FT_GKRELLM )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FULL_PATH} )
set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH} )

find_package( Curses REQUIRED )
find_package( SDL2 REQUIRED )
find_package( GLEW REQUIRED )
find_package( OPENGL REQUIRED )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CURSES_INCLUDE_DIR} )
include_directories( ${SDL2_INCLUDE_DIR} )
include_directories( ${GLEW_INCLUDE_DIR} )
include_directories( ${OPENGL_INCLUDE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/imgui )

add_definitions( -DNDEBUG )
add_definitions( -DFULL_PATH="${FULL_PATH}" )

add_subdirectory( imgui )
add_subdirectory( src )