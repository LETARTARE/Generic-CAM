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
SOURCES = src/genericcam.cpp

# 3D object files:
SOURCES += src/3D/AffineTransformMatrix.cpp \
	src/3D/BoundingBox.cpp \
	src/3D/BooleanBox.cpp \
	src/3D/FileDXF.cpp \
	src/3D/FileGTS.cpp \
	src/3D/FileSTL.cpp \
	src/3D/Geometry.cpp \
	src/3D/GeometryFileAbstract.cpp \
	src/3D/IKSolver.cpp \
	src/3D/OpenGLCanvas.cpp \
	src/3D/OpenGLImage.cpp \
	src/3D/OpenGLPick.cpp \
	src/3D/Polygon3.cpp \
	src/3D/Polygon25.cpp \
	src/3D/Surface.cpp \
	src/3D/Triangle.cpp \
	src/3D/Vector3.cpp \

# 3D controller object files:
SOURCES += src/controller/Control3D.cpp \
	src/controller/Control3DAbstract.cpp \
	src/controller/ControlSpaceBall.cpp \
	src/controller/ControlSpaceMouse.cpp \
	src/controller/ControlSpaceOrb.cpp \
	src/controller/DialogSetup6DOFController.cpp \
	src/controller/guiSetup6DOFController.cpp \
	src/controller/SerialPort.cpp \
	
# Generator object files:
SOURCES += src/generator/Imprinter.cpp \
	src/generator/Octree.cpp \
	src/generator/Polygon25.cpp \
	src/generator/TPGenerator.cpp \
	src/generator/TPGeneratorFast.cpp \
	src/generator/TPGeneratorTest.cpp \
	
# GUI object files:
SOURCES += src/gui/AboutDialog.cpp \
	src/gui/AnimationFrame.cpp \
	src/gui/Control6DOFDialog.cpp \
	src/gui/ErrorFrame.cpp \
	src/gui/gui.cpp \
	src/gui/MainCanvas.cpp \
	src/gui/MainFrame.cpp \
	src/gui/ObjectFrame.cpp \
	src/gui/StockFrame.cpp \
	src/gui/TargetDialog.cpp \
	src/gui/ToolboxFrame.cpp \
	src/gui/ToolCanvas.cpp \
	src/gui/ToolPanel.cpp \
	src/gui/UnitDialog.cpp \

# machine object files:
SOURCES += src/machine/LUACodeEvaluator.cpp \
	src/machine/Machine.cpp \
	src/machine/MachineComponent.cpp \
	src/machine/MachinePosition.cpp \
	src/machine/Tool.cpp \
	src/machine/ToolElement.cpp \
	
# project object files:
SOURCES += src/project/Object.cpp \
	src/project/Project.cpp \
	src/project/Run.cpp \
	src/project/Stock.cpp \
	src/project/StockMaterial.cpp \
	src/project/Target.cpp \
	src/project/TargetPlacement.cpp \
	src/project/Toolbox.cpp \
	src/project/ToolPath.cpp \
	src/project/Unit.cpp \
	src/project/Workpiece.cpp \

# simulator object files:
SOURCES += src/simulator/MachineSimulator.cpp \
	
	
	

# Generate the object file names and dependency filenames
OBJDIR := bin_linux
OBJECTS := $(patsubst %.cpp, ${OBJDIR}/%.o, ${SOURCES})
DEPS := $(patsubst %.cpp, ${OBJDIR}/%.d, ${SOURCES})



# gcc flags:
INCFLAGS := -I./src
CXXFLAGS := `wx-config --cxxflags` -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/lua5.1 -O0 -g3 -Wall 
LDFLAGS  := `wx-config --libs gl,core,base,xml` -L/usr/local/lib -L/usr/lib
LDLIBS   := -llua5.1 -lGLU
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

Release: 	$(PROJECT)

$(PROJECT):	$(OBJECTS)
		$(CXX) -o $(PROJECT) $(OBJECTS) $(LDLIBS) $(LDFLAGS)
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
		mkdir $(OBJDIR)/src/controller
		mkdir $(OBJDIR)/src/generator
		mkdir $(OBJDIR)/src/gui
		mkdir $(OBJDIR)/src/machine
		mkdir $(OBJDIR)/src/project
		mkdir $(OBJDIR)/src/simulator
		
