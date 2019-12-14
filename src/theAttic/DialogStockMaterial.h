///////////////////////////////////////////////////////////////////////////////
// Name               : DialogStockMaterial.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 15.06.2011
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

#ifndef DIALOGSTOCKMATERIAL_H_
#define DIALOGSTOCKMATERIAL_H_

/*!\class DialogStockMaterial
 * \brief Manages the heap of stock material in the workshop
 */

#include <wx/event.h>
#include <wx/string.h>

//#include "../project/Project.h"
//#include "../project/StockFile.h"
//#include "../StdInclude.h"
//#include "CollectionUnits.h"
#include "gui.h"

class DialogStockMaterial:public GUIStockMaterial {
	// Constructor/ Destructor
public:
	DialogStockMaterial(wxWindow* parent);
	virtual ~DialogStockMaterial();

	// Member Variables
private:
	int selectedLine;
	bool isInitialized;

	double sx, sy, sz;
	wxString name;
	double feedrate;
	double toolSpeed;
	bool available;

	// Methods
public:
	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);
	void Initialize(void);

protected:
	Project* GetProject(void);

	void OnXClose(wxCloseEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnAddUpdate(wxCommandEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnDelete(wxCommandEvent& event);
	void OnActivate(wxListEvent& event);
	void OnSelected(wxListEvent& event);
};

#endif /* DIALOGSTOCKMATERIAL_H_ */
