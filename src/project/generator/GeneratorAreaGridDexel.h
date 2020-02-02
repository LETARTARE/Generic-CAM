///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorAreaGridDexel.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.02.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef GENERATORAREAGRIDDEXEL_H_
#define GENERATORAREAGRIDDEXEL_H_

/*!\class GeneratorAreaGridDexel
 * \ingroup Generator
 * \brief ...
 *
 * ...
 */


#include "../Object.h"
#include "Direction.h"
#include "GeneratorDexel.h"
#include "ProtoToolpath.h"
#include "GeneratorFactory.h"

#include <stddef.h>
#include <map>
#include <vector>

#include <wx/radiobut.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

class GeneratorAreaGridDexel:public GeneratorDexel {
public:
	GeneratorAreaGridDexel();
	virtual ~GeneratorAreaGridDexel();
	virtual size_t GetType(void) const
	{
		return TYPE_GENERATORAREAGRID;
	}
	virtual wxString GetTypeName(void) const;
	virtual void CopyParameterFrom(const Generator * other);
	virtual bool operator==(const Generator &b) const;
	virtual wxSizer * AddToPanel(wxPanel * panel,
			CollectionUnits* settings) const;
	virtual void TransferDataToPanel(wxPanel* panel,
			CollectionUnits* settings) const;
	virtual void TransferDataFromPanel(CollectionUnits* settings);
	virtual void GenerateToolpath(const Run &run,
			const std::map <size_t, Object> &objects, const Tool &tool,
			const DexelTarget &base);
private:
	void CollectToolpaths(std::vector <ProtoToolpath> &ptp,
			const double pathDistance);

public:
	double overlap;
	double maxStepUp;
	Direction type;

private:
	mutable wxRadioButton* m_radioBtnXthenY;
	mutable wxStaticBitmap* m_bitmapXthenY;
	mutable wxRadioButton* m_radioBtnYthenX;
	mutable wxStaticBitmap* m_bitmapYthenX;
	mutable wxStaticText* m_staticTextOverlap;
	mutable wxTextCtrl* m_textCtrlOverlap;
	mutable wxStaticText* m_staticTextUnitOverlap;
};

#endif /* GENERATORAREAGRIDDEXEL_H_ */
