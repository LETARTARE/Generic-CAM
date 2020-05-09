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

#include "../../StdInclude.h"

#include "../Object.h"
#include "../Tool.h"
#include "../Selection.h"
#include "CNCPosition.h"
#include "DexelTarget.h"

#include <stddef.h>
#include <list>
#include <vector>
#include <map>

#include <wx/string.h>
#include <wx/txtstrm.h>
#include <wx/panel.h>

class Run;
class CollectionUnits;

class Generator {
//	friend class DialogToolpathGenerator;
	friend class CommandRunGeneratorAdd;
//	friend class GeneratorFactory;

// Constructor/ Destructor
public:
	Generator(size_t ID);
	virtual ~Generator();

	//Member variables:
public:
//	Run * parent; //!< Pointer back to the Run this Generator belongs to.

	wxString name;
	Selection area; //!< Area to work in
	std::string toolguid; //!< Reference to a Tool from Run
	double spindlespeed;
	double feedrate;
	float freeHeight; //!< Distance from the top of the material for fast travel
	float marginBelow; //!< Distance to the final shape below the tool
	float marginSide; //!< Distance to the final shape next to the tool

	bool toolpathGenerated; //!< Flag if toolpath was generated
	std::vector <CNCPosition> toolpath; //!< Generated ToolPath
	bool errorOccured;
	wxString output;

private:
	size_t ID;

//Methods:
public:
	bool operator==(const size_t ID) const;
	size_t GetID(void) const;

	virtual size_t GetType(void) const = 0;
	virtual wxString GetTypeName(void) const = 0;
	virtual wxString GetName(void) const;
	virtual bool operator==(const Generator &b) const;
	virtual void CopyParameterFrom(const Generator * other);
	virtual wxSizer * AddToPanel(wxPanel * panel,
			CollectionUnits * settings) const = 0;
	virtual void TransferDataToPanel(wxPanel* panel,
			CollectionUnits* settings) const = 0;
	virtual void TransferDataFromPanel(CollectionUnits* settings) = 0;
	virtual void ToJSON(JSON &js) const;
	virtual bool FromJSON(const JSON &js);
	virtual void Paint(void) const;
	virtual void GenerateToolpath(const Run &run,
			const std::list <Object> &objects, const Tool &tool,
			const DexelTarget &base) = 0;
};

#endif /* GENERATOR_H_ */
