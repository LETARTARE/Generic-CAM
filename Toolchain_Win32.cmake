# Select this toolchain with:
#
# mkdir bin_win
# cd bin_win
# cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain_Win32.cmake ../.
# make
#

SET(CMAKE_SYSTEM_NAME Windows)
SET(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   i686-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER  i686-w64-mingw32-windres)

#SET(wxWidgets_ROOT_DIR /usr/bin/i686-w64-mingw32)
SET(wxWidgets_CONFIG_EXECUTABLE ${wxWidgets_ROOT_DIR}/bin/wx-config)
SET(wxWidgets_LIB_DIR ${wxWidgets_ROOT_DIR}/lib)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /usr/i686-w64-mingw32 ${wxWidgets_ROOT_DIR})
include_directories(SYSTEM ${wxWidgets_ROOT_DIR}/include)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM FIRST)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
