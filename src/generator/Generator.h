///////////////////////////////////////////////////////////////////////////////
// Name               : Generator.h
// Purpose            : Abstract class for toolpath generators
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 22.08.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <stddef.h>
#include <wx/panel.h>
#include <wx/string.h>

#include "../3D/BoundingBox.h"
#include "../gui/DisplaySettings.h"

class Project;
class ToolPath;

/*!\class Generator
 * \brief Abstract class for toolpath generators
 *
 * ...
 */

class Generator {
	friend class DialogToolpathGenerator;
	// Constructor/ Destructor
public:
	Generator(Project * project, size_t runNr, size_t toolpathNr);
	virtual ~Generator();

	//Member variables:
public:
	bool toolpathGenerated;
	bool errorOccured;
	wxString output;

	BoundingBox box;
	float marginBelow;
	float marginSide;

protected:
	DisplaySettings * settings;
	ToolPath * toolpath;
	Project * project;
	size_t runNr;
	size_t toolpathNr;

	//Methods:
public:

	virtual void CopyFrom(const Generator * other);

	virtual wxString GetName(void) const = 0;
	virtual void AddToPanel(wxPanel * panel, DisplaySettings * settings);
	virtual void TransferDataToPanel(void) const = 0;
	virtual void TransferDataFromPanel(void) = 0;
	virtual wxString ToString(void) const = 0;
	virtual void FromString(const wxString & text) = 0;

	virtual void GenerateToolpath(void) = 0;

};

#endif /* GENERATOR_H_ */
