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
 */

#include "../../3D/AffineTransformMatrix.h"
#include "../generator/CNCPosition.h"
#include "LUACodeEvaluator.h"
#include "MachineComponent.h"

#include <wx/filename.h>
#include <wx/string.h>
#include <stddef.h>
#include <list>
#include <vector>

class Machine {
	friend class LUACodeEvaluator;
public:
	Machine();
	virtual ~Machine();

public:
	void ClearComponents(void); //!< Remove all loaded Geometry parts of the machine. Virtually removing the machine.
	bool Load(wxFileName const& fileName); //!< Load a machine.
	bool ReLoad(void); //!< Reload the machine from the file. E.g. after editing the file externally.

	void EvaluateDescription(void);
	bool IsLoaded(void) const;
	void Assemble(void); //!< Place all components of the machine after reading the MachinePosition.

	void MoveToGlobalZero(void);
	void SetWorkCoordinateSystem(unsigned char index,
			const AffineTransformMatrix &coordsys);
	void SetToolLength(double toollength); //!< Shiftback of machine = Tool.geometry.LB + Holder-length outside of machine
	void SetPosition(const CNCPosition &position);
	CNCPosition GetCurrentPosition(void) const; //!< Return the position the machine actually reached.

	void Paint(void) const;
	void PaintNullTool(double length, double diameter) const;
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
	wxFileName fileName;
	wxString machineDescription; //!< Lua script describing the machine.
	wxString textOut; //!< Errors and output of the Lua script.

	CNCPosition setposition; //!< Position of the controlled point (= tip of the tool)
	CNCPosition reachedposition; //!< Position actually reached

	double toolLength;

	unsigned char selectedCoordSystem;
	AffineTransformMatrix coordSystem[10];

	AffineTransformMatrix toolPosition;
	AffineTransformMatrix workpiecePosition;

	static const size_t NR_IKAXIS = 10;
	double IKaxis[NR_IKAXIS]; //!< Axes for IK based model.
	bool IKaxisused[NR_IKAXIS]; //!< Is the axis really used in the machine?

private:
	bool initialized;

	double GetError(void) const;

	LUACodeEvaluator evaluator;
	std::list <MachineComponent> components;

	MachineComponent* componentWithTool;
	AffineTransformMatrix toolPositionRelativ; //!< Position of the workpiece relative to the component it is connected to.
	MachineComponent* componentWithMaterial;
	AffineTransformMatrix workpiecePositionRelativ; //!< Position of the tool relative to the component it is connected to.

protected:
	// Prevent the machine from accidentally being copied by hiding the copy and
	// assignment constructor.
	Machine(const Machine &);
	Machine& operator=(const Machine &);

};

#endif /* MACHINE_H_ */
