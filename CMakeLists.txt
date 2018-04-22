cmake_minimum_required(VERSION 2.8)

project(genericcam)

find_package(wxWidgets COMPONENTS richtext gl core base html xml adv REQUIRED)
include( "${wxWidgets_USE_FILE}" )

if(MINGW)
	include_directories( "/usr/local/i586-mingw32/include/lua5.3" )
#	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -I/usr/local/i586-mingw32/include")
else(MINGW)
	include_directories( "/usr/include/lua5.3" )
endif(MINGW)

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

if(MINGW)
	add_executable(genericcam src/genericcam.cpp)
	target_link_libraries(genericcam
		gui
		controller
		project
		3D
		${wxWidgets_LIBRARIES}
		opengl32
		glu32
		lua53
#		portmidi
	)
else(MINGW)
	add_executable(genericcam src/genericcam.cpp)
	target_link_libraries(genericcam
		gui
		controller
		project
		3D
		${wxWidgets_LIBRARIES}
		GL
		GLU
		lua5.3
		portmidi
	)
endif(MINGW)

