///////////////////////////////////////////////////////////////////////////////
// Name               : Machine.h
// Purpose            : The machine.
// Thread Safe        : Yes
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

#include "LUACodeEvaluator.h"

#include "MachineComponent.h"
#include "MachinePosition.h"
#include "Tool.h"
#include "../project/ToolPath.h"
//#include "../simulator/Workpiece.h"
#include <wx/string.h>
#include <wx/xml/xml.h>

class Machine {
	friend class LUACodeEvaluator;
	//Constructor / Destructor
public:
	Machine();
	virtual ~Machine();

	// Member variables
public:

	LUACodeEvaluator evaluator;
	MachinePosition position;
	ArrayOfMachineComponent components;

	wxFileName fileName;
	wxString machineDescription;
	wxString textOut;

//	Workpiece workpiece;

	Tool* tool;
	ToolPath* toolpath;

	AffineTransformMatrix toolPosition;
	AffineTransformMatrix workpiecePosition;
private:
	bool initialized;

	size_t componentWithTool;
	size_t componentWithMaterial;
	AffineTransformMatrix toolPositionRelativ;
	AffineTransformMatrix workpiecePositionRelativ;

	// Methods
public:
	void ToXml(wxXmlNode* parentNode);
	bool FromXml(wxXmlNode* node);

	void Paint(void) const;

	void ClearComponents(void);

	bool PlaceComponent(wxString const& nameOfComponent,
			AffineTransformMatrix const& matrix);
	bool AddComponent(wxString const& nameOfComponent);
	void Assemble(void);
	void EvaluateDescription(void);
	bool ReLoad(void);
	bool Load(wxFileName const& fileName);
	bool IsInitialized(void)
	{
		return initialized;
	}
};

#endif /* MACHINE_H_ */
