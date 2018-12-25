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
	src/controller/guiSetup6DOFController.cpp \
	src/controller/SerialPort.cpp \
	src/controller/MidiPort.cpp \

	
# GUI object files:
SOURCES += \
src/gui/DialogSetupStereo3D.cpp \
src/gui/FrameMain.cpp \
src/gui/FrameParent.cpp \
src/gui/DialogToolpathGenerator.cpp \
src/gui/guiSetupStereo3D.cpp \
src/gui/gui.cpp \
src/gui/DialogAnimation.cpp \
src/gui/CanvasTool.cpp \
src/gui/DialogToolbox.cpp \
src/gui/DialogStockMaterial.cpp \
src/gui/DialogRun.cpp \
src/gui/DialogObjectTransformation.cpp \
src/gui/DisplaySettings.cpp \
src/gui/DialogPlacement.cpp \
src/gui/DialogMachineDebugger.cpp \
src/gui/PanelTool.cpp \
src/gui/CanvasMachine.cpp \
src/gui/CanvasMain.cpp \
src/gui/CanvasStereoTest.cpp \
src/gui/DialogMachineControl.cpp \
src/gui/DialogSetupMidi.cpp \
src/gui/DialogSetupUnits.cpp \
src/gui/DialogTestGCode.cpp \
src/gui/DialogToolWizard.cpp \
src/gui/DialogWorkpiece.cpp \
src/gui/DnDFile.cpp \
src/gui/PanelTopView.cpp \
src/gui/TreeItem.cpp \
src/gui/TreeSetup.cpp \


# math functions
SOURCES += \
	src/math/Unit.cpp \
	src/math/MathParser.cpp \


# Project manipultion commands:
SOURCES += \
src/project/command/CommandObjectDelete.cpp \
src/project/command/CommandObjectLoad.cpp \
src/project/command/CommandObjectRename.cpp \
src/project/command/CommandObjectSetColor.cpp \
src/project/command/CommandObjectTransform.cpp \
src/project/command/CommandProjectRename.cpp \
src/project/command/CommandRunAdd.cpp \
src/project/command/CommandRunGeneratorAdd.cpp \
src/project/command/CommandRunGeneratorDelete.cpp \
src/project/command/CommandRunGeneratorUpdate.cpp \
src/project/command/CommandRunMachineLoad.cpp \
src/project/command/CommandRunRemove.cpp \
src/project/command/CommandRunRename.cpp \
src/project/command/CommandRunToolAdd.cpp \
src/project/command/CommandRunToolRemove.cpp \
src/project/command/CommandRunWorkpieceAssign.cpp \
src/project/command/CommandRunWorkpieceTransform.cpp \
src/project/command/CommandWorkpieceAdd.cpp \
src/project/command/CommandWorkpieceDelete.cpp \
src/project/command/CommandWorkpieceObjectAssign.cpp \
src/project/command/CommandWorkpieceObjectRemove.cpp \
src/project/command/CommandWorkpieceObjectTransform.cpp \
src/project/command/CommandWorkpieceRename.cpp \


# Generator object files:
SOURCES += \
	src/project/generator/GeneratorPositioningDrills.cpp \
	src/project/generator/GeneratorLoadFromFile.cpp \
	src/project/generator/GeneratorAreaGridDexel.cpp \
	src/project/generator/DexelTarget.cpp \
	src/project/generator/Field.cpp \
	src/project/generator/GeneratorTest.cpp \
	src/project/generator/GeneratorAreaMillingDynamic.cpp \
	src/project/generator/GeneratorCollection.cpp \
	src/project/generator/GeneratorDexel.cpp \
	src/project/generator/GeneratorDrillDexel.cpp \
	src/project/generator/GeneratorNone.cpp \
	src/project/generator/GeneratorOutlineDexel.cpp \
	src/project/generator/GeneratorSurfaceDexel.cpp \
	src/project/generator/Imprinter.cpp \
	src/project/generator/ProtoToolpath.cpp \
	src/project/generator/ToolpathGeneratorThread.cpp \
	src/project/generator/VoxelVolume.cpp \
	src/project/generator/Direction.cpp \
	src/project/generator/Generator.cpp \


# machine object files:
SOURCES += \
src/project/machine/Machine.cpp \
src/project/machine/MachineSimulator.cpp \
src/project/machine/NelderMeadOptimizer.cpp \
src/project/machine/CNCPosition.cpp \
src/project/machine/GCodeBlock.cpp \
src/project/machine/LUACodeEvaluator.cpp \
src/project/machine/MachineComponent.cpp \
src/project/machine/CNCInterpreter.cpp \

	
# project object files:
SOURCES += \
	src/project/Workpiece.cpp \
	src/project/ToolPath.cpp \
	src/project/Object.cpp \
	src/project/ObjectPlacement.cpp \
	src/project/Project.cpp \
	src/project/ProjectView.cpp \
	src/project/Run.cpp \
	src/project/StockFile.cpp \
	src/project/StockMaterial.cpp \
	src/project/Support.cpp \
	src/project/Tool.cpp \
	src/project/ToolBox.cpp \
	src/project/FlipDrillPattern.cpp \


	
	

# Generate the object file names and dependency filenames
OBJDIR := bin_linux
OBJECTS := $(patsubst %.cpp, ${OBJDIR}/%.o, ${SOURCES})
DEPS := $(patsubst %.cpp, ${OBJDIR}/%.d, ${SOURCES})



# gcc flags:
INCFLAGS := -I./src
CXXFLAGS := `wx-config --cxxflags` -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/lua5.3 -O3 -Wall -Wno-write-strings
LDFLAGS  := `wx-config --libs richtext,gl,core,base,html,xml,adv` -L/usr/local/lib -L/usr/lib
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
		
