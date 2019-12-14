///////////////////////////////////////////////////////////////////////////////
// Name               : CommandWorkpieceAdd.h
// Purpose            : Create a new workpiece from stock material
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 16.01.2015
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

#ifndef COMMANDWORKPIECEADD_H_
#define COMMANDWORKPIECEADD_H_

/**\brief Create a new workpiece from stock material
 */

#include "../Project.h"
#include "../StockMaterial.h"

#include <wx/cmdproc.h>
#include <wx/string.h>

class CommandWorkpieceAdd:public wxCommand {
public:
	CommandWorkpieceAdd(const wxString& name, Project * project,
			StockMaterial stock, int refObject = -1);
	virtual ~CommandWorkpieceAdd();

	bool Do(void);
	bool Undo(void);

protected:
	Project * project;
	StockMaterial stock;
	int refObject;
};

#endif /* COMMANDWORKPIECEADD_H_ */
