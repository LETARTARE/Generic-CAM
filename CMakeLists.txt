cmake_minimum_required(VERSION 2.8)

project(genericcam)
#enable_language(CXX)

find_package(wxWidgets COMPONENTS gl core base html xml adv ribbon propgrid REQUIRED)
include(${wxWidgets_USE_FILE})


if(MINGW)
#	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -I/usr/local/i586-mingw32/include")

	include_directories( "/usr/local/i586-mingw32/include/lua5.3" )

	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -Wno-write-strings")

	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -DUNICODE")
	set(wxWidgets_CONFIGURATION mswu)
	
elseif(MSVC)
	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /wd4018 /wd4305 /wd4996")

	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -DUNICODE")
	set(wxWidgets_CONFIGURATION mswu)
	
else(MINGW)
	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -Wno-write-strings")
	
	include_directories( "/usr/include/lua5.3" )
	
endif(MINGW)


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
		lua53
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
		lua-5.3.5
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
		lua5.3
#		portmidi
	)
	
endif(MINGW)
