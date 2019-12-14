///////////////////////////////////////////////////////////////////////////////
// Name               : Config.h
// Purpose            : Global configuration
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
///////////////////////////////////////////////////////////////////////////////

/*  Configuration file. Major switches that change the code
 *  and the structure can be found here (_DEBUG_ for example).
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define _GENERICCAM_VERSION_MAJOR 0
#define _GENERICCAM_VERSION_MINOR 2
#define _GENERICCAM_VERSION_PATCH 0

//#define _DEBUGMODE
#define _USE_CPPUNIT
#define _USE_3DVIEWS
#define _USE_3DPICKING
#define _USE_MIDI
#define _USE_6DOFCONTROLLER
//#define _USE_MULTITHREADING

#endif /* CONFIG_H_ */
