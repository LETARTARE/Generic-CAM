cmake_minimum_required(VERSION 2.8)

project(genericcam)

find_package(wxWidgets COMPONENTS richtext gl core base html xml adv ribbon propgrid REQUIRED)
include(${wxWidgets_USE_FILE})

if(MINGW)
#	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -I/usr/local/i586-mingw32/include")
endif(MINGW)

if(MINGW)
#	include_directories( "/usr/local/i586-mingw32/include/lua5.3" )
else(MINGW)
#	include_directories( "/usr/include/lua5.3" )
endif(MINGW)

if(MSVC OR MINGW)
	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -DUNICODE")
	set(wxWidgets_CONFIGURATION mswu)
endif(MSVC OR MINGW)

if(NOT MSVC)
	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -Wno-write-strings")
endif(NOT MSVC)

add_subdirectory(src)

if(MINGW)
	add_executable(genericcam src/genericcam.cpp)
		target_link_libraries(
		genericcam
		gui
		controller
		project
		3D
		math
		cppunittest
		${wxWidgets_LIBRARIES}
		opengl32
		glu32
#		lua53
	)
elseif(MSVC)
	add_executable(genericcam WIN32 src/genericcam.cpp)
	target_link_libraries(
		genericcam
		gui
		controller
		project
		3D
		math
		cppunittest
		${wxWidgets_LIBRARIES}
#		OpenGL
#		lua-5.3.5
	)
else(MINGW)
	add_executable(genericcam src/genericcam.cpp)
	target_link_libraries(
		genericcam
		gui
		controller
		project
		3D
		math
		cppunittest
		${wxWidgets_LIBRARIES}
		GL
		GLU
#		lua5.3
#		portmidi
	)
endif(MINGW)
