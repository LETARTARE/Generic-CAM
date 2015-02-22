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

#include "GeneratorDexel.h"

#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/string.h>

/*!\class GeneratorAreaGridDexel
 * \brief ...
 *
 * ...
 */

class GeneratorAreaGridDexel:public GeneratorDexel {
public:
	GeneratorAreaGridDexel();
	virtual ~GeneratorAreaGridDexel();

	virtual void CopyFrom(const Generator * other);
	virtual wxString GetName(void) const;
	virtual void AddToPanel(wxPanel * panel, DisplaySettings* settings);
	virtual void TransferDataToPanel(void) const;
	virtual void TransferDataFromPanel(void);
	virtual wxString ToString(void) const;
	virtual void FromString(const wxString & text);
	virtual wxThread::ExitCode Entry(void);

private:
	wxRadioBox* m_radioBoxDirection;
};

#endif /* GENERATORAREAGRIDDEXEL_H_ */
