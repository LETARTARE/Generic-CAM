///////////////////////////////////////////////////////////////////////////////
// Name               : IDs.h
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 10.01.2015
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

#ifndef IDS_H_
#define IDS_H_

/*!\class IDs
 * \brief List of command IDs
 * This headerfile contains a list of command IDs. These are used to communicate
 * from the child windows to the main window.
 *
 * \par Difference between Update and Refresh
 *  - \b Refresh - Refresh of the display without changing the Project itself.
 *  - \b Update - Changing the Project or the Simulation and updating the display afterwards.
 *
 * \par List of IDs
 *  - \b ID_REFRESH3DVIEW - Refresh the main OpenGL drawing area (e.g after a rotation of scene)
 *  - \b ID_REFRESHMAINGUI - Update and refresh the Treeview, the menu items and the main OpenGL view
 *  - \b ID_REFRESHALL - All of the above, also all subwindows as well (e.g. propagation of Units)
 *  - \b ID_UPDATESIMULATION - Update the Simulation system in the Project. Refresh OpenGL afterwards.
 *  - \b ID_UPDATEMACHINESIMULATION - Refresh the Machine Simulator in the DialogMachineDebugger
 */

#define ID_REFRESH3DVIEW				(wxID_HIGHEST+1)
#define ID_REFRESHMAINGUI				(wxID_HIGHEST+2)
#define ID_REFRESHALL					(wxID_HIGHEST+3)

#define ID_UPDATESIMULATION				(wxID_HIGHEST+11)
#define ID_UPDATEMACHINESIMULATION		(wxID_HIGHEST+12)

//! \def ID_THREADLASTDONE Worker thread to main thread: Processing of volume ready.
#define ID_THREADLASTDONE				(wxID_HIGHEST+21)

#endif /* IDS_H_ */
