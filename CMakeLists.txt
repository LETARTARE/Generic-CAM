cmake_minimum_required(VERSION 2.8)

project(genericcam)

find_package(wxWidgets COMPONENTS richtext gl core base xml adv REQUIRED)
include( "${wxWidgets_USE_FILE}" )

if(UNIX)
include_directories( "/usr/include/lua5.1" )
endif(UNIX)

if(WIN32)
include_directories( "/usr/local/i586-mingw32/include/lua5.3" )
endif(WIN32)

if(WIN32)
set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -I/usr/local/i586-mingw32/include")
endif(WIN32)

set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -Wno-write-strings")


#aux_source_directory(src/3D/. files_3D)
#add_library(3D ${files_3D})

#aux_source_directory(src/command/. files_command)
#add_library(command ${files_command})

#aux_source_directory(src/controller/. files_controller)
#add_library(controller ${files_controller})

#aux_source_directory(src/generator/. files_generator)
#list(REMOVE_ITEM files_generator "src/generator/temp.cpp")
#add_library(generator ${files_generator})

#aux_source_directory(src/gui/. files_gui)
#add_library(gui ${files_gui})

#aux_source_directory(src/icon/. files_icon)
#add_library(icon ${files_icon})

#aux_source_directory(src/machine/. files_machine)
#add_library(machine ${files_machine})

#aux_source_directory(src/project/. files_project)
#add_library(project ${files_project})

add_subdirectory(src)

add_executable(genericcam src/genericcam.cpp)


target_link_libraries(genericcam
	gui
	controller
#	machine
	project
#	generator
#	command
	3D
)

if(UNIX)
target_link_libraries(genericcam
	GLU
	lua5.1
	${wxWidgets_LIBRARIES}
)
endif(UNIX)

if(WIN32)
target_link_libraries(genericcam
	opengl32
	glu32
	lua53
	${wxWidgets_LIBRARIES}
)
endif(WIN32)
