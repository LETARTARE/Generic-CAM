///////////////////////////////////////////////////////////////////////////////
// Name               : Workpiece.cpp
// Purpose            : The workpiece.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.03.2010
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
//$LastChangedDate$
//$Revision$
//$LastChangedBy$
///////////////////////////////////////////////////////////////////////////////


#include "Workpiece.h"
#include <wx/log.h>

Workpiece::Workpiece()
{

	AddBox(0.4, 0.3, 0.1);
	//s.SetSphere(0.2);
	//	if(gts_surface_is_closed(s.s)){
	//		wxLogMessage(_T("Surface is closed!"));
	//	}else{
	//		wxLogMessage(_T("Surface is open!"));
	//	}


	//s.SelfTest();

	//s.Statistics();

	CSGSurface b;
	//b.SetSphere(0.3);
	b.AddBox(0.4, 0.3, 0.1);
	b.Translate(-0.2, -0.15, 0.05);


	//b.Statistics();

	//b.SelfTest();
	BooleanRemove(&b);


	//s.Statistics();


	//s.SelfTest();
}

Workpiece::~Workpiece()
{

}
