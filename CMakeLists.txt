cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME MyProject)

project(${PROJECT_NAME} VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/macros)

include(GlibCompileResourcesSupport)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(RESOURCE_LIST
	STRIPBLANKS mainWindow.glade
	)

compile_gresources(
	RESOURCE_FILE
	XML_OUT
	TYPE EMBED_C
	RESOURCES ${RESOURCE_LIST}
	PREFIX /org/bytesunited/myproject
	)

add_custom_target(
	gladeGeneratedResource
	ALL
	DEPENDS ${RESOURCE_FILE}
	)

add_executable(${PROJECT_NAME} main.cpp build/resources.c)

find_package(PkgConfig)
pkg_search_module(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})