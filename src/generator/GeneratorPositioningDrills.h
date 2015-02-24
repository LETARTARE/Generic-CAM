///////////////////////////////////////////////////////////////////////////////
// Name               : GeneratorPositioningDrills.h
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

#ifndef GENERATORPOSITIONINGDRILLS_H_
#define GENERATORPOSITIONINGDRILLS_H_
#include "Generator.h"

#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>

/*!\class GeneratorPositioningDrills
 * \brief ...
 *
 * ...
 */

class GeneratorPositioningDrills:public Generator {
public:
	GeneratorPositioningDrills(Project * project, size_t runNr,
			size_t toolpathNr);
	virtual ~GeneratorPositioningDrills();

	virtual void CopyFrom(const GeneratorPositioningDrills * other);
	virtual wxString GetName(void) const;
	virtual void AddToPanel(wxPanel * panel, DisplaySettings* settings);
	virtual void TransferDataToPanel(void) const;
	virtual void TransferDataFromPanel(void);
	virtual wxString ToString(void) const;
	virtual void FromString(const wxString & text);
	virtual void GenerateToolpath(void);

private:
	wxChoice* m_choiceSetups;
	wxRadioBox* m_radioBox;
	wxStaticText* m_staticTextHoleDiameter;
	wxTextCtrl* m_textCtrlHoleDiameter;
	wxStaticText* m_staticTextUnitDiameter;
	wxStaticText* m_staticTextHoleDepth;
	wxTextCtrl* m_textCtrlHoleDepth;
	wxStaticText* m_staticTextUnitDepth;
	wxStaticText* m_staticTextInfo;

	float depth;
	float diameter;

};

#endif /* GENERATORPOSITIONINGDRILLS_H_ */
