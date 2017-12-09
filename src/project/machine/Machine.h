///////////////////////////////////////////////////////////////////////////////
// Name               : Machine.h
// Purpose            : CNC machine
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef MACHINE_H_
#define MACHINE_H_

/*!\class Machine
 * \ingroup Machine
 * \brief CNC Machine.
 *
 * This class contains all parts for displaying and animating a CNC machine. The functionality
 * herein is mostly used for displaying the machine. The coordination of the movement is done
 * in the ToolPath class.
 *
 * This class provides additional information on the form of the toolhead. These informations
 * are used to prevent the toolhead from colliding with the workpiece. The collision prevention
 * is done by the Generator%s derived from the GeneratorDexelTarget on initializing.
 *
 * Later this class will be used for collision detection.
 *
 * Order of execution according to "The NIST RS274NGC Interpreter - Version 3"
 *
 *  -# comment (includes message).
 *  -# set feed rate mode (G93, G94 — inverse time or per minute). (G-modal-mode 5 - feedrate mode)
 *  -# set feed rate (F).
 *  -# set spindle speed (S).
 *  -# select tool (T).
 *  -# change tool (M6). (M-modal-mode 6 - tool change)
 *  -# spindle on or off (M3, M4, M5). (M-modal-mode 7 - spindle turning)
 *  -# coolant on or off (M7, M8, M9). (M-modal-mode 8 - coolant)
 *  -# enable or disable overrides (M48, M49). (M-modal-mode 9 - override switches)
 *  -# dwell (G4). (G-modal-mode 0 - non-modal)
 *  -# set active plane (G17, G18, G19). (G-modal-mode 2 - plane selection)
 *  -# set length units (G20, G21). (G-modal-mode 6 - units)
 *  -# cutter radius compensation on or off (G40, G41, G42). (G-modal-mode 7 - cutter radius compensation)
 *  -# cutter length compensation on or off (G43, G49). (G-modal-mode 8 - tool length offset)
 *  -# coordinate system selection (G54, G55, G56, G57, G58, G59, G59.1, G59.2, G59.3). (G-modal-mode 12 - coordinate system selection)
 *  -# set path control mode (G61, G61.1, G64). (G-modal-mode 13 - path control mode)
 *  -# set distance mode (G90, G91). (G-modal-mode 3 - distance mode)
 *  -# set retract mode (G98, G99). (G-modal-mode 10 - return mode in canned cycles)
 *  -# home (G28, G30) or change coordinate system data (G10) or set axis offsets (G92, G92.1, G92.2, G94). (G-modal-mode 0 - non-modal)
 *  -# perform motion (G0 to G3, G80 to G89), as modified (possibly) by G53. (G-modal-mode 1 - motion)
 *  -# stop (M0, M1, M2, M30, M60). (M-modal-mode 4 - stopping)
 *
 */

#include "LUACodeEvaluator.h"
#include "MachineComponent.h"
#include "GCodeBlock.h"
#include "../Tool.h"
#include <wx/xml/xml.h>
#include <wx/string.h>
#include <list>

#include "../ToolPath.h"
#include "CNCPosition.h"

class Machine {
	friend class LUACodeEvaluator;
	//Constructor / Destructor
public:
	Machine();
	Machine(const Machine &other); //!< Copy constructor
	Machine& operator=(const Machine &other); ///< Assignment operator
	virtual ~Machine();

public:
	void ClearComponents(void); //!< Remove all loaded Geometry parts of the machine. Virtually removing the machine.
	bool Load(wxFileName const& fileName); //!< Load a machine.
	bool ReLoad(void); //!< Reload the machine from the file. E.g. after editing the file externally.
	void ToXml(wxXmlNode* parentNode);
	bool FromXml(wxXmlNode* node);

	void EvaluateDescription(void);
	bool IsInitialized(void) const;
	void Assemble(void); //!< Place all components of the machine after reading the MachinePosition.
	void Paint(void) const;
	void PaintNullTool(double length, double diameter) const;
	void PaintCoordinateSystem(double diameter) const;
private:
	bool PlaceComponent(wxString const& nameOfComponent,
			AffineTransformMatrix const& matrix);
	bool AddComponent(wxString const& nameOfComponent);
	bool LoadGeometryIntoComponent(const wxString &filename,
			MachineComponent* component, const AffineTransformMatrix &matrix);
	bool LoadGeometryIntoComponentFromZip(const wxFileName &zipFile,
			const wxString &filename, MachineComponent* component,
			const AffineTransformMatrix &matrix);
public:

	void Reset();

	Vector3 GetCenter(void) const;

	//TODO Remove the quick simulator
//	void DryRunToolPath(ToolPath* tp); //!< Rough estimation of the duration of a toolpath. Quick and dirty stand-alone machine simulator.

	void TouchoffPoint(const CNCPosition &point);
	void TouchoffHeight(const double height);

	bool InterpretGCode(GCodeBlock* block, bool generateMicroSteps = true);
	bool Step(void);

	// Member variables
public:
	wxFileName fileName;
	wxString machineDescription; //!< Lua script describing the machine.
	wxString textOut; //!< Errors and output of the Lua script.

	GCodeBlock codestate;
	CNCPosition lastpos;
	CNCPosition currentpos; //!< Absolute Position of the Machine

	unsigned char selectedCoordSystem;
	CNCPosition coordSystem[10];

	CNCPosition controlledpoint; //!< Position of the controlled point (= tip of the tool)
	double feedRate; //!< Feedrate (m/s)
	int spindleSpeed; //!< Spindle speed (1/s)
	bool floodCoolant;
	bool mistCoolant;
	enum Units {
		mms, inches
	};
	Units activeUnits;
	enum Plane {
		XY, YZ, XZ
	};
	Plane selectedPlane;
	ArrayOfTool tools; ///< Tool%s in the Machine
	int selectedTool;
	unsigned int selectedToolSlot;
	double toolLengthOffset;

	bool rapidMovement;

	AffineTransformMatrix toolPosition;
	AffineTransformMatrix workpiecePosition;

	CNCPosition offset0; //!< Offset from workpiece position to tool position zero. Used for rendering the machine and tools.

	// *** For simulation ***
	enum MicrostepMode {
		distanceBased, timeBased, gridBased
	};
	MicrostepMode microstepMode;
	double microstepDistance;
	double microstepDt;
	CNCPosition gridOrigin;
	CNCPosition gridDelta;
	size_t microstepPosition;
	std::vector <CNCPosition> microsteps;

private:
	void Interpolate(CNCPosition *a, CNCPosition *b, bool generateMicroSteps);

	bool initialized;
	LUACodeEvaluator evaluator;
	std::list <MachineComponent> components;

	MachineComponent* componentWithTool;
	AffineTransformMatrix toolPositionRelativ; //!< Position of the workpiece relative to the component it is connected to.
	MachineComponent* componentWithMaterial;
	AffineTransformMatrix workpiecePositionRelativ; //!< Position of the tool relative to the component it is connected to.

	//TODO Test if the variables below are really needed
	GCodeBlock newcode;
	GCodeBlock oldcode;
};

#endif /* MACHINE_H_ */
