///////////////////////////////////////////////////////////////////////////////
// Name               : Toolbox.h
// Purpose            : Holds a collection of tools.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 16.03.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate: 2010-05-04 01:11:20 +0200 (Di, 04 Mai 2010) $
//$Revision: 44 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////


#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include "../machine/Tool.h"

#include <wx/xml/xml.h>
#include <wx/string.h>
#include <wx/filename.h>

class Toolbox {
	//Constructor / Destructor
public:
	Toolbox();
	virtual ~Toolbox();

	//Member variables
public:
	wxFileName fileName;

	ArrayOfTool tools;

private:
	bool initialized;
	wxXmlDocument xmlDocument;

	// Methods
public:
	bool LoadToolbox(wxFileName& fileName);
	bool SaveToolbox(wxFileName& fileName);
	bool IsInitialized(void)
	{
		return initialized;
	}
};

#endif /* TOOLBOX_H_ */
