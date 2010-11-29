###############################################################################
## Name               : Makefile
## Purpose            : Main makefile
## Platform dependent : No
## Author             : Tobias Schaefer
## Created            : 12.09.2010
## Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
## Licence            : GNU General Public License version 3.0 (GPLv3)
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
##
##$LastChangedDate: $
##$Revision: $
##$LastChangedBy: $
###############################################################################

## macro definitions:

PROJECT := genericcam

# Main object file:
SOURCES = src/GenericCAM.cpp

# 3D object files:
SOURCES += src/3D/Geometry.cpp \
	src/3D/OpenGLCanvas.cpp \
	src/3D/Vector3.cpp \
	src/3D/IKSolver.cpp \
	src/3D/AffineTransformMatrix.cpp \
	src/3D/CSGSurface.cpp \

# CSGLib object files:
SOURCES += src/CSGLib/Face.cpp \
	src/CSGLib/Vector.cpp \
	src/CSGLib/BooleanModeller.cpp \
	src/CSGLib/Bound.cpp \
	src/CSGLib/Color.cpp \
	src/CSGLib/Solid.cpp \
	src/CSGLib/Segment.cpp \
	src/CSGLib/Line.cpp \
	src/CSGLib/VectorSet.cpp \
	src/CSGLib/Object3D.cpp \
	src/CSGLib/Vertex.cpp \
	src/CSGLib/ColorSet.cpp \
	src/CSGLib/VertexSet.cpp \
	src/CSGLib/FaceSet.cpp \
	src/CSGLib/IntSet.cpp \

# simulator object files:
SOURCES += src/simulator/Workpiece.cpp \
	src/simulator/LUACodeEvaluator.cpp \
	src/simulator/Toolbox.cpp \
	src/simulator/MachineComponent.cpp \
	src/simulator/Machine.cpp \
	src/simulator/ToolPath.cpp \
	src/simulator/Tool.cpp \
	src/simulator/MachinePosition.cpp \
	src/simulator/MachineSimulator.cpp \
	src/simulator/ToolElement.cpp \

# 3D controller object files:
SOURCES += src/controller/SerialPort.cpp \
	src/controller/Control3DAbstract.cpp \
	src/controller/ControlSpaceBall.cpp \
	src/controller/ControlSpaceMouse.cpp \
	src/controller/Control3D.cpp \
	src/controller/ControlSpaceOrb.cpp \

# GUI object files:
SOURCES += src/gui/ToolPanel.cpp \
	src/gui/MainFrame.cpp \
	src/gui/ErrorFrame.cpp \
	src/gui/MachineCanvas.cpp \
	src/gui/ToolCanvas.cpp \
	src/gui/DataCanvas.cpp \
	src/gui/AboutDialog.cpp \
	src/gui/gui.cpp \
	src/gui/DataFrame.cpp \
	src/gui/Control6DOFDialog.cpp \
	src/gui/ToolboxFrame.cpp \

# Generate the object file names and dependency filenames
OBJDIR := bin_linux
OBJECTS := $(patsubst %.cpp, ${OBJDIR}/%.o, ${SOURCES})
DEPS := $(patsubst %.cpp, ${OBJDIR}/%.d, ${SOURCES})



# gcc flags:
INCFLAGS := -I./src
CXXFLAGS := `wx-config --cxxflags` -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/lua5.1 -O0 -g3 -Wall 
LDFLAGS  := `wx-config --libs gl,core,base,xml` -L/usr/local/lib -L/usr/lib
LDLIBS   := -llua5.1
#REZFLAGS := `wx-config --rez-flags`

ifdef FINAL
    EXTRAFLAGS := -MD -O2 -fno-rtti -fno-exceptions -fomit-frame-pointer
else
    EXTRAFLAGS := -MD -g
endif

## Search paths

#vpath %.cpp	src
vpath %.o	$(OBJDIR)/src
#vpath %.d	$(OBJDIR)/src

## target definitions

# Include all dependencies
#-include $(OBJECTPATH)/$(DEPS)

.PHONY : all clean

all:	$(PROJECT)

$(PROJECT):	$(OBJECTS)
		$(CXX) $(LDFLAGS) -o $(PROJECT) $(OBJECTS) $(LDLIBS)
#ifdef RELEASE
#		strip $(PROJECT)
#endif



# for resources (later)
#$(PROJECT).o: $(PROJECT).rc
#		windres -i $(PROJECT).rc -o $(PROJECT)_resources.o $(REZFLAGS)
 
#clean:
#		rm -f *.o $(PROGRAM)

## suffix rules

#.SUFFIXES:	.o .cpp
  
#.cpp.o :
$(OBJECTS) : $(SOURCES) | $(OBJDIR)
		$(CXX) -c $(CXXFLAGS) -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$(@:${OBJDIR}/%.o=%.cpp)"
		

# How to automate the following correctly?
$(OBJDIR) :
		@echo 'Making directory structure...'
		mkdir $(OBJDIR)
		mkdir $(OBJDIR)/src
		mkdir $(OBJDIR)/src/3D
		mkdir $(OBJDIR)/src/CSGLib
		mkdir $(OBJDIR)/src/simulator
		mkdir $(OBJDIR)/src/controller
		mkdir $(OBJDIR)/src/gui
		