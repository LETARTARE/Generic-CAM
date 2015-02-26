///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorTest.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.07.2011
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

#ifndef GENERATORTEST_H_
#define GENERATORTEST_H_

#include <stddef.h>
#include <wx/string.h>

#include "../machine/Tool.h"
#include "GeneratorDexel.h"

/*!\class GeneratorTest
 * \brief ...
 *
 * ...
 */

class GeneratorTest:public GeneratorDexel {
	// Constructor/ Destructor
public:
	GeneratorTest(Project * project, size_t runNr, size_t toolpathNr);
	virtual ~GeneratorTest();

	virtual void CopyFrom(const Generator * other);
	virtual wxString GetName(void) const;
	virtual void AddToPanel(wxPanel * panel, DisplaySettings* settings);
	virtual void TransferDataToPanel(void) const;
	virtual void TransferDataFromPanel(void);
	virtual wxString ToString(void) const;
	virtual void FromString(const wxString & text);

	virtual void GenerateToolpath(void);

	//Member variables:
public:

	// Generic Toolpath parameters
	double freeHeightAboveMaterial;

	// Toolpath generation parameter (extract from tool?)
	double levelDrop;

};

#endif /* GENERATORTEST_H_ */
