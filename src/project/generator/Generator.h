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

/*!\class Generator
 * \ingroup GeneratorBasic
 * \brief Abstract class for toolpath generators
 *
 *
 * Note: The pointers in this class do not own objects. No copy constructor is needed.
 */

#include "../Tool.h"
#include "../ToolPath.h"
#include "../../gui/DisplaySettings.h"
#include "../../3D/BoundingBox.h"
//#include "../../3D/AffineTransformMatrix.h"

#include "../../StdInclude.h"
#include <wx/panel.h>
#include <wx/string.h>
#include <wx/txtstrm.h>
#include <wx/dynarray.h>
#include <stddef.h>

class Run;
class Workpiece;

class Generator {
	friend class DialogToolpathGenerator;
	friend class GeneratorCollection;

	// Constructor/ Destructor
public:
	Generator();
	virtual ~Generator();

	//Member variables:
public:
	Run * parent; //!< Pointer back to the Run this Generator belongs to.
	BoundingBox area; //!< Area to work in

	ToolPath toolpath; //!< Generated ToolPath
	bool toolpathGenerated; //!< Flag if toolpath was generated

	bool errorOccured;
	wxString output;

public:
	// Common settings for all toolpath generators
	unsigned int refTool; //!< Reference number of a Tool from Run //TODO:: Check for consistency over all classes.
	float freeHeight; //!< Distance from the top of the material for fast travel
	float marginBelow; //!< Distance to the final shape below the tool
	float marginSide; //!< Distance to the final shape next to the tool

	bool selected;

protected:
	DisplaySettings * settings;

//Methods:
public:
	virtual wxString GetName(void) const;
	virtual void CopyParameterFrom(const Generator * other);
	virtual void AddToPanel(wxPanel * panel, DisplaySettings * settings);
	virtual void TransferDataToPanel(void) const = 0;
	virtual void TransferDataFromPanel(void) = 0;
	virtual void ToStream(wxTextOutputStream & stream);
	virtual bool FromStream(wxTextInputStream & stream);
	virtual void Paint(void) const;
	virtual void GenerateToolpath(void) = 0;
};
WX_DECLARE_OBJARRAY(Generator*, ArrayOfGeneratorPointer);

#endif /* GENERATOR_H_ */
