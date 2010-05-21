///////////////////////////////////////////////////////////////////////////////
// Name               : GenericCAM.cpp
// Purpose            : Main entry point.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
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

#include "GenericCAM.h"

// The line that starts it all.
IMPLEMENT_APP(GenericCAMApp)

GenericCAMApp::GenericCAMApp()
{
}

bool GenericCAMApp::OnInit()
{
	frame = new MainFrame(NULL);
	frame -> Show();
	return true;
}

/*! \mainpage Generic CAM - Developers Documentation
 *
 * \image html  pictures/start.png
 *
 */

