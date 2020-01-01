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

/*!\class GeneratorTest
 * \ingroup Generator
 * \brief ...
 *
 * ...
 */

#include "GeneratorDexel.h"
#include "../Tool.h"

#include <wx/string.h>
#include <stddef.h>

#define TYPE_GENERATORTEST	34745572

class GeneratorTest:public GeneratorDexel {
	// Constructor/ Destructor
public:
	GeneratorTest();
	virtual ~GeneratorTest();
	virtual size_t GetType(void) const
	{
		return TYPE_GENERATORTEST;
	}
	virtual wxString GetTypeName(void) const
	{
		return _("Test (dexel-based)");
	}
	virtual void CopyParameterFrom(const Generator * other);
	virtual bool operator==(const Generator &b) const;
	virtual wxSizer * AddToPanel(wxPanel* panel,
			CollectionUnits* settings) const;
	virtual void TransferDataToPanel(wxPanel* panel,
			CollectionUnits* settings) const;
	virtual void TransferDataFromPanel(CollectionUnits* settings);
	virtual void GenerateToolpath(const Run &run,
			const std::map <size_t, Object>  &objects,
			const Tool * tool, DexelTarget * base);

	//Member variables:
public:
	double twiddleFactor;

	mutable wxStaticText* m_staticTextTwiddleFactor;
	mutable wxTextCtrl* m_textCtrlTwiddleFactor;
	mutable wxStaticText* m_staticTextUnit;
};

#endif /* GENERATORTEST_H_ */
