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
 *  - \b Refresh - Issue a request to refresh a window in the next run of the wxWidgets main event loop.
 *  - \b Update(in the context of wxWidgets) - Repaint the window immediately!
 *  - \b Update(in the context of Project) - Update the inner workings of the Project or the Simulation and issue a refresh for the next main event loop.
 */

//!> Refresh every view of every document:
#define ID_REFRESHALL					(wxID_HIGHEST+1)

//!> Refresh every 3D view of every document:
#define ID_REFRESHALL3D					(wxID_HIGHEST+2)

//!> Refresh all views of current document:
#define ID_REFRESHVIEW					(wxID_HIGHEST+3)

//!> Refresh all 3D views of the current document:
#define ID_REFRESHVIEW3D				(wxID_HIGHEST+4)

//!> Refresh the treeview of the current document:
#define ID_REFRESHTREEVIEW				(wxID_HIGHEST+5)

//!> Start the recalculation of the current project state:
#define ID_UPDATEPROJECT				(wxID_HIGHEST+21)
#define ID_UPDATESIMULATION				(wxID_HIGHEST+22)
#define ID_UPDATEMACHINESIMULATION		(wxID_HIGHEST+23)

// Setup calls to common hardware setup
#define ID_SETUPLANGUAGE				(wxID_HIGHEST+41)
#define ID_SETUPUNITS					(wxID_HIGHEST+42)
#define ID_SETUPSTEREO3D				(wxID_HIGHEST+43)
#define ID_SETUPMIDI					(wxID_HIGHEST+44)
#define ID_SETUPCONTROLLER				(wxID_HIGHEST+45)
#define ID_SETUPPATHS					(wxID_HIGHEST+46)

#define ID_PROJECTRENAME				(wxID_HIGHEST+61)
#define ID_OBJECTRENAME					(wxID_HIGHEST+62)
#define ID_OBJECTDELETE					(wxID_HIGHEST+63)
#define ID_RUNRENAME					(wxID_HIGHEST+64)
#define ID_RUNDELETE					(wxID_HIGHEST+65)
#define ID_GENERATORMODIFY				(wxID_HIGHEST+66)
#define ID_GENERATORRENAME				(wxID_HIGHEST+67)
#define ID_GENERATORDELETE				(wxID_HIGHEST+68)
#define ID_TOOLPATHGENERATE				(wxID_HIGHEST+69)

#define ID_SELECTIONDONE				(wxID_HIGHEST+80)
#define ID_SELECTIONOBJECT				(wxID_HIGHEST+81)
#define ID_SELECTIONFACE				(wxID_HIGHEST+82)
#define ID_SELECTIONEDGE				(wxID_HIGHEST+83)

#define ID_GENERATORADDTYPE				(wxID_HIGHEST+601)
// ... and the next 100 IDs ...

#endif /* IDS_H_ */
