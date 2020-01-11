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
###############################################################################

## macro definitions:

PROJECT := genericcam

# Main object file:
SOURCES = src/genericcam.cpp

# 3D object files:
SOURCES += \
        src/3D/AffineTransformMatrix.cpp \
        src/3D/BooleanBox.cpp \
        src/3D/BoundingBox.cpp \
        src/3D/FileDXF.cpp \
        src/3D/FileGTS.cpp \
        src/3D/FileSTL.cpp \
        src/3D/Geometry.cpp \
        src/3D/GeometryFileAbstract.cpp \
        src/3D/Hull.cpp \
        src/3D/Octree.cpp \
        src/3D/OctreeGenerator.cpp \
        src/3D/OpenGLCanvas.cpp \
        src/3D/OpenGLImage.cpp \
        src/3D/OpenGLLight.cpp \
        src/3D/OpenGLMaterial.cpp \
        src/3D/OpenGLPick.cpp \
        src/3D/Polygon25.cpp \
        src/3D/Polygon3.cpp \
        src/3D/Quadtree.cpp \
        src/3D/Triangle.cpp \
        src/3D/Vector3.cpp \


# 3D controller object files:
SOURCES += \
        src/controller/Control3D.cpp \
        src/controller/Control3DAbstract.cpp \
        src/controller/ControlSpaceBall.cpp \
        src/controller/ControlSpaceMouse.cpp \
        src/controller/ControlSpaceOrb.cpp \
        src/controller/DialogSetup6DOFController.cpp \
        src/controller/MidiPort.cpp \
        src/controller/SerialPort.cpp \
        src/controller/guiSetup6DOFController.cpp \

	
# GUI object files:
SOURCES += \
	src/gui/CanvasMachine.cpp \
        src/gui/CanvasMain.cpp \
        src/gui/CanvasStereoTest.cpp \
        src/gui/CanvasTool.cpp \
        src/gui/CollectionFilepaths.cpp \
        src/gui/CollectionUnits.cpp \
        src/gui/DialogAnimation.cpp \
        src/gui/DialogJobSetup.cpp \
        src/gui/DialogObjectTransformation.cpp \
        src/gui/DialogPostProcess.cpp \
        src/gui/DialogSetupMidi.cpp \
        src/gui/DialogSetupPaths.cpp \
        src/gui/DialogSetupStereo3D.cpp \
        src/gui/DialogSetupUnits.cpp \
        src/gui/DialogTestGCode.cpp \
        src/gui/DialogToolpathGenerator.cpp \
        src/gui/DnDFile.cpp \
        src/gui/FrameMain.cpp \
        src/gui/FrameParent.cpp \
        src/gui/PanelTool.cpp \
        src/gui/SettingsStereo3D.cpp \
        src/gui/TreeItem.cpp \
        src/gui/TreeSetup.cpp \
        src/gui/gui.cpp \
        src/gui/guiSetupStereo3D.cpp \


# math functions
SOURCES += \
        src/math/MathParser.cpp \
        src/math/MatlabFile.cpp \
        src/math/MatlabMatrix.cpp \
        src/math/NelderMeadOptimizer.cpp \
        src/math/Unit.cpp \


# Project manipultion commands:
SOURCES += \
        src/project/command/CommandObjectLoad.cpp \
        src/project/command/CommandObjectRemove.cpp \
        src/project/command/CommandObjectRename.cpp \
        src/project/command/CommandObjectTransform.cpp \
        src/project/command/CommandProjectRename.cpp \
        src/project/command/CommandRunAdd.cpp \
        src/project/command/CommandRunGeneratorAdd.cpp \
        src/project/command/CommandRunGeneratorDelete.cpp \
        src/project/command/CommandRunGeneratorRename.cpp \
        src/project/command/CommandRunGeneratorUpdate.cpp \
        src/project/command/CommandRunRemove.cpp \
        src/project/command/CommandRunRename.cpp \
        src/project/command/CommandRunSetBoundingBox.cpp \
        src/project/command/CommandRunSetCorrdinateSystem.cpp \
        src/project/command/CommandRunSetObject.cpp \
        src/project/command/CommandRunSetStockBox.cpp \
        src/project/command/CommandRunSetStockObject.cpp \
        src/project/command/CommandRunSetStockOrigin.cpp \
        src/project/command/CommandRunSetStockType.cpp \

# Generator object files:
SOURCES += \
        src/project/generator/CNCPosition.cpp \
        src/project/generator/CNCSimulator.cpp \
        src/project/generator/DexelTarget.cpp \
        src/project/generator/Direction.cpp \
        src/project/generator/Field.cpp \
        src/project/generator/Generator.cpp \
        src/project/generator/GeneratorAreaGridDexel.cpp \
        src/project/generator/GeneratorAreaMillingDynamic.cpp \
        src/project/generator/GeneratorDexel.cpp \
        src/project/generator/GeneratorDrillDexel.cpp \
        src/project/generator/GeneratorFactory.cpp \
        src/project/generator/GeneratorLoadFromFile.cpp \
        src/project/generator/GeneratorOutlineDexel.cpp \
        src/project/generator/GeneratorSurfaceDexel.cpp \
        src/project/generator/GeneratorTest.cpp \
        src/project/generator/Imprinter.cpp \
        src/project/generator/ProtoToolpath.cpp \
        src/project/generator/VoxelVolume.cpp \
        src/project/post/CollectionPostProcessor.cpp \
        src/project/post/GenericPostProcessor.cpp \
        src/project/post/LUAPostProcessor.cpp \
        src/project/post/PostProcessor.cpp \


# machine object files:
SOURCES += \
        src/project/machine/GCodeBlock.cpp \

	
# project object files:
SOURCES += \
        src/project/JSON.cpp \
        src/project/Object.cpp \
        src/project/Project.cpp \
        src/project/ProjectView.cpp \
        src/project/Run.cpp \
        src/project/Selection.cpp \
        src/project/Tool.cpp \
        src/test/TestSelection.cpp \
        src/test/test.cpp \


# Generate the object file names and dependency filenames
OBJDIR := bin_linux
OBJECTS := $(patsubst %.cpp, ${OBJDIR}/%.o, ${SOURCES})
DEPS := $(patsubst %.cpp, ${OBJDIR}/%.d, ${SOURCES})


# gcc flags:
INCFLAGS := -I./src
CXXFLAGS := `wx-config --cxxflags` -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/lua5.3 -O3 -Wall -Wno-write-strings
LDFLAGS  := `wx-config --libs richtext,gl,core,base,html,xml,adv,ribbon,propgrid` -L/usr/local/lib -L/usr/lib
LDLIBS   := -llua5.3 -lGL -lGLU
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
		mkdir $(OBJDIR)/src/gui
		mkdir $(OBJDIR)/src/math
		mkdir $(OBJDIR)/src/project
		mkdir $(OBJDIR)/src/project/command
		mkdir $(OBJDIR)/src/project/generator
		mkdir $(OBJDIR)/src/project/machine
		mkdir $(OBJDIR)/src/project/post
		mkdir $(OBJDIR)/src/test
		
