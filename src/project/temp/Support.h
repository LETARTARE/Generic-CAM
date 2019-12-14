///////////////////////////////////////////////////////////////////////////////
// Name               : Support.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 09.02.2015
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

#ifndef SUPPORT_H_
#define SUPPORT_H_

/*!\class Support
 * \ingroup document
 * \brief Support structure around the object
 *
 * When manufacturing an object, that is atand alone (i.e. not just an incarving) the object
 * may be unconnected to the rest of the workpiece. It would float around.
 *
 * This object provides an support structure, that is added to the object, to keep it from
 * doing just that, by adding connections to the rest of the workpiece.
 */


class Support {
public:
	Support();
	virtual ~Support();


	//	double supportDistance;
		//	double supportWidth;
		//	double supportHeight;
		//	double middleY;
		//	double offsetX;

};

#endif /* SUPPORT_H_ */
